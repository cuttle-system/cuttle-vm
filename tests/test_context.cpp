#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "test.hpp"
#include "context_methods.hpp"
#include "value_methods.hpp"
#include "type_error.hpp"
#include "name_error.hpp"
#include "type_argn_error.hpp"

using namespace cuttle::vm;

inline void test_add_variable_to_context() {
	{
		context_t context;
		value_t val = { {type_id::integral} };
		value_t val2 = { {type_id::integral} };

		val.data.integral = context.gc.add_r(new integral_t{ 1 });
		val2.data.integral = context.gc.add_r(new integral_t{ 2 });

		add(context, "foo", val);

		AssertEqual(context.variables["foo"][val.type], val, "Value");
		AssertNotEqual(context.variables["foo"][val.type], val2, "Another value");
	}
	{
		context_t context;
		value_t val = { { type_id::integral } };
		value_t val2 = { { type_id::integral } };
		value_t val3 = { { type_id::integral } };

		val.data.integral = context.gc.add_r(new integral_t{ 1 });
		val2.data.integral = context.gc.add_r(new integral_t{ 1 });
		val3.data.integral = context.gc.add_r(new integral_t{ 2 });
		
		add(context, "foo", val);

		AssertEqual(context.variables["foo"][val.type], val2, "Value");
		AssertNotEqual(context.variables["foo"][val.type], val3, "Another value");
	}
	{
		context_t context;
		value_t val = { { type_id::integral } };
		value_t val2 = { { type_id::integral } };
		value_t val3 = { { type_id::integral } };

		val.data.integral = context.gc.add_r(new integral_t{ 1 });
		val2.data.integral = context.gc.add_r(new integral_t{ 2 });
		val3.data.integral = context.gc.add_r(new integral_t{ 3 });

		add(context, "foo", val);
		add(context, "bar", val2);
		add(context, "baz", val3);

		AssertEqual(context.variables["foo"][val.type], val, "Value");
		AssertEqual(context.variables["bar"][val2.type], val2, "Value");
		AssertEqual(context.variables["baz"][val3.type], val3, "Value");
	}
	{
		context_t context;
		value_t val = { { type_id::integral } };
		value_t val2 = { { type_id::integral } };

		val.data.integral = context.gc.add_r(new integral_t{ 1 });
		val2.data.integral = context.gc.add_r(new integral_t{ 2 });

		add(context, "foo", val);
		AssertEqual(context.variables["foo"][val.type], val, "Value");
		AssertThrows(type_error, {
			add(context, "foo", val2);
		});
		AssertEqual(context.variables["foo"][val.type], val, "Value");
	}
}

inline void test_add_variable_to_context_with_one_name_and_different_types() {
	{
		context_t context;
		value_t val = { { type_id::integral } };
		value_t val2 = { { type_id::string } };

		val.data.integral = context.gc.add_r(new integral_t{ 1 });
		val2.data.string = context.gc.add_r(new std::string{ "this is a test string" });

		add(context, "foo", val);
		add(context, "foo", val2);

		AssertEqual(context.variables["foo"][val.type], val, "Integral value");
		AssertEqual(context.variables["foo"][val2.type], val2, "String value");
	}
	{
		context_t context;
		value_t val = { { type_id::integral } };
		value_t val2 = { { type_id::string } };

		val.data.integral = context.gc.add_r(new integral_t{ 1 });
		val2.data.string = context.gc.add_r(new std::string{ "this is a test string" });

		add(context, "foo", val);
		add(context, "foo", val2);
		
		add(context, "bar", val);
		add(context, "bar", val2);

		AssertEqual(context.variables["foo"][val.type], val, "Integral value");
		AssertEqual(context.variables["foo"][val2.type], val2, "String value");

		AssertEqual(context.variables["bar"][val.type], val, "Integral value");
		AssertEqual(context.variables["bar"][val2.type], val2, "String value");
	}
}

inline void test_get_variable_from_context() {
	{
		context_t context;
		value_t val = { { type_id::integral } };
		value_t val2 = { { type_id::integral } };

		val.data.integral = context.gc.add_r(new integral_t{ 1 });
		val2.data.integral = context.gc.add_r(new integral_t{ 2 });

		add(context, "foo", val);

		AssertEqual(get(context, "foo", val.type), val, "Value");
		AssertNotEqual(get(context, "foo", val.type), val2, "Another value");
	}
	{
		context_t context;
		value_t val = { { type_id::integral } };
		value_t val2 = { { type_id::integral } };
		value_t val3 = { { type_id::integral } };

		val.data.integral = context.gc.add_r(new integral_t{ 1 });
		val2.data.integral = context.gc.add_r(new integral_t{ 1 });
		val3.data.integral = context.gc.add_r(new integral_t{ 2 });

		add(context, "foo", val);

		AssertEqual(get(context, "foo", val.type), val2, "Value");
		AssertNotEqual(get(context, "foo", val.type), val3, "Another value");
	}
	{
		context_t context;
		value_t val = { { type_id::integral } };
		value_t val2 = { { type_id::integral } };
		value_t val3 = { { type_id::integral } };

		val.data.integral = context.gc.add_r(new integral_t{ 1 });
		val2.data.integral = context.gc.add_r(new integral_t{ 2 });
		val3.data.integral = context.gc.add_r(new integral_t{ 3 });

		add(context, "foo", val);
		add(context, "bar", val2);
		add(context, "baz", val3);

		AssertEqual(get(context, "foo", val.type), val, "Value");
		AssertEqual(get(context, "bar", val2.type), val2, "Value");
		AssertEqual(get(context, "baz", val3.type), val3, "Value");
	}
}

