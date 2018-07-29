#pragma once

#include <vector>
#include "value.hpp"

namespace cuttle {
	namespace vm {
		struct context;
		struct value_t;

		using function_ptr_t = int(context& context, const std::vector<value_t>& args, value_t& ret);
	}
}