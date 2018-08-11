#include "context_methods.hpp"
#include "value_methods.hpp"

using namespace cuttle::vm;

int equal_func(context_t& context, const std::vector<value_t>& args, value_t& ret) {
	ret = { { type_id::boolean },{ context.gc.add(new bool{ args[0] == args[1] }) } };
	return 0;
}

int not_equal_func(context_t& context, const std::vector<value_t>& args, value_t& ret) {
	ret = { { type_id::boolean },{ context.gc.add(new bool{ args[0] != args[1] }) } };
	return 0;
}

void register_boolean(context_t& context) {
	value_t equal = { { type_id::function, { { type_id::any }, { type_id::any } } } };
	equal.data.function = equal_func;
	add(context, "==", equal);

	value_t not_equal = { { type_id::function, { { type_id::any },{ type_id::any } } } };
	not_equal.data.function = not_equal_func;
	add(context, "!=", not_equal);
}