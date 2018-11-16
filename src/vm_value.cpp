#include <algorithm>
#include "vm_value_methods.hpp"
#include "type_error.hpp"
#include "vm_context.hpp"

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
		return std::abs(*left.data.real - *right.data.real) < std::numeric_limits<real_t>::epsilon() * std::max({
			*left.data.real,
			*right.data.real,
			1.0
		});
	case type_id::byte:
		return *left.data.byte == *right.data.byte;
	case type_id::string:
		return *left.data.string == *right.data.string;
	case type_id::object:
		return left.data.object == right.data.object;
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

	return (left.id == right.id || left.id == type_id::any || right.id == type_id::any) && left.children == right.children;
}

bool cuttle::vm::operator!=(const type_t& left, const type_t& right) {
	using namespace cuttle::vm;

	return !(left == right);
}

bool cuttle::vm::operator>=(const type_t& left, const type_t& right) {
	return left == right || left.id >= right.id || left.children >= right.children;
}

bool cuttle::vm::operator<=(const type_t& left, const type_t& right) {
	return left == right || left.id <= right.id || left.children <= right.children;
}

bool cuttle::vm::operator>(const type_t& left, const type_t& right) {
	return left != right && (left.id > right.id || left.children > right.children);
}

bool cuttle::vm::operator<(const type_t& left, const type_t& right) {
	return left != right && (left.id < right.id || left.children < right.children);
}

cuttle::vm::value_t cuttle::vm::copy_value(context_t &context, const value_t &value) {
	value_t copied;
	copied.type = value.type;

	switch (value.type.id) {
		case type_id::real:
			copied.data.any = context.gc.add(new real_t{*value.data.real});
			break;
		case type_id::integral:
			copied.data.any = context.gc.add(new integral_t{*value.data.integral});
			break;
		case type_id::string:
			copied.data.any = context.gc.add(new string_t{*value.data.string});
			break;
		case type_id::boolean:
			copied.data.any = context.gc.add(new boolean_t{*value.data.boolean});
			break;
		case type_id::byte:
			copied.data.any = context.gc.add(new byte_t{*value.data.byte});
			break;
		case type_id::array:
			copied.data.any = context.gc.add(new array_t{*value.data.array});
			break;
		case type_id::function:
			copied.data.function = value.data.function;
			break;
		case type_id::object:
			copied.data.object = value.data.object;
			break;
		default:
			throw type_error("can't copy type");
	}

	return copied;
}