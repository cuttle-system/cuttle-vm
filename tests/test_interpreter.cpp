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
	{
		std::stringstream input("b s foo \\nbar baz\\n\nb r 101.0\nb s foo bar\\nbaz\\n");
		std::deque<value_t> arg_stack;
		value_t val1 = value_t{ { type_id::string },{ (double *)context.gc.add(new std::string("foo \nbar baz\n")) } };
		value_t val2 = value_t{ { type_id::real },{ context.gc.add(new double(101.0)) } };
		value_t val3 = value_t{ { type_id::string },{ (double *) context.gc.add(new std::string("foo bar\nbaz\n")) } };
		std::deque<value_t> expected = { val1, val2, val3 };
		eval(input, context, arg_stack);
		eval(input, context, arg_stack);
		eval(input, context, arg_stack);
		AssertEqual(arg_stack, expected, "Argument stack");
	}
}

inline void test_can_call_functions() {
	using namespace cuttle::vm;

	context_t context;
	populate(context);

	{
		std::stringstream input1("b r 100.0");
		std::stringstream input2("c 1 string");
		std::deque<value_t> arg_stack;
		value_t val1 = value_t{ { type_id::string },{ (double *) context.gc.add(new std::string("100.000000")) } };
		eval(input1, context, arg_stack);
		eval(input2, context, arg_stack);
		AssertEqual(arg_stack, std::deque<value_t>{val1}, "Argument stack");
	}
	{
		std::stringstream input("b r 100.0\nb r 101.0\nb r 19.012383\nc 1 string");
		std::deque<value_t> arg_stack;
		value_t val1 = value_t{ { type_id::real },{ context.gc.add(new double(100.0)) } };
		value_t val2 = value_t{ { type_id::real },{ context.gc.add(new double(101.0)) } };
		value_t val3 = value_t{ { type_id::string },{ (double *) context.gc.add(new std::string("19.012383")) } };
		std::deque<value_t> expected = { val1, val2, val3 };
		eval(input, context, arg_stack);
		eval(input, context, arg_stack);
		eval(input, context, arg_stack);
		eval(input, context, arg_stack);
		AssertEqual(arg_stack, expected, "Argument stack");
	}
	{
		std::stringstream input("b s foo \\nbar baz\\n\nb r 101.0\nb s foo bar\\nbaz\\n");
		std::deque<value_t> arg_stack;
		value_t val1 = value_t{ { type_id::string },{ (double *)context.gc.add(new std::string("foo \nbar baz\n")) } };
		value_t val2 = value_t{ { type_id::real },{ context.gc.add(new double(101.0)) } };
		value_t val3 = value_t{ { type_id::string },{ (double *)context.gc.add(new std::string("foo bar\nbaz\n")) } };
		std::deque<value_t> expected = { val1, val2, val3 };
		eval(input, context, arg_stack);
		eval(input, context, arg_stack);
		eval(input, context, arg_stack);
		AssertEqual(arg_stack, expected, "Argument stack");
	}
}

void run_interpreter_tests() {
    TESTCASE
    test_can_push_back_to_stack();
	test_can_call_functions();
}