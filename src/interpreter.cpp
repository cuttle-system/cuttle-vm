#include <sstream>
#include <iterator>
#include <vector>
#include "context_methods.hpp"
#include "interpreter.hpp"
#include "special_char_conversion_error.hpp"

std::string convert_special_chars(std::string str) {
	using namespace cuttle::vm;

	std::string converted_str = "";
	for (int i = 0; i < str.length(); ++i) {
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
			default:
				throw special_char_conversion_error("Unknown character '" + str[i] + std::string("'"));
			}
		} else {
			converted_str += str[i];
		}
	}
	return converted_str;
}

cuttle::vm::value_t parse_value(cuttle::vm::context_t& context, std::stringstream &input) {
	using namespace cuttle::vm;
	
	value_t val;
	char type;
	std::string str;
	input >> type;
	input.ignore(1);
	getline(input, str);

	std::string converted_str = convert_special_chars(str);
	value_t str_value = { {type_id::string}, {(double *) context.gc.add(new std::string(converted_str))} };

	// TODO: integral and boolean from string translation

	switch (type) {
	case 'i':
		call(context, "integral", {str_value}, val);
		break;
	case 's':
		val = str_value;
		break;
	case 'r':
		call(context, "real", { str_value }, val);
		break;
	case 'b':
		call(context, "boolean", { str_value }, val);
		break;
	}

	return val;
}

void cuttle::vm::eval(std::stringstream &input, cuttle::vm::context_t &context, std::deque<cuttle::vm::value_t> &arg_stack) {
	using namespace cuttle::vm;

	char operation;
	input >> operation;

	switch (operation) {
	case 'b':
		arg_stack.push_back(parse_value(context, input));
		break;
	case 'f':
		arg_stack.push_front(parse_value(context, input));
		break;
	case 'c':
		int argn;
		std::string func_name;
		value_t ret;
		input >> argn >> func_name;
		std::vector<value_t> args(arg_stack.begin() + (arg_stack.size() - argn), arg_stack.end());
		call(context, func_name, args, ret);
		while (argn--) {
			arg_stack.pop_back();
		}
		arg_stack.push_back(ret);
		break;
	}
}