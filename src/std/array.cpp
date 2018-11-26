#include <algorithm>
#include "vm_context_methods.hpp"
#include "vm_value_methods.hpp"

using namespace cuttle::vm;

std::vector<type_t> array_construct_type_children(const std::vector<value_t>& args) {
    long i;
    std::vector<type_t> children;

    for (i = args.size() - 2; i >= 0; --i) {
        if (args[i + 1].type != args[i].type) {
            children.push_back(args[i + 1].type);
            break;
        }
    }
    for (; i >= 0; --i) children.push_back(args[i].type);

    if (children.empty() && !args.empty()) {
        children.push_back(args[0].type);
    }

    std::reverse(children.begin(), children.end());
    return children;
}

int array_func(context_t& context, const std::vector<value_t>& args, value_t& ret) {
    std::vector<value_t> *value = context.gc.add_r(
        new std::vector<value_t>(args)
    );
    ret = { { type_id::array, array_construct_type_children(args) },{ (real_t *) value } };
    return 0;
}

int get_func(context_t& context, const std::vector<value_t>& args, value_t& ret) {
    ret = copy_value(context, (*args[0].data.array)[*args[1].data.integral]);
    return 0;
}

void register_array(context_t& context) {
    value_t array = { { type_id::function } };
    array.data.function = array_func;
    add(context, "array", array);

    value_t get = { { type_id::function, {{type_id::any}, {type_id::integral}} } };
    get.data.function = get_func;
    add(context, "get_element", get);
}