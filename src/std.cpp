#include "std.hpp"
#include "context_methods.hpp"
#include "std/real.cpp"


void cuttle::vm::populate(context_t& context) {
	using namespace cuttle::vm;

	register_real(context);

//#include "std/int.cpp"

	//add(context, "+", integral_plus_func);
	//add(context, "int", real_to_integral_func);
	//add(context, "int", string_to_integral_func);
	//add(context, "int", _to_integral_func);

	// 
}