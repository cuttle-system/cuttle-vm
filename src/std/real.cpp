#include "context_methods.hpp"
#include "value_methods.hpp"

using namespace cuttle::vm;

int real_plus_func(context_t& context, const std::vector<value_t>& args, value_t& ret) {
	ret = { {type_id::real}, {context.gc.add(new double{*args[0].data.real + *args[1].data.real})} };
	return 0;
}

int real_minus_func(context_t& context, const std::vector<value_t>& args, value_t& ret) {
	ret = { { type_id::real },{ context.gc.add(new double{ *args[0].data.real - *args[1].data.real }) } };
	return 0;
}

int real_multiply_func(context_t& context, const std::vector<value_t>& args, value_t& ret) {
	ret = { { type_id::real },{ context.gc.add(new double{ *args[0].data.real * *args[1].data.real }) } };
	return 0;
}

int real_divide_func(context_t& context, const std::vector<value_t>& args, value_t& ret) {
	ret = { { type_id::real },{ context.gc.add(new double{ *args[0].data.real / *args[1].data.real }) } };
	return 0;
}

int string_to_real_func(context_t& context, const std::vector<value_t>& args, value_t& ret) {
	ret = { {type_id::real} };
	ret.data.real = context.gc.add(new double{ atof(args[0].data.string->c_str()) });
	return 0;
}

int integral_to_real_func(context_t& context, const std::vector<value_t>& args, value_t& ret) {
	ret = { { type_id::real } };
	ret.data.real = context.gc.add(new double{ (double) *args[0].data.integral });
	return 0;
}

void register_real(context_t& context) {
	value_t plus = { { { type_id::function },{ { type_id::real },{ type_id::real } } }};
	plus.data.function = real_plus_func;
	add(context, "+", plus);

	value_t minus = { { { type_id::function },{ { type_id::real },{ type_id::real } } } };
	minus.data.function = real_minus_func;
	add(context, "-", minus);

	value_t multiply = { { { type_id::function },{ { type_id::real },{ type_id::real } } } };
	multiply.data.function = real_multiply_func;
	add(context, "*", multiply);

	value_t divide = { { { type_id::function },{ { type_id::real },{ type_id::real } } } };
	divide.data.function = real_divide_func;
	add(context, "/", divide);

	value_t string_to_real = { { { type_id::function },{ { type_id::string } } } };
	string_to_real.data.function = string_to_real_func;
	add(context, "real", string_to_real);

	value_t integral_to_real = { { { type_id::function },{ { type_id::integral } } } };
	integral_to_real.data.function = integral_to_real_func;
	add(context, "real", integral_to_real);

	//value_t plus = { { { type_id::function },{ { type_id::real },{ type_id::real } } } };
	//plus.data.function = real_plus_func;
	//add(context, "+", plus);
	//add(context, "real", { { type_id::function },{ real_plus_func } });
	//add(context, "real", { { type_id::function }, { real_plus_func }});
	//add(context, "real", string_to_real_func);
	//add(context, "real", integral_to_real_func);
}