#define BOOST_TEST_DYN_LINK

#include <iostream>
#include <boost/test/unit_test.hpp>
#include <string>
#include <unordered_map>
#include <vector>

#include "context_methods.hpp"
#include "value_methods.hpp"
#include "type_error.hpp"
#include "name_error.hpp"
#include "type_argn_error.hpp"

using namespace cuttle::vm;

struct context_fixture {
    context_t context;
};

BOOST_FIXTURE_TEST_SUITE(add_variable_to_context_suite, context_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
		value_t val = { {type_id::integral} };
		value_t val2 = { {type_id::integral} };

		val.data.integral = context.gc.add_r(new integral_t{ 1 });
		val2.data.integral = context.gc.add_r(new integral_t{ 2 });

		add(context, "foo", val);

		BOOST_CHECK(context.variables["foo"][val.type] == val);
		BOOST_CHECK(context.variables["foo"][val.type] != val2);
	}

    BOOST_AUTO_TEST_CASE(case2) {
		value_t val = { { type_id::integral } };
		value_t val2 = { { type_id::integral } };
		value_t val3 = { { type_id::integral } };

		val.data.integral = context.gc.add_r(new integral_t{ 1 });
		val2.data.integral = context.gc.add_r(new integral_t{ 1 });
		val3.data.integral = context.gc.add_r(new integral_t{ 2 });
		
		add(context, "foo", val);

		BOOST_CHECK(context.variables["foo"][val.type] == val2);
		BOOST_CHECK(context.variables["foo"][val.type] != val3);
	}

    BOOST_AUTO_TEST_CASE(case3) {
		value_t val = { { type_id::integral } };
		value_t val2 = { { type_id::integral } };
		value_t val3 = { { type_id::integral } };

		val.data.integral = context.gc.add_r(new integral_t{ 1 });
		val2.data.integral = context.gc.add_r(new integral_t{ 2 });
		val3.data.integral = context.gc.add_r(new integral_t{ 3 });

		add(context, "foo", val);
		add(context, "bar", val2);
		add(context, "baz", val3);

		BOOST_CHECK(context.variables["foo"][val.type] == val);
		BOOST_CHECK(context.variables["bar"][val2.type] == val2);
		BOOST_CHECK(context.variables["baz"][val3.type] == val3);
	}

    BOOST_AUTO_TEST_CASE(case4) {
		value_t val = { { type_id::integral } };
		value_t val2 = { { type_id::integral } };

		val.data.integral = context.gc.add_r(new integral_t{ 1 });
		val2.data.integral = context.gc.add_r(new integral_t{ 2 });

		add(context, "foo", val);
		BOOST_CHECK(context.variables["foo"][val.type] == val);
		BOOST_CHECK_THROW(do {
			add(context, "foo", val2);
		} while (0), type_error);
		BOOST_CHECK(context.variables["foo"][val.type] == val);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(add_variable_to_context_with_one_name_and_different_types_suite, context_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
		value_t val = { { type_id::integral } };
		value_t val2 = { { type_id::string } };

		val.data.integral = context.gc.add_r(new integral_t{ 1 });
		val2.data.string = context.gc.add_r(new std::string{ "this is a test string" });

		add(context, "foo", val);
		add(context, "foo", val2);

		BOOST_CHECK(context.variables["foo"][val.type] == val);
		BOOST_CHECK(context.variables["foo"][val2.type] == val2);
	}

    BOOST_AUTO_TEST_CASE(case2) {
		value_t val = { { type_id::integral } };
		value_t val2 = { { type_id::string } };

		val.data.integral = context.gc.add_r(new integral_t{ 1 });
		val2.data.string = context.gc.add_r(new std::string{ "this is a test string" });

		add(context, "foo", val);
		add(context, "foo", val2);
		
		add(context, "bar", val);
		add(context, "bar", val2);

		BOOST_CHECK(context.variables["foo"][val.type] == val);
		BOOST_CHECK(context.variables["foo"][val2.type] == val2);

		BOOST_CHECK(context.variables["bar"][val.type] == val);
		BOOST_CHECK(context.variables["bar"][val2.type] == val2);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(get_variable_from_context_suite, context_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
		value_t val = { { type_id::integral } };
		value_t val2 = { { type_id::integral } };

		val.data.integral = context.gc.add_r(new integral_t{ 1 });
		val2.data.integral = context.gc.add_r(new integral_t{ 2 });

		add(context, "foo", val);

		BOOST_CHECK(get(context, "foo", val.type) == val);
		BOOST_CHECK(get(context, "foo", val.type) != val2);
	}

    BOOST_AUTO_TEST_CASE(case2) {
		value_t val = { { type_id::integral } };
		value_t val2 = { { type_id::integral } };
		value_t val3 = { { type_id::integral } };

		val.data.integral = context.gc.add_r(new integral_t{ 1 });
		val2.data.integral = context.gc.add_r(new integral_t{ 1 });
		val3.data.integral = context.gc.add_r(new integral_t{ 2 });

		add(context, "foo", val);

		BOOST_CHECK(get(context, "foo", val.type) == val2);
		BOOST_CHECK(get(context, "foo", val.type) != val3);
	}

    BOOST_AUTO_TEST_CASE(case3) {
		value_t val = { { type_id::integral } };
		value_t val2 = { { type_id::integral } };
		value_t val3 = { { type_id::integral } };

		val.data.integral = context.gc.add_r(new integral_t{ 1 });
		val2.data.integral = context.gc.add_r(new integral_t{ 2 });
		val3.data.integral = context.gc.add_r(new integral_t{ 3 });

		add(context, "foo", val);
		add(context, "bar", val2);
		add(context, "baz", val3);

		BOOST_CHECK(get(context, "foo", val.type) == val);
		BOOST_CHECK(get(context, "bar", val2.type) == val2);
		BOOST_CHECK(get(context, "baz", val3.type) == val3);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(get_variable_from_context_with_one_name_and_different_types_suite, context_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
		value_t val = { { type_id::integral } };
		value_t val2 = { { type_id::string } };

		val.data.integral = context.gc.add_r(new integral_t{ 1 });
		val2.data.string = context.gc.add_r(new std::string{ "this is a test string" });

		add(context, "foo", val);
		add(context, "foo", val2);

		BOOST_CHECK(get(context, "foo", val.type) == val);
		BOOST_CHECK(get(context, "foo", val2.type) == val2);
	}

    BOOST_AUTO_TEST_CASE(case2) {
		value_t val = { { type_id::integral } };
		value_t val2 = { { type_id::string } };

		val.data.integral = context.gc.add_r(new integral_t{ 1 });
		val2.data.string = context.gc.add_r(new std::string{ "this is a test string" });

		add(context, "foo", val);
		add(context, "foo", val2);

		add(context, "bar", val);
		add(context, "bar", val2);

		BOOST_CHECK(get(context, "foo", val.type) == val);
		BOOST_CHECK(get(context, "foo", val2.type) == val2);

		BOOST_CHECK(get(context, "bar", val.type) == val);
		BOOST_CHECK(get(context, "bar", val2.type) == val2);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(get_variable_from_context_throws_name_error_suite, context_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
		BOOST_CHECK_THROW(do {
			get(context, "foo", {type_id::integral});
		} while (0), name_error);
	}

    BOOST_AUTO_TEST_CASE(case2) {
		value_t val = { { type_id::integral } };
		value_t val2 = { { type_id::string } };

		val.data.integral = context.gc.add_r(new integral_t{ 1 });
		val2.data.string = context.gc.add_r(new std::string{ "this is a test string" });

		add(context, "foo", val);
		add(context, "foo", val2);

		BOOST_CHECK_THROW(do {
			get(context, "foo",{ type_id::function });
		} while (0), name_error);
	}

    BOOST_AUTO_TEST_CASE(case3) {
		value_t val = { { type_id::integral } };

		val.data.integral = context.gc.add_r(new integral_t{ 1 });

		add(context, "foo", val);

		BOOST_CHECK_THROW(do {
			get(context, "foo",{ type_id::real });
		} while (0), name_error);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(call_function_suite, context_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
		value_t func = { {type_id::function} };
		func.data.function = [](context_t& context, const std::vector<value_t>& args, value_t& ret) {
			ret.type = { type_id::integral };
			ret.data.integral = context.gc.add_r(new integral_t{ 275 });
			return 0;
		};
		value_t ret;
		value_t expect = { {type_id::integral} };
		expect.data.integral = context.gc.add_r(new integral_t{ 275 });

		add(context, "foo", func);

		int status = call(context, "foo", {}, 0, ret);

		BOOST_CHECK(status == 0);
		BOOST_CHECK(ret == expect);
	}

    BOOST_AUTO_TEST_CASE(case2) {
		value_t func = { { type_id::function, {{type_id::integral}} } };
		func.data.function = [](context_t& context, const std::vector<value_t>& args, value_t& ret) {
			ret.type = { type_id::integral };
			ret.data.integral = context.gc.add_r(new integral_t{ 275 + *args[0].data.integral });
			return 0;
		};
		value_t ret;
		value_t arg = { {type_id::integral} };
		arg.data.integral = context.gc.add_r(new integral_t{ 25 });
		value_t expect = { { type_id::integral } };
		expect.data.integral = context.gc.add_r(new integral_t{ 300 });

		add(context, "foo", func);

		int status = call(context, "foo", {arg}, 1, ret);

		BOOST_CHECK(status == 0);
		BOOST_CHECK(ret == expect);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(get_variable_from_context_with_type_id_any_suite, context_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
		value_t func = { { type_id::function, { { type_id::any } } } };
		func.data.function = [](context_t& context, const std::vector<value_t>& args, value_t& ret) {
			ret.type = { type_id::integral };
			ret.data.integral = context.gc.add_r(new integral_t{ 275 });
			return 0;
		};
		value_t ret;
		value_t expect = { { type_id::integral } };
		expect.data.integral = context.gc.add_r(new integral_t{ 275 });

		add(context, "foo", func);

		int status = call(context, "foo", { { type_id::integral } }, 1, ret);

		BOOST_CHECK(status == 0);
		BOOST_CHECK(ret == expect);

		status = call(context, "foo", { { type_id::boolean } }, 1, ret);

		BOOST_CHECK(status == 0);
		BOOST_CHECK(ret == expect);

		BOOST_CHECK_THROW(do {
			status = call(context, "foo", { {type_id::boolean}, {type_id::boolean} }, 2, ret);
		} while (0), name_error);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(call_type_argn_arg_properly_handled_suite, context_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
		value_t func = { { type_id::function, { { type_id::integral } } } };
		func.data.function = [](context_t& context, const std::vector<value_t>& args, value_t& ret) {
			ret.type = { type_id::boolean };
			ret.data.boolean = context.gc.add_r(new bool{ true });
			return 0;
		};
		value_t ret;
		value_t expect = { { type_id::boolean } };
		expect.data.boolean = context.gc.add_r(new bool{ true });

		add(context, "foo", func);

		int status = call(context, "foo", { { type_id::integral } }, 1, ret);

		BOOST_CHECK(status == 0);
		BOOST_CHECK(ret == expect);

		status = call(context, "foo", { { type_id::integral }, { type_id::integral } }, 1, ret);

		BOOST_CHECK(status == 0);
		BOOST_CHECK(ret == expect);

		BOOST_CHECK_THROW(do {
			status = call(context, "foo", { {type_id::boolean} }, 1, ret);
		} while (0), name_error);

        BOOST_CHECK_THROW(do {
            status = call(context, "foo", { {type_id::boolean} }, 2, ret);
        } while (0), type_argn_error);

        BOOST_CHECK_THROW(do {
            status = call(context, "foo", { {type_id::integral} }, 2, ret);
        } while (0), type_argn_error);
	}

	BOOST_AUTO_TEST_CASE(case2) {
        value_t func = { { type_id::function, { { type_id::integral } } } };
        func.data.function = [](context_t& context, const std::vector<value_t>& args, value_t& ret) {
            integral_t value = 0;
            for (auto arg : args) {
                value += *arg.data.integral;
            }
            ret = { {type_id::integral}, context.gc.add(new integral_t{value}) };
            return 0;
        };
        value_t ret;
        value_t expect = { {type_id::integral}, context.gc.add(new integral_t{111}) };
        std::vector<value_t> args {
            { {type_id::integral}, context.gc.add(new integral_t{1}) },
            { {type_id::integral}, context.gc.add(new integral_t{100}) },
            { {type_id::integral}, context.gc.add(new integral_t{10}) }
        };

        add(context, "foo", func);

        int status = call(context, "foo", args, 1, ret);

        BOOST_CHECK(status == 0);
        BOOST_CHECK(ret == expect);
    }

    BOOST_AUTO_TEST_CASE(case3) {
        value_t func = { { type_id::function, { { type_id::any } } } };
        func.data.function = [](context_t& context, const std::vector<value_t>& args, value_t& ret) {
            ret.type = { type_id::boolean };
            ret.data.boolean = context.gc.add_r(new bool{ true });
            return 0;
        };
        value_t ret;
        value_t expect = { { type_id::boolean } };
        expect.data.boolean = context.gc.add_r(new bool{ true });

        add(context, "foo", func);

        int status = call(context, "foo", { { type_id::integral } }, 1, ret);

        BOOST_CHECK(status == 0);
        BOOST_CHECK(ret == expect);

        status = call(context, "foo", { { type_id::integral }, { type_id::boolean } }, 1, ret);

        BOOST_CHECK(status == 0);
        BOOST_CHECK(ret == expect);

        status = call(context, "foo", { { type_id::integral }, { type_id::boolean } }, 1, ret);

        BOOST_CHECK(status == 0);
        BOOST_CHECK(ret == expect);

        status = call(context, "foo", { { type_id::array }, { type_id::boolean } }, 1, ret);

        BOOST_CHECK(status == 0);
        BOOST_CHECK(ret == expect);

        status = call(context, "foo", { { type_id::array }, { type_id::integral }, { type_id::boolean } }, 1, ret);

        BOOST_CHECK(status == 0);
        BOOST_CHECK(ret == expect);

        status = call(context, "foo", { { type_id::array }, { type_id::integral }, { type_id::boolean }, { type_id::real } }, 1, ret);

        BOOST_CHECK(status == 0);
        BOOST_CHECK(ret == expect);

        status = call(context, "foo", { { type_id::real }, { type_id::real }, { type_id::real }, { type_id::real } }, 1, ret);

        BOOST_CHECK(status == 0);
        BOOST_CHECK(ret == expect);
    }

BOOST_AUTO_TEST_SUITE_END()