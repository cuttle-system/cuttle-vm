#include <sstream>
#include <iterator>
#include <vector>
#include "vm_context_methods.hpp"
#include "interpreter.hpp"
#include "special_char_conversion_error.hpp"
#include "parse_error.hpp"

std::string convert_special_chars(std::string str) {
	using namespace cuttle::vm;

	std::string converted_str;
	for (unsigned int i = 0; i < str.length(); ++i) {
		if (str[i] == '\\') {
			if (i >= str.length() - 1) {
				throw special_char_conversion_error("Unexpected end of input");
			}
			++i;
			switch (str[i]) {
			case 'n':
				converted_str += '\n';
				break;
			case 'r':
				converted_str += '\r';
				break;
			case 't':
				converted_str += '\t';
				break;
			case '\\':
				converted_str += '\\';
				break;
			default:
				throw special_char_conversion_error(std::string("Unknown character '") + str[i] + "'");
			}
		} else {
			converted_str += str[i];
		}
	}
	return converted_str;
}

cuttle::vm::value_t parse_value(cuttle::vm::context_t& context, std::istream &input) {
	using namespace cuttle::vm;

	value_t val;
	char type;
	std::string str;
	input >> type;
	input.ignore(1);
	getline(input, str);

	std::string converted_str = convert_special_chars(str);
	value_t str_value = { {type_id::string}, {context.gc.add(new std::string(converted_str))} };

	switch (type) {
	case 'i':
		call(context, "integral", {str_value}, 1, val);
		break;
	case 's':
		val = str_value;
		break;
	case 'r':
		call(context, "real", { str_value }, 1, val);
		break;
	case 'b':
		call(context, "boolean", { str_value }, 1, val);
		break;
	default:
		throw parse_error(std::string("Unknown type: ") + type);
	}

	return val;
}

void cuttle::vm::eval(std::istream &input, cuttle::vm::context_t &context, std::deque<cuttle::vm::value_t> &arg_stack) {
	using namespace cuttle::vm;

    unsigned int argn, type_argn;
    char operation, direction;
    value_t ret;
    std::string func_name, label_name, register_name;
    std::vector<value_t> args;

    input >> operation;

	switch (operation) {
	case 'b':
		arg_stack.push_back(parse_value(context, input));
		context.registers.push_back("");
		break;
	case 'f':
		arg_stack.push_front(parse_value(context, input));
		context.registers.push_front("");
		break;
	case 'c':
		input >> argn >> type_argn >> func_name;
		args = std::vector<value_t>(arg_stack.begin() + (arg_stack.size() - argn), arg_stack.end());
		call(context, func_name, args, type_argn, ret);
		while (argn--) {
			arg_stack.pop_back();
            context.registers.pop_back();
		}
		if (ret.type.id != type_id::nothing) {
            arg_stack.push_back(ret);
            context.registers.push_back("");
        }
		break;
    case 'a':
        input >> register_name >> func_name;
        argn = 0;
        for (auto it = context.registers.crbegin(); it != context.registers.crend() && *it != register_name; ++it, ++argn);
        args = std::vector<value_t>(arg_stack.begin() + (arg_stack.size() - argn), arg_stack.end());
        call(context, func_name, args, 0, ret);
        while (argn--) {
            arg_stack.pop_back();
            context.registers.pop_back();
        }
        if (ret.type.id != type_id::nothing) {
            arg_stack.push_back(ret);
            context.registers.push_back("");
        }
	    break;
    case 'g':
	    input >> direction >> label_name;
		if (!arg_stack.empty()) {
			if (*arg_stack.back().data.boolean) {
                if (direction == '<') {
                    input.seekg(context.labels[label_name]);
                } else if (direction == '>') {
                    std::string line, found_label_name;
                    while (std::getline(input, line)) {
                        if (line[0] == 'l') {
                            std::stringstream ss;
                            ss.str(line);
                            char op;
                            ss >> op >> found_label_name;
                            if (label_name == found_label_name) {
                                break;
                            }
                        }
                    }
                }
            }
            arg_stack.pop_back();
            context.registers.pop_back();
        }
	    break;
    case 'l':
        input >> label_name;
        context.labels[label_name] = input.tellg();
        break;
    case 'r':
        input >> register_name;
        context.registers.push_back(register_name);
	    break;
    default:
        throw parse_error(std::string("Unknown operation: ") + operation);
	}
}