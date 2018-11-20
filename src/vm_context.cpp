#include "vm_context_methods.hpp"
#include "name_error.hpp"
#include "type_argn_error.hpp"

void cuttle::vm::add(context_t& context, const std::string& name, value_t& value) {
	using namespace cuttle::vm;

	if (context.variables.count(name) == 0) {
		context.variables[name] = {};
	}

	context.variables[name][value.type] = value;
}

const cuttle::vm::value_t& cuttle::vm::get(context_t& context, const std::string& name, const type_t& type) {
	context_t *current = &context;
	while (true) {
		if (!current->parent && (current->variables.count(name) == 0 || current->variables[name].count(type) == 0)) {
			throw name_error("variable '" + name + "' not found");
		} else if (current->parent) {
			current = current->parent;
		} else {
			break;
		}
	}
	return current->variables[name][type];
}

int cuttle::vm::call(
    context_t& context,
    const std::string& name,
    const std::vector<value_t>& values,
    unsigned int type_argn,
    value_t& ret
) {
    if (type_argn > values.size()) {
        throw type_argn_error("The type_argn is invalid for the values array passed");
    }
	std::vector<type_t> arg_types(type_argn, type_t());
	for (unsigned int i = 0; i < type_argn; ++i) {
		arg_types[i] = values[i].type;
	}
	auto func = get(context, name, { type_id::function, arg_types});
	return func.data.function(context, values, ret);
}