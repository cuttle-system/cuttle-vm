#pragma once

#include "vm_error.hpp"

namespace cuttle {
	namespace vm {
		class type_error : public vm_error
		{
		public:
			type_error() : vm_error("Unknown type error") {}
			type_error(std::string msg) : vm_error(msg.c_str()) {}
		};
	}
}