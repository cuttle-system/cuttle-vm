#pragma once

#include "vm_value.hpp"

namespace cuttle {
	namespace vm {
		bool operator==(const value_t& left, const value_t& right);
		bool operator!=(const value_t& left, const value_t& right);
		
		bool operator==(const type_t& left, const type_t& right);
		bool operator!=(const type_t& left, const type_t& right);

		bool operator>=(const type_t& left, const type_t& right);
		bool operator<=(const type_t& left, const type_t& right);
		bool operator>(const type_t& left, const type_t& right);
		bool operator<(const type_t& left, const type_t& right);
	}
}