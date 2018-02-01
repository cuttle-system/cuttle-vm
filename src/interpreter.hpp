#pragma once

#include <sstream>
#include <deque>
#include "context.hpp"

namespace cuttle {
	namespace vm {
		void eval(std::stringstream &input, context_t &context, std::deque<value_t> &arg_stack);
	}
}
