#pragma once

#include <string>
#include <vector>
#include "vm_function.hpp"
#include "type_error.hpp"

#define VALUE_GCC_SUPPORTED_TYPES \
	real_t, integral_t, string_t, boolean_t, byte_t, array_t

namespace cuttle {
	namespace vm {
		using any_t = void;
		using real_t = double;
		using integral_t = long long;
		using string_t = std::string;
		using boolean_t = bool;
		using byte_t = char;
		using array_t = std::vector<value_t>;
		using function_t = function_ptr_t;
		using object_t = void *;

		struct value_t;

		union data_t {
			any_t *any = nullptr;
			real_t *real;
			integral_t *integral;
			std::string *string;
			bool *boolean;
			char *byte;
			std::vector<value_t> *array;
			function_ptr_t *function;
			object_t object;
		};

		enum type_id {
			nothing,
			any,
			real,
			integral,
			string,
			boolean,
			byte,
			array,
			function,
			object
		};

		/*
		 * Note: type children can't be type_id::any because then they can't be found by an implemented context_t structure.
		 * Also, the runtime check will have too big impact on performance, so it is not implemented
		 */
		struct type_t {
			type_id id;
			std::vector<type_t> children = {};
		};

		struct value_t {
			type_t type;
			union data_t data = {};
		};
	}
}