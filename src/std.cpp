#include "std.hpp"
#include "context_methods.hpp"
#include "std/real.cpp"
#include "std/boolean.cpp"


void cuttle::vm::populate(context_t& context) {
	using namespace cuttle::vm;

	register_real(context);
	register_boolean(context);
}