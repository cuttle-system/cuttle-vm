#pragma once

#include <stdexcept>

namespace cuttle {
	namespace vm {
		class name_error : public std::runtime_error
		{
		public:
			name_error() : runtime_error("Unknown name error") {}
            explicit name_error(const std::string& msg) : runtime_error(msg) {}
		};
	}
}