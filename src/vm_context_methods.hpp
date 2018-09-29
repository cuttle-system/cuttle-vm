#pragma once

#include "vm_context.hpp"

namespace cuttle {
	namespace vm {
		void add(context_t& context, const std::string& name, value_t& value);
		const value_t& get(context_t& context, const std::string& name, const type_t& type);
		int call(
			context_t& context,
			const std::string& name,
			const std::vector<value_t>& values,
			unsigned int type_argn,
			value_t& ret
		);
	}
}