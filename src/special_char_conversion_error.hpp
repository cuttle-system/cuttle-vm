#pragma once

#include "vm_error.hpp"

namespace cuttle {
	namespace vm {
		class special_char_conversion_error : public vm_error {
		public:
			special_char_conversion_error() : vm_error("Unknown special character conversion error") {}
			special_char_conversion_error(std::string msg) : vm_error(msg.c_str()) {}
		};
	}
}