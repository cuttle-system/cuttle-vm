#pragma once

#include <map>
#include "vm_value.hpp"
#include "vm_value_methods.hpp"
#include "gc.hpp"

namespace cuttle {
	namespace vm {
		using variable_types_map_t = std::map < type_t, value_t >;
		using variables_t = std::map < std::string, variable_types_map_t > ;
		struct context_t {
			 variables_t variables;
			 gc_t gc;
		};
	}
}
