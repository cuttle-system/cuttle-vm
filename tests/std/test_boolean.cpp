#define BOOST_TEST_DYN_LINK

#include <iostream>
#include <boost/test/unit_test.hpp>
#include <fstream>
#include <string>
#include "context.hpp"
#include "std.hpp"
#include "std/boolean.cpp"

using namespace std;
using namespace cuttle::vm;

struct context_fixture {
    context_t context;

    void setup() {
        populate(context);
    }
};

BOOST_FIXTURE_TEST_SUITE(equal_suite, context_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
        value_t val1 = { { type_id::real },{ context.gc.add(new real_t{ 1.0123891723 }) } };
		value_t val2 = { { type_id::real },{ context.gc.add(new real_t{ 1.0123891723 }) } };
		value_t expect = { { type_id::boolean },{ context.gc.add(new bool{ true }) } };
		value_t ret;

		equal_func(context, { val1, val2 }, ret);

		BOOST_CHECK(ret == expect);
	}

    BOOST_AUTO_TEST_CASE(case2) {
		value_t val1 = { { type_id::real },{ context.gc.add(new real_t{ 11237891723.0123891723 }) } };
		value_t val2 = { { type_id::real },{ context.gc.add(new real_t{ 11237891723.0123891723 }) } };
		value_t expect = { { type_id::boolean },{ context.gc.add(new bool{ true }) } };
		value_t ret;

		equal_func(context, { val1, val2 }, ret);

		BOOST_CHECK(ret == expect);
	}

    BOOST_AUTO_TEST_CASE(case3) {
		value_t val1 = { { type_id::real },{ context.gc.add(new real_t{ 192839.00011 }) } };
		value_t val2 = { { type_id::real },{ context.gc.add(new real_t{ 3.002 }) } };
		value_t expect = { { type_id::boolean },{ context.gc.add(new bool{ false }) } };
		value_t ret;

		equal_func(context, { val1, val2 }, ret);

		BOOST_CHECK(ret == expect);
	}

    BOOST_AUTO_TEST_CASE(case4) {
		value_t val1 = { { type_id::integral },{ context.gc.add(new integral_t{ 123 }) } };
		value_t val2 = { { type_id::integral },{ context.gc.add(new integral_t{ 123 }) } };
		value_t expect = { { type_id::boolean },{ context.gc.add(new bool{ true }) } };
		value_t ret;

		equal_func(context, { val1, val2 }, ret);

		BOOST_CHECK(ret == expect);
	}

    BOOST_AUTO_TEST_CASE(case5) {
		value_t val1 = { { type_id::integral },{ context.gc.add(new integral_t{ 123451237198732981 }) } };
		value_t val2 = { { type_id::integral },{ context.gc.add(new integral_t{ 123451237198732981 }) } };
		value_t expect = { { type_id::boolean },{ context.gc.add(new bool{ true }) } };
		value_t ret;

		equal_func(context, { val1, val2 }, ret);

		BOOST_CHECK(ret == expect);
	}

    BOOST_AUTO_TEST_CASE(case6) {
		value_t val1 = { { type_id::integral },{ context.gc.add(new integral_t{ 12 }) } };
		value_t val2 = { { type_id::integral },{ context.gc.add(new integral_t{ 123 }) } };
		value_t expect = { { type_id::boolean },{ context.gc.add(new bool{ false }) } };
		value_t ret;

		equal_func(context, { val1, val2 }, ret);

		BOOST_CHECK(ret == expect);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(not_equal_suite, context_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
		value_t val1 = { { type_id::real },{ context.gc.add(new real_t{ 1.0123891723 }) } };
		value_t val2 = { { type_id::real },{ context.gc.add(new real_t{ 1.0123891723 }) } };
		value_t expect = { { type_id::boolean },{ context.gc.add(new bool{ false }) } };
		value_t ret;

		not_equal_func(context, { val1, val2 }, ret);

		BOOST_CHECK(ret == expect);
	}

    BOOST_AUTO_TEST_CASE(case2) {
		value_t val1 = { { type_id::real },{ context.gc.add(new real_t{ 1.0123891723 }) } };
		value_t val2 = { { type_id::real },{ context.gc.add(new real_t{ 1.0123891273 }) } };
		value_t expect = { { type_id::boolean },{ context.gc.add(new bool{ true }) } };
		value_t ret;

		not_equal_func(context, { val1, val2 }, ret);

		BOOST_CHECK(ret == expect);
	}

    BOOST_AUTO_TEST_CASE(case3) {
		value_t val1 = { { type_id::integral },{ context.gc.add(new integral_t{ 12 }) } };
		value_t val2 = { { type_id::integral },{ context.gc.add(new integral_t{ 123 }) } };
		value_t expect = { { type_id::boolean },{ context.gc.add(new bool{ true }) } };
		value_t ret;

		not_equal_func(context, { val1, val2 }, ret);

		BOOST_CHECK(ret == expect);
	}

BOOST_AUTO_TEST_SUITE_END()

//BOOST_FIXTURE_TEST_SUITE(bigger_suite, context_fixture)
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
//		BOOST_CHECK(ret == expect);
//	}
//	{
//		value_t val1 = { { type_id::real },{ context.gc.add(new real_t{ 1.0123891723 }) } };
//		value_t val2 = { { type_id::real },{ context.gc.add(new real_t{ 1.0123891273 }) } };
//		value_t expect = { { type_id::boolean },{ context.gc.add(new bool{ true }) } };
//		value_t ret;
//
//		not_equal_func(context, { val1, val2 }, ret);
//
//		BOOST_CHECK(ret == expect);
//	}
//	{
//		value_t val1 = { { type_id::integral },{ context.gc.add(new integral_t{ 12 }) } };
//		value_t val2 = { { type_id::integral },{ context.gc.add(new integral_t{ 123 }) } };
//		value_t expect = { { type_id::boolean },{ context.gc.add(new bool{ false }) } };
//		value_t ret;
//
//		not_equal_func(context, { val1, val2 }, ret);
//
//		BOOST_CHECK(ret == expect);
//	}
//}
//
//BOOST_FIXTURE_TEST_SUITE(smaller_suite, context_fixture)
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
//		BOOST_CHECK(ret == expect);
//	}
//	{
//		value_t val1 = { { type_id::real },{ context.gc.add(new real_t{ 1.0123891723 }) } };
//		value_t val2 = { { type_id::real },{ context.gc.add(new real_t{ 1.0123891273 }) } };
//		value_t expect = { { type_id::boolean },{ context.gc.add(new bool{ true }) } };
//		value_t ret;
//
//		not_equal_func(context, { val1, val2 }, ret);
//
//		BOOST_CHECK(ret == expect);
//	}
//	{
//		value_t val1 = { { type_id::integral },{ context.gc.add(new integral_t{ 12 }) } };
//		value_t val2 = { { type_id::integral },{ context.gc.add(new integral_t{ 123 }) } };
//		value_t expect = { { type_id::boolean },{ context.gc.add(new bool{ false }) } };
//		value_t ret;
//
//		not_equal_func(context, { val1, val2 }, ret);
//
//		BOOST_CHECK(ret == expect);
//	}
//}