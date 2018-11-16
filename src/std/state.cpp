#include "vm_context_methods.hpp"
#include "vm_value_methods.hpp"

using namespace cuttle::vm;

int setvar_func(context_t& context, const std::vector<value_t>& args, value_t& ret) {
    value_t value = copy_value(context, args[1]);
    add(context, *args[0].data.string, value);
	ret = { { type_id::nothing },{ nullptr } };
	return 0;
}

int getvar_func(context_t& context, const std::vector<value_t>& args, value_t& ret) {
	const auto &value = get(context, *args[0].data.string, { type_id::any });
	ret = copy_value(context, value);
	return 0;
}

void register_state(context_t& context) {
	value_t setvar = { { type_id::function, { { type_id::string }, { type_id::any } } } };
	setvar.data.function = setvar_func;
	add(context, "setvar", setvar);

	value_t getvar = { { type_id::function, { { type_id::string } } } };
	getvar.data.function = getvar_func;
	add(context, "getvar", getvar);
}