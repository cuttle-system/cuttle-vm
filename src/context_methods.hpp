#pragma once

#include "context.hpp"

namespace cuttle {
	namespace vm {
		void add(context_t& context, const std::string& name, value_t& value);
		const value_t& get(context_t& context, const std::string& name, const type_t& type);
	}
}