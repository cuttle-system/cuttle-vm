#include <sstream>
#include <iterator>
#include <vector>
#include "context_methods.hpp"
#include "interpreter.hpp"

cuttle::vm::value_t parse_value(cuttle::vm::context_t& context, std::stringstream &input) {
	using namespace cuttle::vm;
	
	value_t val;
	char type;
	std::string str;
	input >> type;
	getline(input, str);

	value_t str_value = { {type_id::string}, {(double *) context.gc.add(new std::string(str))} };

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
		std::vector<value_t> args(arg_stack.begin() + argn, arg_stack.end());
		call(context, func_name, args, ret);
		arg_stack.clear();
		arg_stack.push_back(ret);
		break;
	}
}