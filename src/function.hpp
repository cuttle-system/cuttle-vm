#pragma once

#include <vector>

namespace cuttle {
	namespace vm {
		struct context;
		struct value;

		using function_ptr_t = int(struct context& context, const std::vector<struct value>& args, struct value& ret);
	}
}