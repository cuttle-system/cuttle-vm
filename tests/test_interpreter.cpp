#define BOOST_TEST_DYN_LINK

#include <iostream>
#include <boost/test/unit_test.hpp>
#include <sstream>
#include "interpreter.hpp"
#include "std.hpp"

using namespace std;
using namespace cuttle::vm;

struct context_fixture {
    context_t context;

    void setup() {
        populate(context);
    }
};

BOOST_FIXTURE_TEST_SUITE(can_push_back_to_stack_suite, context_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
		std::stringstream input("b r 100.0");
		std::deque<value_t> arg_stack;
		value_t val1 = value_t{ { type_id::real },{ context.gc.add(new real_t(100.0)) } };
		eval(input, context, arg_stack);
		BOOST_CHECK(arg_stack == std::deque<value_t>{val1});
	}

    BOOST_AUTO_TEST_CASE(case2) {
		std::stringstream input("b r 100.0\nb r 101.0\nb r 19.012383");
		std::deque<value_t> arg_stack;
		value_t val1 = value_t{ { type_id::real },{ context.gc.add(new real_t(100.0)) } };
		value_t val2 = value_t{ { type_id::real },{ context.gc.add(new real_t(101.0)) } };
		value_t val3 = value_t{ { type_id::real },{ context.gc.add(new real_t(19.012383)) } };
		std::deque<value_t> expected = { val1, val2, val3 };
		eval(input, context, arg_stack);
		eval(input, context, arg_stack);
		eval(input, context, arg_stack);
		BOOST_CHECK(arg_stack == expected);
	}

    BOOST_AUTO_TEST_CASE(case3) {
		std::stringstream input("b s foo \\nbar baz\\n\nb r 101.0\nb s foo bar\\nbaz\\n");
		std::deque<value_t> arg_stack;
		value_t val1 = value_t{ { type_id::string },{ context.gc.add(new std::string("foo \nbar baz\n")) } };
		value_t val2 = value_t{ { type_id::real },{ context.gc.add(new real_t(101.0)) } };
		value_t val3 = value_t{ { type_id::string },{ context.gc.add(new std::string("foo bar\nbaz\n")) } };
		std::deque<value_t> expected = { val1, val2, val3 };
		eval(input, context, arg_stack);
		eval(input, context, arg_stack);
		eval(input, context, arg_stack);
		BOOST_CHECK(arg_stack == expected);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(can_call_functions_suite, context_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
		std::stringstream input1("b r 100.0");
		std::stringstream input2("c 1 1 string");
		std::deque<value_t> arg_stack;
		value_t val1 = value_t{ { type_id::string },{ context.gc.add(new std::string("100.000000")) } };
		eval(input1, context, arg_stack);
		eval(input2, context, arg_stack);
		BOOST_CHECK(arg_stack == std::deque<value_t>{val1});
	}

    BOOST_AUTO_TEST_CASE(case2) {
		std::stringstream input("b r 100.0\nb r 101.0\nb r 19.012383\nc 1 1 string");
		std::deque<value_t> arg_stack;
		value_t val1 = value_t{ { type_id::real },{ context.gc.add(new real_t(100.0)) } };
		value_t val2 = value_t{ { type_id::real },{ context.gc.add(new real_t(101.0)) } };
		value_t val3 = value_t{ { type_id::string },{ context.gc.add(new std::string("19.012383")) } };
		std::deque<value_t> expected = { val1, val2, val3 };
		eval(input, context, arg_stack);
		eval(input, context, arg_stack);
		eval(input, context, arg_stack);
		eval(input, context, arg_stack);
		BOOST_CHECK(arg_stack == expected);
	}

    BOOST_AUTO_TEST_CASE(case3) {
		std::stringstream input("b s foo \\nbar baz\\n\nb r 101.0\nb s foo bar\\nbaz\\n");
		std::deque<value_t> arg_stack;
		value_t val1 = value_t{ { type_id::string },{ context.gc.add(new std::string("foo \nbar baz\n")) } };
		value_t val2 = value_t{ { type_id::real },{ context.gc.add(new real_t(101.0)) } };
		value_t val3 = value_t{ { type_id::string },{ context.gc.add(new std::string("foo bar\nbaz\n")) } };
		std::deque<value_t> expected = { val1, val2, val3 };
		eval(input, context, arg_stack);
		eval(input, context, arg_stack);
		eval(input, context, arg_stack);
		BOOST_CHECK(arg_stack == expected);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(can_call_functions_with_type_argn_less_than_argn_suite, context_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
		std::stringstream input1("b r 100.0");
		std::stringstream input2("b r 200.0");
		std::stringstream input3("b r 300.0");
		std::stringstream input4("c 3 0 array");
		std::deque<value_t> arg_stack;
		value_t val1 = value_t{ { type_id::array, { {type_id::real} } },
            context.gc.add(new std::vector<value_t>{
                { {type_id::real}, context.gc.add(new real_t(100.0)) },
                { {type_id::real}, context.gc.add(new real_t(200.0)) },
                { {type_id::real}, context.gc.add(new real_t(300.0)) },
		    })
		};
		eval(input1, context, arg_stack);
		eval(input2, context, arg_stack);
		eval(input3, context, arg_stack);
		eval(input4, context, arg_stack);
		BOOST_CHECK(arg_stack == std::deque<value_t>{val1});
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(can_call_void_functions, context_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
        std::stringstream input1("b s a");
        std::stringstream input2("b i 121");
        std::stringstream input3("c 2 2 setvar");
        std::stringstream input4("b s a");
        std::stringstream input5("c 1 1 getvar");
        std::deque<value_t> arg_stack;
        value_t val1 = value_t{ { type_id::integral }, context.gc.add(new integral_t(121)) };
        eval(input1, context, arg_stack);
        eval(input2, context, arg_stack);
        eval(input3, context, arg_stack);
        eval(input4, context, arg_stack);
        eval(input5, context, arg_stack);
        BOOST_CHECK(arg_stack == std::deque<value_t>{val1});
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(can_handle_gotos, context_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
        std::stringstream input("b s a\n"
                                 "l foo\n"
                                 "b i 121\n"
                                 "b b true\n"
                                 "g < foo");
        std::deque<value_t> arg_stack;
        value_t val1 = value_t{ { type_id::string }, context.gc.add(new string_t("a")) };
        value_t val2 = value_t{ { type_id::integral }, context.gc.add(new integral_t(121)) };
        value_t val3 = value_t{ { type_id::integral }, context.gc.add(new integral_t(121)) };
        std::deque<value_t> expected = { val1, val2, val3 };
        eval(input, context, arg_stack);
        eval(input, context, arg_stack);
        eval(input, context, arg_stack);
        eval(input, context, arg_stack);
        eval(input, context, arg_stack);
        eval(input, context, arg_stack);
        BOOST_CHECK(arg_stack == expected);
    }

    BOOST_AUTO_TEST_CASE(case2) {
        std::stringstream input("b b true\n"
                                "g > foo\n"
                                "b s a\n"
                                "l foo\n"
                                "b i 121");
        std::deque<value_t> arg_stack;
        value_t val1 = value_t{ { type_id::integral }, context.gc.add(new integral_t(121)) };
        std::deque<value_t> expected = { val1 };
        eval(input, context, arg_stack);
        eval(input, context, arg_stack);
        eval(input, context, arg_stack);
        BOOST_CHECK(arg_stack == expected);
    }

BOOST_AUTO_TEST_SUITE_END()