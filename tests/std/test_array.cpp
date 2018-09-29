#define BOOST_TEST_DYN_LINK

#include <iostream>
#include <boost/test/unit_test.hpp>
#include <fstream>
#include <string>
#include "vm_context.hpp"
#include "std.hpp"
#include "std/array.cpp"

using namespace std;
using namespace cuttle::vm;

struct context_fixture {
    context_t context;

    void setup() {
        populate(context);
    }
};

BOOST_FIXTURE_TEST_SUITE(array_construct_type_children_works_properly_with_empty_or_one_args_suite, context_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
        std::vector<value_t> args;
        std::vector<type_t> expect;
        auto ret = array_construct_type_children(args);

        BOOST_CHECK(ret == expect);
    }

    BOOST_AUTO_TEST_CASE(case2) {
        std::vector<value_t> args { { {type_id::real}, context.gc.add(new real_t {1238912.1239})} };
        std::vector<type_t> expect = { {type_id::real } };
        auto ret = array_construct_type_children(args);

        BOOST_CHECK(ret == expect);
    }

    BOOST_AUTO_TEST_CASE(case3) {
        std::vector<value_t> args { { {type_id::boolean}, context.gc.add((real_t *)new bool {true})} };
        std::vector<type_t> expect = { {type_id::boolean } };
        auto ret = array_construct_type_children(args);

        BOOST_CHECK(ret == expect);
    }

    BOOST_AUTO_TEST_CASE(case4) {
        std::vector<value_t> args { { {type_id::integral}, context.gc.add((real_t *)new integral_t {3ll})} };
        std::vector<type_t> expect = { {type_id::integral } };
        auto ret = array_construct_type_children(args);

        BOOST_CHECK(ret == expect);
    }

    BOOST_AUTO_TEST_CASE(case5) {
        std::vector<value_t> args { { {type_id::string}, context.gc.add((real_t *)new std::string("foo"))} };
        std::vector<type_t> expect = { {type_id::string} };
        auto ret = array_construct_type_children(args);

        BOOST_CHECK(ret == expect);
    }

    BOOST_AUTO_TEST_CASE(case6) {
        std::vector<value_t> args { { {type_id::array}, context.gc.add((real_t *)new std::vector<value_t>)} };
        std::vector<type_t> expect = { {type_id::array} };
        auto ret = array_construct_type_children(args);

        BOOST_CHECK(ret == expect);
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(array_construct_type_children_works_properly_with_two_or_more_args_suite, context_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
        value_t arg1 = { {type_id::real}, context.gc.add(new real_t {1238912.1239})};
        value_t arg2 = { {type_id::real}, context.gc.add(new real_t {123812312.100})};
        value_t arg3 = { {type_id::real}, context.gc.add(new real_t {122.15639})};
        std::vector<type_t> expect = { {type_id::real} };
        auto ret = array_construct_type_children({ arg1, arg2, arg3 });

        BOOST_CHECK(ret == expect);
    }

    BOOST_AUTO_TEST_CASE(case2) {
        value_t arg1 = { {type_id::real}, context.gc.add(new real_t {1238912.1239})};
        value_t arg2 = { {type_id::real}, context.gc.add(new real_t {123812312.100})};
        std::vector<type_t> expect = { {type_id::real} };
        auto ret = array_construct_type_children({ arg1, arg2 });

        BOOST_CHECK(ret == expect);
    }

    BOOST_AUTO_TEST_CASE(case3) {
        value_t arg1 = { {type_id::real}, context.gc.add(new real_t {1238912.1239})};
        value_t arg2 = { {type_id::real}, context.gc.add(new real_t {123812312.100})};
        value_t arg3 = { {type_id::boolean}, context.gc.add((real_t *) new bool{true})};
        std::vector<type_t> expect = { {type_id::real}, {type_id::real}, {type_id::boolean} };
        auto ret = array_construct_type_children({ arg1, arg2, arg3 });

        BOOST_CHECK(ret == expect);
    }

    BOOST_AUTO_TEST_CASE(case4) {
        value_t arg1 = { {type_id::boolean}, context.gc.add((real_t *) new bool {true})};
        value_t arg2 = { {type_id::real}, context.gc.add(new real_t {123812312.100})};
        value_t arg3 = { {type_id::real}, context.gc.add(new real_t {1238912.1239})};
        std::vector<type_t> expect = { {type_id::boolean}, {type_id::real}, };
        auto ret = array_construct_type_children({ arg1, arg2, arg3 });

        BOOST_CHECK(ret == expect);
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(array_creates_new_array_from_empty_or_one_args_suite, context_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
		value_t expect = { { type_id::array }, {
		    context.gc.add(new std::vector<value_t>)
         } };
		value_t ret;

		array_func(context, { }, ret);

		BOOST_CHECK(ret == expect);
	}

    BOOST_AUTO_TEST_CASE(case2) {
        value_t arg1 = { {type_id::real}, context.gc.add(new real_t {1238912.1239})};
        value_t expect = { { type_id::array, { {type_id::real} } },{
            context.gc.add(new std::vector<value_t> {
                    { {type_id::real}, context.gc.add(new real_t {1238912.1239})}
            })
        } };
        value_t ret;

        array_func(context, { arg1 }, ret);

        BOOST_CHECK(ret == expect);
    }

    BOOST_AUTO_TEST_CASE(case3) {
        value_t arg1 = { {type_id::boolean}, context.gc.add((real_t *) new bool {true})};
        value_t expect = { { type_id::array, { {type_id::boolean} } },{
             context.gc.add(new std::vector<value_t> {
                     { {type_id::boolean}, context.gc.add((real_t *) new bool {true})}
             })
        } };
        value_t ret;

        array_func(context, { arg1 }, ret);

        BOOST_CHECK(ret == expect);
    }

    BOOST_AUTO_TEST_CASE(case4) {
        value_t arg1 = { {type_id::array}, context.gc.add((real_t *) new std::vector<value_t>)};
        value_t expect = { { type_id::array, { {type_id::array} } },{
             context.gc.add(new std::vector<value_t> {
                     { {type_id::array}, context.gc.add((real_t *) new std::vector<value_t>)}
             })
        } };
        value_t ret;

        array_func(context, { arg1 }, ret);

        BOOST_CHECK(ret == expect);
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(array_creates_new_array_different_combinations_of_two_or_more_args_suite, context_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
        value_t arg1 = { {type_id::real}, context.gc.add(new real_t {1238912.1239})};
        value_t arg2 = { {type_id::real}, context.gc.add(new real_t {123812312.100})};
        value_t arg3 = { {type_id::real}, context.gc.add(new real_t {122.15639})};
        value_t expect = { { type_id::array, { {type_id::real} } },{
            context.gc.add(new std::vector<value_t> {arg1, arg2, arg3})
        } };
        value_t ret;

        array_func(context, { arg1, arg2, arg3 }, ret);

        BOOST_CHECK(ret == expect);
    }

    BOOST_AUTO_TEST_CASE(case2) {
        value_t arg1 = { {type_id::real}, context.gc.add(new real_t {1238912.1239})};
        value_t arg2 = { {type_id::real}, context.gc.add(new real_t {123812312.100})};
        value_t expect = { { type_id::array, { {type_id::real} } },{
             context.gc.add(new std::vector<value_t> {arg1, arg2})
        } };
        value_t ret;

        array_func(context, { arg1, arg2 }, ret);

        BOOST_CHECK(ret == expect);
    }

    BOOST_AUTO_TEST_CASE(case3) {
        value_t arg1 = { {type_id::boolean}, context.gc.add((real_t *) new bool {true})};
        value_t arg2 = { {type_id::real}, context.gc.add(new real_t {123812312.100})};
        value_t arg3 = { {type_id::real}, context.gc.add(new real_t {1238912.1239})};
        value_t expect = { { type_id::array, { {type_id::boolean}, {type_id::real} } },{
            context.gc.add(new std::vector<value_t> {arg1, arg2, arg3})
        } };
        value_t ret;

        array_func(context, { arg1, arg2, arg3 }, ret);

        BOOST_CHECK(ret == expect);
    }

    BOOST_AUTO_TEST_CASE(case4) {
        value_t arg1 = { {type_id::boolean}, context.gc.add((real_t *) new bool {true})};
        value_t arg2 = { {type_id::boolean}, context.gc.add((real_t *) new bool {true})};
        value_t arg3 = { {type_id::boolean}, context.gc.add((real_t *) new bool {true})};
        value_t arg4 = { {type_id::boolean}, context.gc.add((real_t *) new bool {true})};
        value_t arg5 = { {type_id::boolean}, context.gc.add((real_t *) new bool {true})};
        value_t arg6 = { {type_id::boolean}, context.gc.add((real_t *) new bool {true})};
        value_t arg7 = { {type_id::real}, context.gc.add(new real_t {123812312.100})};
        value_t arg8 = { {type_id::real}, context.gc.add(new real_t {1238912.1239})};
        value_t arg9 = { {type_id::real}, context.gc.add(new real_t {1238912.1239})};
        value_t arg10 = { {type_id::real}, context.gc.add(new real_t {1238912.1239})};
        value_t arg11 = { {type_id::real}, context.gc.add(new real_t {1238912.1239})};
        value_t arg12 = { {type_id::real}, context.gc.add(new real_t {1238912.1239})};
        value_t arg13 = { {type_id::real}, context.gc.add(new real_t {1238912.1239})};
        value_t arg14 = { {type_id::real}, context.gc.add(new real_t {1238912.1239})};
        value_t arg15 = { {type_id::real}, context.gc.add(new real_t {1238912.1239})};
        value_t arg16 = { {type_id::real}, context.gc.add(new real_t {1238912.1239})};
        value_t expect = { { type_id::array, {
            {type_id::boolean}, {type_id::boolean}, {type_id::boolean},
            {type_id::boolean}, {type_id::boolean}, {type_id::boolean},
            {type_id::real}
        } },{
             context.gc.add(new std::vector<value_t> {
                 arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16
             })
        } };
        value_t ret;

        array_func(context, {
            arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16
        }, ret);

        BOOST_CHECK(ret == expect);
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(array_func_is_correctly_located_by_context_suite, context_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
        value_t expect = { { type_id::array }, {
                             context.gc.add(new std::vector<value_t>)
        } };
        value_t ret;

        call(context, "array", { }, 0, ret);

        BOOST_CHECK(ret == expect);
    }

    BOOST_AUTO_TEST_CASE(case2) {
        value_t arg1 = { {type_id::boolean}, context.gc.add((real_t *) new bool {true})};
        value_t arg2 = { {type_id::boolean}, context.gc.add((real_t *) new bool {true})};
        value_t arg3 = { {type_id::boolean}, context.gc.add((real_t *) new bool {true})};
        value_t arg4 = { {type_id::boolean}, context.gc.add((real_t *) new bool {true})};
        value_t arg5 = { {type_id::boolean}, context.gc.add((real_t *) new bool {true})};
        value_t arg6 = { {type_id::boolean}, context.gc.add((real_t *) new bool {true})};
        value_t arg7 = { {type_id::real}, context.gc.add(new real_t {123812312.100})};
        value_t arg8 = { {type_id::real}, context.gc.add(new real_t {1238912.1239})};
        value_t arg9 = { {type_id::real}, context.gc.add(new real_t {1238912.1239})};
        value_t arg10 = { {type_id::real}, context.gc.add(new real_t {1238912.1239})};
        value_t arg11 = { {type_id::real}, context.gc.add(new real_t {1238912.1239})};
        value_t arg12 = { {type_id::real}, context.gc.add(new real_t {1238912.1239})};
        value_t arg13 = { {type_id::real}, context.gc.add(new real_t {1238912.1239})};
        value_t arg14 = { {type_id::real}, context.gc.add(new real_t {1238912.1239})};
        value_t arg15 = { {type_id::real}, context.gc.add(new real_t {1238912.1239})};
        value_t arg16 = { {type_id::real}, context.gc.add(new real_t {1238912.1239})};
        value_t expect = { { type_id::array, {
                                                     {type_id::boolean}, {type_id::boolean}, {type_id::boolean},
                                                     {type_id::boolean}, {type_id::boolean}, {type_id::boolean},
                                                     {type_id::real}
                                             } },{
                             context.gc.add(new std::vector<value_t> {
                                     arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16
                             })
                           } };
        value_t ret;

        call(context, "array", {
                arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16
        }, 0, ret);

        BOOST_CHECK(ret == expect);
    }

BOOST_AUTO_TEST_SUITE_END()