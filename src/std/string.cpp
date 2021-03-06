#include <sstream>
#include <iomanip>
#include "vm_context_methods.hpp"
#include "vm_value_methods.hpp"

using namespace cuttle::vm;

int real_to_string_func(context_t& context, const std::vector<value_t>& args, value_t& ret) {
	std::ostringstream oss;
	oss << std::fixed << *args[0].data.real;
	ret = { { type_id::string } };
	ret.data.string = context.gc.add_r(new std::string{ oss.str() });
	return 0;
}

int integral_to_string_func(context_t& context, const std::vector<value_t>& args, value_t& ret) {
	std::ostringstream oss;
	oss << *args[0].data.integral;
	ret = { { type_id::string } };
	ret.data.string = context.gc.add_r(new std::string{ oss.str() });
	return 0;
}

int string_to_string_func(context_t& context, const std::vector<value_t>& args, value_t& ret) {
	ret.data.string = context.gc.add_r(new std::string{ *args[0].data.string });
	return 0;
}

void register_string(context_t& context) {
	value_t real_to_string = { { type_id::function, { { type_id::real } } } };
	real_to_string.data.function = real_to_string_func;
	add(context, "string", real_to_string);

	value_t integral_to_string = { { type_id::function, { { type_id::integral } } } };
	integral_to_string.data.function = integral_to_string_func;
	add(context, "string", integral_to_string);

	value_t string_to_string = { { type_id::function, { { type_id::string } } } };
	string_to_string.data.function = string_to_string_func;
	add(context, "string", string_to_string);

	//value_t plus = { { { type_id::function },{ { type_id::real },{ type_id::real } } } };
	//plus.data.function = real_plus_func;
	//add(context_t, "+", plus);

	//value_t string_to_real = { { { type_id::function },{ { type_id::string } } } };
	//string_to_real.data.function = string_to_real_func;
	//add(context_t, "real", string_to_real);

	//value_t plus = { { { type_id::function },{ { type_id::real },{ type_id::real } } } };
	//plus.data.function = real_plus_func;
	//add(context_t, "+", plus);
	//add(context_t, "real", { { type_id::function },{ real_plus_func } });
	//add(context_t, "real", { { type_id::function }, {real_plus_func }});
	//add(context_t, "real", string_to_real_func);
	//add(context_t, "real", integral_to_real_func);
}