inline void test_get_variable_from_context_with_one_name_and_different_types() {
	{
		context_t context;
		value_t val = { { type_id::integral } };
		value_t val2 = { { type_id::string } };

		val.data.integral = context.gc.add_r(new integral_t{ 1 });
		val2.data.string = context.gc.add_r(new std::string{ "this is a test string" });

		add(context, "foo", val);
		add(context, "foo", val2);

		AssertEqual(get(context, "foo", val.type), val, "Integral value");
		AssertEqual(get(context, "foo", val2.type), val2, "String value");
	}
	{
		context_t context;
		value_t val = { { type_id::integral } };
		value_t val2 = { { type_id::string } };

		val.data.integral = context.gc.add_r(new integral_t{ 1 });
		val2.data.string = context.gc.add_r(new std::string{ "this is a test string" });

		add(context, "foo", val);
		add(context, "foo", val2);

		add(context, "bar", val);
		add(context, "bar", val2);

		AssertEqual(get(context, "foo", val.type), val, "Integral value");
		AssertEqual(get(context, "foo", val2.type), val2, "String value");

		AssertEqual(get(context, "bar", val.type), val, "Integral value");
		AssertEqual(get(context, "bar", val2.type), val2, "String value");
	}
}

inline void test_get_variable_from_context_throws_name_error() {
	{
		context_t context;
		
		AssertThrows(name_error, {
			get(context, "foo", {type_id::integral});
		});
	}
	{
		context_t context;
		value_t val = { { type_id::integral } };
		value_t val2 = { { type_id::string } };

		val.data.integral = context.gc.add_r(new integral_t{ 1 });
		val2.data.string = context.gc.add_r(new std::string{ "this is a test string" });

		add(context, "foo", val);
		add(context, "foo", val2);

		AssertThrows(name_error, {
			get(context, "foo",{ type_id::function });
		});
	}
	{
		context_t context;
		value_t val = { { type_id::integral } };

		val.data.integral = context.gc.add_r(new integral_t{ 1 });

		add(context, "foo", val);

		AssertThrows(name_error, {
			get(context, "foo",{ type_id::real });
		});
	}
}

inline void test_call_function() {
	{
		context_t context;
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

		AssertEqual(status, 0, "Status");
		AssertEqual(ret, expect, "Return value");
	}
	{
		context_t context;
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

		AssertEqual(status, 0, "Status");
		AssertEqual(ret, expect, "Return value");
	}
}

inline void test_get_variable_from_context_with_type_id_any() {
	{
		context_t context;
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

		AssertEqual(status, 0, "Status");
		AssertEqual(ret, expect, "Return value");

		status = call(context, "foo", { { type_id::boolean } }, 1, ret);

		AssertEqual(status, 0, "Status");
		AssertEqual(ret, expect, "Return value");

		AssertThrows(name_error, {
			status = call(context, "foo", { {type_id::boolean}, {type_id::boolean} }, 2, ret);
		});
	}
}

inline void test_call_type_argn_arg_properly_handled() {
	{
		context_t context;
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

		AssertEqual(status, 0, "Status");
		AssertEqual(ret, expect, "Return value");

		status = call(context, "foo", { { type_id::integral }, { type_id::integral } }, 1, ret);

		AssertEqual(status, 0, "Status");
		AssertEqual(ret, expect, "Return value");

		AssertThrows(name_error, {
			status = call(context, "foo", { {type_id::boolean} }, 1, ret);
		});

        AssertThrows(type_argn_error, {
            status = call(context, "foo", { {type_id::boolean} }, 2, ret);
        });

        AssertThrows(type_argn_error, {
            status = call(context, "foo", { {type_id::integral} }, 2, ret);
        });
	}
    {
        context_t context;
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

        AssertEqual(status, 0, "Status");
        AssertEqual(ret, expect, "Return value");
    }
    {
        context_t context;
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

        AssertEqual(status, 0, "Status");
        AssertEqual(ret, expect, "Return value");

        status = call(context, "foo", { { type_id::integral }, { type_id::boolean } }, 1, ret);

        AssertEqual(status, 0, "Status");
        AssertEqual(ret, expect, "Return value");

        status = call(context, "foo", { { type_id::integral }, { type_id::boolean } }, 1, ret);

        AssertEqual(status, 0, "Status");
        AssertEqual(ret, expect, "Return value");

        status = call(context, "foo", { { type_id::array }, { type_id::boolean } }, 1, ret);

        AssertEqual(status, 0, "Status");
        AssertEqual(ret, expect, "Return value");

        status = call(context, "foo", { { type_id::array }, { type_id::integral }, { type_id::boolean } }, 1, ret);

        AssertEqual(status, 0, "Status");
        AssertEqual(ret, expect, "Return value");

        status = call(context, "foo", { { type_id::array }, { type_id::integral }, { type_id::boolean }, { type_id::real } }, 1, ret);

        AssertEqual(status, 0, "Status");
        AssertEqual(ret, expect, "Return value");

        status = call(context, "foo", { { type_id::real }, { type_id::real }, { type_id::real }, { type_id::real } }, 1, ret);

        AssertEqual(status, 0, "Status");
        AssertEqual(ret, expect, "Return value");
    }
}

void run_context_tests() {
	TESTCASE
	test_add_variable_to_context();
	test_add_variable_to_context_with_one_name_and_different_types();
	test_get_variable_from_context();
	test_get_variable_from_context_with_one_name_and_different_types();
	test_get_variable_from_context_throws_name_error();
	test_get_variable_from_context_with_type_id_any();
	test_call_function();
	test_call_type_argn_arg_properly_handled();
}