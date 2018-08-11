#pragma once

#include "vm_error.hpp"
#include <typeindex>

namespace cuttle {
    namespace vm {
        class gc_type_error : public vm_error
        {
        public:
            gc_type_error() : vm_error("Can't clear pointer of unknown type") {}
            explicit gc_type_error(const std::type_index& type)
                : vm_error(std::string("Can't clear pointer of type: ") + type.name()) {}
        };
    }
}