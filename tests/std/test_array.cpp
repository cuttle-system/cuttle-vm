#include <iostream>
#include <fstream>
#include <string>
#include "test.hpp"
#include "test_array.hpp"
#include "context.hpp"
#include "std.hpp"
#include "std/array.cpp"

using namespace std;

inline void test_array_creates_new_array_from_passed_args() {
	using namespace cuttle::vm;

	context_t context;

	populate(context);

//	{
//		value_t val1 = { { type_id::real },{ context.gc.add(new std::vector<value_t>{ 1.0123891723 }) } };
//		value_t val2 = { { type_id::real },{ context.gc.add(new std::vector<value_t>{ 1.0123891723 }) } };
//		value_t expect = { { type_id::boolean },{ (double *) context.gc.add(new bool{ true }) } };
//		value_t ret;
//
//		equal_func(context, { val1, val2 }, ret);
//
//		AssertEqual(ret, expect, "Return value");
//	}
}

void run_array_tests() {
	TESTCASE;
    test_array_creates_new_array_from_passed_args();
}