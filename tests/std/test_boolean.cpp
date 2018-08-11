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
		value_t val1 = { { type_id::real },{ context.gc.add(new real_t{ 1.0123891723 }) } };
		value_t val2 = { { type_id::real },{ context.gc.add(new real_t{ 1.0123891723 }) } };
		value_t expect = { { type_id::boolean },{ context.gc.add(new bool{ true }) } };
		value_t ret;

		equal_func(context, { val1, val2 }, ret);

		AssertEqual(ret, expect, "Return value");
	}
	{
		value_t val1 = { { type_id::real },{ context.gc.add(new real_t{ 11237891723.0123891723 }) } };
		value_t val2 = { { type_id::real },{ context.gc.add(new real_t{ 11237891723.0123891723 }) } };
		value_t expect = { { type_id::boolean },{ context.gc.add(new bool{ true }) } };
		value_t ret;

		equal_func(context, { val1, val2 }, ret);

		AssertEqual(ret, expect, "Return value");
	}
	{
		value_t val1 = { { type_id::real },{ context.gc.add(new real_t{ 192839.00011 }) } };
		value_t val2 = { { type_id::real },{ context.gc.add(new real_t{ 3.002 }) } };
		value_t expect = { { type_id::boolean },{ context.gc.add(new bool{ false }) } };
		value_t ret;

		equal_func(context, { val1, val2 }, ret);

		AssertEqual(ret, expect, "Return value");
	}
	{
		value_t val1 = { { type_id::integral },{ context.gc.add(new integral_t{ 123 }) } };
		value_t val2 = { { type_id::integral },{ context.gc.add(new integral_t{ 123 }) } };
		value_t expect = { { type_id::boolean },{ context.gc.add(new bool{ true }) } };
		value_t ret;

		equal_func(context, { val1, val2 }, ret);

		AssertEqual(ret, expect, "Return value");
	}
	{
		value_t val1 = { { type_id::integral },{ context.gc.add(new integral_t{ 123451237198732981 }) } };
		value_t val2 = { { type_id::integral },{ context.gc.add(new integral_t{ 123451237198732981 }) } };
		value_t expect = { { type_id::boolean },{ context.gc.add(new bool{ true }) } };
		value_t ret;

		equal_func(context, { val1, val2 }, ret);

		AssertEqual(ret, expect, "Return value");
	}
	{
		value_t val1 = { { type_id::integral },{ context.gc.add(new integral_t{ 12 }) } };
		value_t val2 = { { type_id::integral },{ context.gc.add(new integral_t{ 123 }) } };
		value_t expect = { { type_id::boolean },{ context.gc.add(new bool{ false }) } };
		value_t ret;

		equal_func(context, { val1, val2 }, ret);

		AssertEqual(ret, expect, "Return value");
	}
}

inline void test_not_equal() {
	using namespace cuttle::vm;

	context_t context;

	populate(context);

	{
		value_t val1 = { { type_id::real },{ context.gc.add(new real_t{ 1.0123891723 }) } };
		value_t val2 = { { type_id::real },{ context.gc.add(new real_t{ 1.0123891723 }) } };
		value_t expect = { { type_id::boolean },{ context.gc.add(new bool{ false }) } };
		value_t ret;

		not_equal_func(context, { val1, val2 }, ret);

		AssertEqual(ret, expect, "Return value");
	}
	{
		value_t val1 = { { type_id::real },{ context.gc.add(new real_t{ 1.0123891723 }) } };
		value_t val2 = { { type_id::real },{ context.gc.add(new real_t{ 1.0123891273 }) } };
		value_t expect = { { type_id::boolean },{ context.gc.add(new bool{ true }) } };
		value_t ret;

		not_equal_func(context, { val1, val2 }, ret);

		AssertEqual(ret, expect, "Return value");
	}
	{
		value_t val1 = { { type_id::integral },{ context.gc.add(new integral_t{ 12 }) } };
		value_t val2 = { { type_id::integral },{ context.gc.add(new integral_t{ 123 }) } };
		value_t expect = { { type_id::boolean },{ context.gc.add(new bool{ true }) } };
		value_t ret;

		not_equal_func(context, { val1, val2 }, ret);

		AssertEqual(ret, expect, "Return value");
	}
}

//inline void test_bigger() {
//	using namespace cuttle::vm;
//
//	context_t context;
//
//	populate(context);
//
//	{
//		value_t val1 = { { type_id::real },{ context.gc.add(new real_t{ 1.0123891723 }) } };
//		value_t val2 = { { type_id::real },{ context.gc.add(new real_t{ 1.0123891723 }) } };
//		value_t expect = { { type_id::boolean },{ context.gc.add(new bool{ false }) } };
//		value_t ret;
//
//		not_equal_func(context, { val1, val2 }, ret);
//
//		AssertEqual(ret, expect, "Return value");
//	}
//	{
//		value_t val1 = { { type_id::real },{ context.gc.add(new real_t{ 1.0123891723 }) } };
//		value_t val2 = { { type_id::real },{ context.gc.add(new real_t{ 1.0123891273 }) } };
//		value_t expect = { { type_id::boolean },{ context.gc.add(new bool{ true }) } };
//		value_t ret;
//
//		not_equal_func(context, { val1, val2 }, ret);
//
//		AssertEqual(ret, expect, "Return value");
//	}
//	{
//		value_t val1 = { { type_id::integral },{ context.gc.add(new integral_t{ 12 }) } };
//		value_t val2 = { { type_id::integral },{ context.gc.add(new integral_t{ 123 }) } };
//		value_t expect = { { type_id::boolean },{ context.gc.add(new bool{ false }) } };
//		value_t ret;
//
//		not_equal_func(context, { val1, val2 }, ret);
//
//		AssertEqual(ret, expect, "Return value");
//	}
//}
//
//inline void test_smaller() {
//	using namespace cuttle::vm;
//
//	context_t context;
//
//	populate(context);
//
//	{
//		value_t val1 = { { type_id::real },{ context.gc.add(new real_t{ 1.0123891723 }) } };
//		value_t val2 = { { type_id::real },{ context.gc.add(new real_t{ 1.0123891723 }) } };
//		value_t expect = { { type_id::boolean },{ context.gc.add(new bool{ false }) } };
//		value_t ret;
//
//		not_equal_func(context, { val1, val2 }, ret);
//
//		AssertEqual(ret, expect, "Return value");
//	}
//	{
//		value_t val1 = { { type_id::real },{ context.gc.add(new real_t{ 1.0123891723 }) } };
//		value_t val2 = { { type_id::real },{ context.gc.add(new real_t{ 1.0123891273 }) } };
//		value_t expect = { { type_id::boolean },{ context.gc.add(new bool{ true }) } };
//		value_t ret;
//
//		not_equal_func(context, { val1, val2 }, ret);
//
//		AssertEqual(ret, expect, "Return value");
//	}
//	{
//		value_t val1 = { { type_id::integral },{ context.gc.add(new integral_t{ 12 }) } };
//		value_t val2 = { { type_id::integral },{ context.gc.add(new integral_t{ 123 }) } };
//		value_t expect = { { type_id::boolean },{ context.gc.add(new bool{ false }) } };
//		value_t ret;
//
//		not_equal_func(context, { val1, val2 }, ret);
//
//		AssertEqual(ret, expect, "Return value");
//	}
//}

void run_boolean_tests() {
	TESTCASE;
	test_equal();
	test_not_equal();
	//test_bigger(); TODO
	//test_smaller();
	//test_bigger_or_equal();
	//test_smaller_or_equal();
}