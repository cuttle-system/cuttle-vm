#pragma once

#include <stdexcept>

namespace cuttle {
	namespace vm {
		class vm_error : public std::runtime_error
		{
		public:
			vm_error() : runtime_error("Unknown vm error") {}
			explicit vm_error(std::string msg) : runtime_error(msg.c_str()) {}
		};
	}
}