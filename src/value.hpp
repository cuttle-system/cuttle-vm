#pragma once

#include <string>
#include <vector>
#include "function.hpp"
#include "type_error.hpp"

namespace cuttle {
	namespace vm {
		struct value_t;

		union data {
			double *real = nullptr;
			long long *integral;
			std::string *string;
			bool *boolean;
			char *byte;
			std::vector<value_t> *array;
			function_ptr_t *function;
		};

		enum class type_id {
			real,
			integral,
			string,
			boolean,
			byte,
			array,
			function,
			any
		};

		struct type_t {
			type_id id;
			std::vector<type_t> children = {};
		};

		struct value_t {
			type_t type;
			union data data = {nullptr};
		};
	}
}