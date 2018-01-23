#include <algorithm>
#include "value_methods.hpp"
#include "type_error.hpp"

bool cuttle::vm::operator==(const value_t& left, const value_t& right) {
	using namespace cuttle::vm;

	if (left.type != right.type) {
		return false;
	}

	if (left.type.children != right.type.children) {
		return false;
	}

	switch (left.type.id) {
	case type_id::function:
		return left.data.function == right.data.function;
	case type_id::array:
		return *left.data.array == *right.data.array;
	case type_id::boolean:
		return *left.data.boolean == *right.data.boolean;
	case type_id::integral:
		return *left.data.integral == *right.data.integral;
	case type_id::real:
		return std::abs(*left.data.real - *right.data.real) < std::numeric_limits<double>::epsilon() * std::max({
			*left.data.real,
			*right.data.real,
			1.0
		});
	case type_id::byte:
		return *left.data.byte == *right.data.byte;
	case type_id::string:
		return *left.data.string == *right.data.string;
	default:
		throw type_error("unknown type");
	}
}

bool cuttle::vm::operator!=(const value_t& left, const value_t& right) {
	using namespace cuttle::vm;

	return !(left == right);
}

bool cuttle::vm::operator==(const type_t& left, const type_t& right) {
	using namespace cuttle::vm;

	return left.id == right.id && left.children == right.children;
}

bool cuttle::vm::operator!=(const type_t& left, const type_t& right) {
	using namespace cuttle::vm;

	return !(left == right);
}

bool cuttle::vm::operator>=(const type_t& left, const type_t& right) {
	return left.id >= right.id || left.children >= right.children;
}

bool cuttle::vm::operator<=(const type_t& left, const type_t& right) {
	return left.id <= right.id || left.children <= right.children;
}

bool cuttle::vm::operator>(const type_t& left, const type_t& right) {
	return left.id > right.id || left.children > right.children;
}

bool cuttle::vm::operator<(const type_t& left, const type_t& right) {
	return left.id < right.id || left.children < right.children;
}