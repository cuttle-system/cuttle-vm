#include <iostream>
#include <sstream>
#include "test.hpp"
#include "interpreter.hpp"
#include "std.hpp"
#include "test_interpreter.hpp"

using namespace std;

inline void test_can_push_back_to_stack() {
	using namespace cuttle::vm;

	context_t context;
	populate(context);

	{
		std::stringstream input("b r 100.0");
		std::deque<value_t> arg_stack;
		value_t val1 = value_t{ { type_id::real },{ context.gc.add(new double(100.0)) } };
		eval(input, context, arg_stack);
		AssertEqual(arg_stack, std::deque<value_t>{val1}, "Argument stack");
		
	}
	{
		std::stringstream input("b r 100.0\nb r 101.0\nb r 19.012383");
		std::deque<value_t> arg_stack;
		value_t val1 = value_t{ { type_id::real },{ context.gc.add(new double(100.0)) } };
		value_t val2 = value_t{ { type_id::real },{ context.gc.add(new double(101.0)) } };
		value_t val3 = value_t{ { type_id::real },{ context.gc.add(new double(19.012383)) } };
		std::deque<value_t> expected = { val1, val2, val3 };
		eval(input, context, arg_stack);
		eval(input, context, arg_stack);
		eval(input, context, arg_stack);
		AssertEqual(arg_stack, expected, "Argument stack");

	}
	//{ // TODO string test. strings can have special symbols
	//	std::stringstream input("b r 100.0\nb r 101.0\nb r 19.012383");
	//	std::deque<value_t> arg_stack;
	//	value_t val1 = value_t{ { type_id::real },{ context.gc.add(new double(100.0)) } };
	//	value_t val2 = value_t{ { type_id::real },{ context.gc.add(new double(101.0)) } };
	//	value_t val3 = value_t{ { type_id::real },{ context.gc.add(new double(19.012383)) } };
	//	std::deque<value_t> expected = { val1, val2, val3 };
	//	eval(input, context, arg_stack);
	//	eval(input, context, arg_stack);
	//	eval(input, context, arg_stack);
	//	AssertEqual(arg_stack, expected, "Argument stack");

	//}
}

void run_interpreter_tests() {
    TESTCASE
    test_can_push_back_to_stack();
}