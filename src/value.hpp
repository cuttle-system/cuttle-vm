#pragma once

#include <string>
#include <vector>
#include "function.hpp"
#include "type_error.hpp"

namespace cuttle {
	namespace vm {
		struct value;

		union data {
			double *real;
			int *integral;
			std::string *string;
			bool *boolean;
			char *byte;
			std::vector<struct value> *array;
			function_ptr_t *function;
		};

		enum class type_id {
			real,
			integral,
			string,
			boolean,
			byte,
			array,
			function
		};

		using type_t = struct type {
			type_id id;
			std::vector<struct type> children;
		};

		using value_t = struct value {
			type_t type;
			union data data;
		};
	}
}