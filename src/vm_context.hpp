#pragma once

#include <map>
#include <list>
#include <istream>
#include "vm_value.hpp"
#include "vm_value_methods.hpp"
#include "gc.hpp"

#define CUTTLE_GLOBAL_CONTEXT_NAME "__cuttle_global_context_name"
#define CUTTLE_UNDEFINED_VARIABLE_NAME "__cuttle_undefined_variable_name"

namespace cuttle {
    namespace vm {
        using variable_types_map_t = std::map<type_t, value_t>;
        using variables_t = std::map<std::string, variable_types_map_t>;
        using registers_t = std::list<std::string>;
        using labels_t = std::map<std::string, std::ios::pos_type>;
        struct context_t {
            context_t *parent = nullptr;
            registers_t registers;
            labels_t labels;
            variables_t variables;
            gc_t gc;
        };
    }
}
