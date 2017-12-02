#pragma once

#include <map>
#include "value.hpp"
#include "value_methods.hpp"
#include "gc.hpp"

namespace cuttle {
	namespace vm {
		using variable_types_map_t = std::map < type_t, value_t >;
		using variables_t = std::map < std::string, variable_types_map_t > ;
		using context_t = struct context {
			 variables_t variables;
			 gc gc;
		};
	}
}