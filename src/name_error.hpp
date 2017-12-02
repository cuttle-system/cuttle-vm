#pragma once

#include <stdexcept>

namespace cuttle {
	namespace vm {
		class name_error : public std::runtime_error
		{
		public:
			name_error() : runtime_error("Unknown name error") {}
			name_error(std::string msg) : runtime_error(msg.c_str()) {}
		};
	}
}