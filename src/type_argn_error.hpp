#pragma once

#include "vm_error.hpp"

namespace cuttle {
	namespace vm {
		class type_argn_error : public vm_error {
		public:
			type_argn_error() : vm_error("Unknown type_argn error") {}
			explicit type_argn_error(const std::string &msg) : vm_error(msg) {}
		};
	}
}