#pragma once

#include <map>
#include <list>
#include <istream>
#include "vm_value.hpp"
#include "vm_value_methods.hpp"
#include "gc.hpp"

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
