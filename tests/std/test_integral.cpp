
#define BOOST_TEST_DYN_LINK

#include <iostream>
#include <boost/test/unit_test.hpp>
#include <fstream>
#include <string>
#include "vm_context.hpp"
#include "std.hpp"
#include "std/integral.cpp"

using namespace std;
using namespace cuttle::vm;

struct context_fixture {
    context_t context;

    void setup() {
        populate(context);
    }
};

BOOST_FIXTURE_TEST_SUITE(integral_plus_suite, context_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
		value_t val1 = { { type_id::integral },{ context.gc.add(new integral_t{ 1 }) } };
		value_t val2 = { {type_id::integral}, {context.gc.add(new integral_t{ 2 })} };
		value_t expect = { {type_id::integral}, {context.gc.add(new integral_t{ 3 })} };
		value_t ret;

		integral_plus_func(context, { val1, val2 }, ret);

		BOOST_CHECK(ret == expect);
	}

    BOOST_AUTO_TEST_CASE(case2) {
		value_t val1 = { { type_id::integral },{ context.gc.add(new integral_t{ 100 }) } };
		value_t val2 = { { type_id::integral },{ context.gc.add(new integral_t{ 3 }) } };
		value_t expect = { { type_id::integral },{ context.gc.add(new integral_t{ 103 }) } };
		value_t ret;

		integral_plus_func(context, { val1, val2 }, ret);

		BOOST_CHECK(ret == expect);
	}

BOOST_AUTO_TEST_SUITE_END()


BOOST_FIXTURE_TEST_SUITE(integral_minus_suite, context_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
		value_t val1 = { { type_id::integral },{ context.gc.add(new integral_t{ 1 }) } };
		value_t val2 = { { type_id::integral },{ context.gc.add(new integral_t{ 2 }) } };
		value_t expect = { { type_id::integral },{ context.gc.add(new integral_t{ -1 }) } };
		value_t ret;

		integral_minus_func(context, { val1, val2 }, ret);

		BOOST_CHECK(ret == expect);
	}

    BOOST_AUTO_TEST_CASE(case2) {
		value_t val1 = { { type_id::integral },{ context.gc.add(new integral_t{ 100 }) } };
		value_t val2 = { { type_id::integral },{ context.gc.add(new integral_t{ 3 }) } };
		value_t expect = { { type_id::integral },{ context.gc.add(new integral_t{ 97 }) } };
		value_t ret;

		integral_minus_func(context, { val1, val2 }, ret);

		BOOST_CHECK(ret == expect);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(integral_multiply_suite, context_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
		value_t val1 = { { type_id::integral },{ context.gc.add(new integral_t{ 1 }) } };
		value_t val2 = { { type_id::integral },{ context.gc.add(new integral_t{ 2 }) } };
		value_t expect = { { type_id::integral },{ context.gc.add(new integral_t{ 2 }) } };
		value_t ret;

		integral_multiply_func(context, { val1, val2 }, ret);

		BOOST_CHECK(ret == expect);
	}

    BOOST_AUTO_TEST_CASE(case2) {
		value_t val1 = { { type_id::integral },{ context.gc.add(new integral_t{ 100 }) } };
		value_t val2 = { { type_id::integral },{ context.gc.add(new integral_t{ 0 }) } };
		value_t expect = { { type_id::integral },{ context.gc.add(new integral_t{ 0 }) } };
		value_t ret;

		integral_multiply_func(context, { val1, val2 }, ret);

		BOOST_CHECK(ret == expect);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(integral_divide_suite, context_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
		value_t val1 = { { type_id::integral },{ context.gc.add(new integral_t{ 1 }) } };
		value_t val2 = { { type_id::integral },{ context.gc.add(new integral_t{ 2 }) } };
		value_t expect = { { type_id::integral },{ context.gc.add(new integral_t{ 0 }) } };
		value_t ret;

		integral_divide_func(context, { val1, val2 }, ret);

		BOOST_CHECK(ret == expect);
	}

    BOOST_AUTO_TEST_CASE(case2) {
		value_t val1 = { { type_id::integral },{ context.gc.add(new integral_t{ 29 }) } };
		value_t val2 = { { type_id::integral },{ context.gc.add(new integral_t{ 5 }) } };
		value_t expect = { { type_id::integral },{ context.gc.add(new integral_t{ 5 }) } };
		value_t ret;

		integral_divide_func(context, { val1, val2 }, ret);

		BOOST_CHECK(ret == expect);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(string_to_integral_suite, context_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
		value_t val = { { type_id::string } };
		val.data.string = context.gc.add_r(new std::string{ "31" });
		value_t expect = { { type_id::integral },{ context.gc.add(new integral_t{ 31 }) } };
		value_t ret;

		string_to_integral_func(context, { val }, ret);

		BOOST_CHECK(ret == expect);
	}

    BOOST_AUTO_TEST_CASE(case2) {
		value_t val = { { type_id::string } };
		val.data.string = context.gc.add_r(new std::string{ "3" });
		value_t expect = { { type_id::integral },{ context.gc.add(new integral_t{ 3 }) } };
		value_t ret;

		string_to_integral_func(context, { val }, ret);

		BOOST_CHECK(ret == expect);
	}

    BOOST_AUTO_TEST_CASE(case3) {
		value_t val = { { type_id::string } };
		val.data.string = context.gc.add_r(new std::string{ "ads" });
		value_t ret;

		BOOST_CHECK_THROW(string_to_integral_func(context, { val }, ret), std::invalid_argument);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(real_to_integral_suite, context_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
		value_t val = { { type_id::integral } };
		val.data.real = context.gc.add_r(new real_t{ 3.21 });
		value_t expect = { { type_id::integral },{ context.gc.add(new integral_t{ 3 }) } };
		value_t ret;

		real_to_integral_func(context, { val }, ret);

		BOOST_CHECK(ret == expect);
	}

BOOST_AUTO_TEST_SUITE_END()