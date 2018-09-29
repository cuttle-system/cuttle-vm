#include "vm_context_methods.hpp"
#include "vm_value_methods.hpp"

using namespace cuttle::vm;

int integral_plus_func(context_t& context, const std::vector<value_t>& args, value_t& ret) {
	ret = { {type_id::integral}, {context.gc.add(new integral_t{*args[0].data.integral + *args[1].data.integral})} };
	return 0;
}

int integral_minus_func(context_t& context, const std::vector<value_t>& args, value_t& ret) {
	ret = { { type_id::integral }, { context.gc.add(new integral_t{ *args[0].data.integral - *args[1].data.integral }) } };
	return 0;
}

int integral_multiply_func(context_t& context, const std::vector<value_t>& args, value_t& ret) {
	ret = { { type_id::integral }, { context.gc.add(new integral_t{ *args[0].data.integral * *args[1].data.integral }) } };
	return 0;
}

int integral_divide_func(context_t& context, const std::vector<value_t>& args, value_t& ret) {
	ret = { { type_id::integral }, { context.gc.add(new integral_t{ *args[0].data.integral / *args[1].data.integral }) } };
	return 0;
}

int string_to_integral_func(context_t& context, const std::vector<value_t>& args, value_t& ret) {
	ret = { {type_id::integral} };
	ret.data.integral = context.gc.add_r(new integral_t{ std::stoi(*args[0].data.string) });
	return 0;
}

int real_to_integral_func(context_t& context, const std::vector<value_t>& args, value_t& ret) {
	ret = { { type_id::integral } };
	ret.data.integral = context.gc.add_r(new integral_t{ (integral_t) *args[0].data.real });
	return 0;
}

void register_integral(context_t& context) {
	value_t plus = { { type_id::function, { { type_id::integral }, { type_id::integral } } }};
	plus.data.function = integral_plus_func;
	add(context, "+", plus);

	value_t minus = { { type_id::function, { { type_id::integral }, { type_id::integral } } } };
	minus.data.function = integral_minus_func;
	add(context, "-", minus);

	value_t multiply = { { type_id::function, { { type_id::integral }, { type_id::integral } } } };
	multiply.data.function = integral_multiply_func;
	add(context, "*", multiply);

	value_t divide = { { type_id::function, { { type_id::integral }, { type_id::integral } } } };
	divide.data.function = integral_divide_func;
	add(context, "/", divide);

	value_t string_to_integral = { { type_id::function, { { type_id::string } } } };
	string_to_integral.data.function = string_to_integral_func;
	add(context, "integral", string_to_integral);

	value_t real_to_integral = { { type_id::function, { { type_id::integral } } } };
	real_to_integral.data.function = real_to_integral_func;
	add(context, "integral", real_to_integral);

	//value_t plus = { { type_id::function, { { type_id::integral }, { type_id::integral } } } };
	//plus.data.function = integral_plus_func;
	//add(context_t, "+", plus);
	//add(context_t, "integral", { type_id::function, { integral_plus_func } });
	//add(context_t, "integral", { type_id::function,  { integral_plus_func }});
	//add(context_t, "integral", string_to_integral_func);
	//add(context_t, "integral", real_to_integral_func);
}