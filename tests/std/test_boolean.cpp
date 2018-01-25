#include <iostream>
#include <fstream>
#include <string>
#include "test.hpp"
#include "test_real.hpp"
#include "context.hpp"
#include "std.hpp"
#include "std/boolean.cpp"

using namespace std;

inline void test_equal() {
	using namespace cuttle::vm;

	context_t context;

	populate(context);

	{
		value_t val1 = { { type_id::real },{ context.gc.add(new double{ 1.0123891723 }) } };
		value_t val2 = { { type_id::real },{ context.gc.add(new double{ 1.0123891723 }) } };
		value_t expect = { { type_id::boolean },{ (double *) context.gc.add(new bool{ true }) } };
		value_t ret;

		equal_func(context, { val1, val2 }, ret);

		AssertEqual(ret, expect, "Return value");
	}
	{
		value_t val1 = { { type_id::real },{ context.gc.add(new double{ 11237891723.0123891723 }) } };
		value_t val2 = { { type_id::real },{ context.gc.add(new double{ 11237891723.0123891723 }) } };
		value_t expect = { { type_id::boolean },{ (double *)context.gc.add(new bool{ true }) } };
		value_t ret;

		equal_func(context, { val1, val2 }, ret);

		AssertEqual(ret, expect, "Return value");
	}
	{
		value_t val1 = { { type_id::real },{ context.gc.add(new double{ 192839.00011 }) } };
		value_t val2 = { { type_id::real },{ context.gc.add(new double{ 3.002 }) } };
		value_t expect = { { type_id::boolean },{ (double *) context.gc.add(new bool{ false }) } };
		value_t ret;

		equal_func(context, { val1, val2 }, ret);

		AssertEqual(ret, expect, "Return value");
	}
	{
		value_t val1 = { { type_id::integral },{ (double *) context.gc.add(new long long{ 123 }) } };
		value_t val2 = { { type_id::integral },{ (double *) context.gc.add(new long long{ 123 }) } };
		value_t expect = { { type_id::boolean },{ (double *)context.gc.add(new bool{ true }) } };
		value_t ret;

		equal_func(context, { val1, val2 }, ret);

		AssertEqual(ret, expect, "Return value");
	}
	{
		value_t val1 = { { type_id::integral },{ (double *)context.gc.add(new long long{ 123451237198732981 }) } };
		value_t val2 = { { type_id::integral },{ (double *)context.gc.add(new long long{ 123451237198732981 }) } };
		value_t expect = { { type_id::boolean },{ (double *)context.gc.add(new bool{ true }) } };
		value_t ret;

		equal_func(context, { val1, val2 }, ret);

		AssertEqual(ret, expect, "Return value");
	}
	{
		value_t val1 = { { type_id::integral },{ (double *)context.gc.add(new long long{ 12 }) } };
		value_t val2 = { { type_id::integral },{ (double *)context.gc.add(new long long{ 123 }) } };
		value_t expect = { { type_id::boolean },{ (double *)context.gc.add(new bool{ false }) } };
		value_t ret;

		equal_func(context, { val1, val2 }, ret);

		AssertEqual(ret, expect, "Return value");
	}
}

void run_boolean_tests() {
	TESTCASE;
	test_equal();
}