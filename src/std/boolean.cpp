#include "vm_context_methods.hpp"
#include "vm_value_methods.hpp"

using namespace cuttle::vm;

int equal_func(context_t& context, const std::vector<value_t>& args, value_t& ret) {
	ret = { { type_id::boolean },{ context.gc.add(new bool{ args[0] == args[1] }) } };
	return 0;
}

int not_equal_func(context_t& context, const std::vector<value_t>& args, value_t& ret) {
	ret = { { type_id::boolean },{ context.gc.add(new bool{ args[0] != args[1] }) } };
	return 0;
}

int boolean_from_string_func(context_t& context, const std::vector<value_t>& args, value_t& ret) {
	ret = { { type_id::boolean },{ context.gc.add(new bool{ *args[0].data.string == "true" }) } };
	return 0;
}

void register_boolean(context_t& context) {
	value_t equal = { { type_id::function, { { type_id::any }, { type_id::any } } } };
	equal.data.function = equal_func;
	add(context, "==", equal);

	value_t not_equal = { { type_id::function, { { type_id::any },{ type_id::any } } } };
	not_equal.data.function = not_equal_func;
	add(context, "!=", not_equal);

	value_t boolean_from_string = { { type_id::function, { { type_id::string } } } };
	boolean_from_string.data.function = boolean_from_string_func;
	add(context, "boolean", boolean_from_string);
}