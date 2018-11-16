#include "std.hpp"
#include "vm_context_methods.hpp"
#include "std/real.cpp"
#include "std/boolean.cpp"
#include "std/string.cpp"
#include "std/array.cpp"
#include "std/integral.cpp"
#include "std/state.cpp"

void cuttle::vm::populate(context_t& context) {
	using namespace cuttle::vm;

	register_real(context);
	register_boolean(context);
	register_string(context);
	register_array(context);
	register_integral(context);
	register_state(context);
}