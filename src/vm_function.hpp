#pragma once

#include <vector>
#include "vm_value.hpp"

namespace cuttle {
	namespace vm {
		struct context_t;
		struct value_t;

		using function_ptr_t = int(context_t& context, const std::vector<value_t>& args, value_t& ret);
	}
}