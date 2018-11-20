#pragma once

#include <istream>
#include <deque>
#include "vm_context.hpp"

namespace cuttle {
	namespace vm {
		void eval(std::istream &input, context_t &context, std::deque<value_t> &arg_stack);

		void interpret(std::istream &input, context_t &context, std::deque<value_t> &arg_stack);
	}
}
