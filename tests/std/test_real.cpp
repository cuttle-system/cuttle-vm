
#define BOOST_TEST_DYN_LINK

#include <iostream>
#include <boost/test/unit_test.hpp>
#include <fstream>
#include <string>
#include "vm_context.hpp"
#include "std.hpp"
#include "std/real.cpp"

using namespace std;
using namespace cuttle::vm;

struct context_fixture {
    context_t context;

    void setup() {
        populate(context);
    }
};

BOOST_FIXTURE_TEST_SUITE(real_plus_suite, context_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
		value_t val1 = { { type_id::real },{ context.gc.add(new real_t{ 1.0 }) } };
		value_t val2 = { {type_id::real}, {context.gc.add(new real_t{ 2.0 })} };
		value_t expect = { {type_id::real}, {context.gc.add(new real_t{ 3.0 })} };
		value_t ret;

		real_plus_func(context, { val1, val2 }, ret);

		BOOST_CHECK(ret == expect);
	}

    BOOST_AUTO_TEST_CASE(case2) {
		value_t val1 = { { type_id::real },{ context.gc.add(new real_t{ 100.01 }) } };
		value_t val2 = { { type_id::real },{ context.gc.add(new real_t{ 3.002 }) } };
		value_t expect = { { type_id::real },{ context.gc.add(new real_t{ 103.012 }) } };
		value_t ret;

		real_plus_func(context, { val1, val2 }, ret);

		BOOST_CHECK(ret == expect);
	}

BOOST_AUTO_TEST_SUITE_END()


BOOST_FIXTURE_TEST_SUITE(real_minus_suite, context_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
		value_t val1 = { { type_id::real },{ context.gc.add(new real_t{ 1.0 }) } };
		value_t val2 = { { type_id::real },{ context.gc.add(new real_t{ 2.0 }) } };
		value_t expect = { { type_id::real },{ context.gc.add(new real_t{ -1.0 }) } };
		value_t ret;

		real_minus_func(context, { val1, val2 }, ret);

		BOOST_CHECK(ret == expect);
	}

    BOOST_AUTO_TEST_CASE(case2) {
		value_t val1 = { { type_id::real },{ context.gc.add(new real_t{ 100.02 }) } };
		value_t val2 = { { type_id::real },{ context.gc.add(new real_t{ 3.01 }) } };
		value_t expect = { { type_id::real },{ context.gc.add(new real_t{ 97.01 }) } };
		value_t ret;

		real_minus_func(context, { val1, val2 }, ret);

		BOOST_CHECK(ret == expect);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(real_multiply_suite, context_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
		value_t val1 = { { type_id::real },{ context.gc.add(new real_t{ 1.0 }) } };
		value_t val2 = { { type_id::real },{ context.gc.add(new real_t{ 2.1 }) } };
		value_t expect = { { type_id::real },{ context.gc.add(new real_t{ 2.1 }) } };
		value_t ret;

		real_multiply_func(context, { val1, val2 }, ret);

		BOOST_CHECK(ret == expect);
	}

    BOOST_AUTO_TEST_CASE(case2) {
		value_t val1 = { { type_id::real },{ context.gc.add(new real_t{ 100.02 }) } };
		value_t val2 = { { type_id::real },{ context.gc.add(new real_t{ 0.03 }) } };
		value_t expect = { { type_id::real },{ context.gc.add(new real_t{ 3.0006 }) } };
		value_t ret;

		real_multiply_func(context, { val1, val2 }, ret);

		BOOST_CHECK(ret == expect);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(real_divide_suite, context_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
		value_t val1 = { { type_id::real },{ context.gc.add(new real_t{ 1.0 }) } };
		value_t val2 = { { type_id::real },{ context.gc.add(new real_t{ 2.0 }) } };
		value_t expect = { { type_id::real },{ context.gc.add(new real_t{ 0.5 }) } };
		value_t ret;

		real_divide_func(context, { val1, val2 }, ret);

		BOOST_CHECK(ret == expect);
	}

    BOOST_AUTO_TEST_CASE(case2) {
		value_t val1 = { { type_id::real },{ context.gc.add(new real_t{ 29.0 }) } };
		value_t val2 = { { type_id::real },{ context.gc.add(new real_t{ 5.0 }) } };
		value_t expect = { { type_id::real },{ context.gc.add(new real_t{ 5.8 }) } };
		value_t ret;

		real_divide_func(context, { val1, val2 }, ret);

		BOOST_CHECK(ret == expect);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(string_to_real_suite, context_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
		value_t val = { { type_id::string } };
		val.data.string = context.gc.add_r(new std::string{ "3.10" });
		value_t expect = { { type_id::real },{ context.gc.add(new real_t{ 3.1 }) } };
		value_t ret;

		string_to_real_func(context, { val }, ret);

		BOOST_CHECK(ret == expect);
	}

    BOOST_AUTO_TEST_CASE(case2) {
		value_t val = { { type_id::string } };
		val.data.string = context.gc.add_r(new std::string{ "3" });
		value_t expect = { { type_id::real },{ context.gc.add(new real_t{ 3.0 }) } };
		value_t ret;

		string_to_real_func(context, { val }, ret);

		BOOST_CHECK(ret == expect);
	}

    BOOST_AUTO_TEST_CASE(case3) {
		value_t val = { { type_id::string } };
		val.data.string = context.gc.add_r(new std::string{ "ads" });
		value_t ret;

		BOOST_CHECK_THROW(string_to_real_func(context, { val }, ret), std::invalid_argument);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(integral_to_real_suite, context_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
		value_t val = { { type_id::integral } };
		val.data.integral = context.gc.add_r(new integral_t{ 3 });
		value_t expect = { { type_id::real },{ context.gc.add(new real_t{ 3.0 }) } };
		value_t ret;

		integral_to_real_func(context, { val }, ret);

		BOOST_CHECK(ret == expect);
	}

BOOST_AUTO_TEST_SUITE_END()