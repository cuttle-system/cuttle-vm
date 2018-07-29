#pragma once

#include "vm_error.hpp"

namespace cuttle {
    namespace vm {
        class parse_error : public vm_error
        {
        public:
            parse_error() : vm_error("Unknown parse error") {}
            explicit parse_error(const std::string& msg) : vm_error(msg) {}
        };
    }
}