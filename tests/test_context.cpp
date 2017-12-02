#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "test.hpp"
#include "context_methods.hpp"
#include "value_methods.hpp"
#include "type_error.hpp"
#include "name_error.hpp"

using namespace cuttle::vm;

inline void test_add_variable_to_context() {
	{
		context_t context;
		value_t val = { {type_id::integral} };
		value_t val2 = { {type_id::integral} };

		val.data.integral = context.gc.add(new int{ 1 });
		val2.data.integral = context.gc.add(new int{ 2 });

		add(context, "foo", val);

		AssertEqual(context.variables["foo"][val.type], val, "Value");
		AssertNotEqual(context.variables["foo"][val.type], val2, "Another value");
	}
	{
		context_t context;
		value_t val = { { type_id::integral } };
		value_t val2 = { { type_id::integral } };
		value_t val3 = { { type_id::integral } };

		val.data.integral = context.gc.add(new int{ 1 });
		val2.data.integral = context.gc.add(new int{ 1 });
		val3.data.integral = context.gc.add(new int{ 2 });
		
		add(context, "foo", val);

		AssertEqual(context.variables["foo"][val.type], val2, "Value");
		AssertNotEqual(context.variables["foo"][val.type], val3, "Another value");
	}
	{
		context_t context;
		value_t val = { { type_id::integral } };
		value_t val2 = { { type_id::integral } };
		value_t val3 = { { type_id::integral } };

		val.data.integral = context.gc.add(new int{ 1 });
		val2.data.integral = context.gc.add(new int{ 2 });
		val3.data.integral = context.gc.add(new int{ 3 });

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

		val.data.integral = context.gc.add(new int{ 1 });
		val2.data.integral = context.gc.add(new int{ 2 });

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

		val.data.integral = context.gc.add(new int{ 1 });
		val2.data.string = context.gc.add(new std::string{ "this is a test string" });

		add(context, "foo", val);
		add(context, "foo", val2);

		AssertEqual(context.variables["foo"][val.type], val, "Integral value");
		AssertEqual(context.variables["foo"][val2.type], val2, "String value");
	}
	{
		context_t context;
		value_t val = { { type_id::integral } };
		value_t val2 = { { type_id::string } };

		val.data.integral = context.gc.add(new int{ 1 });
		val2.data.string = context.gc.add(new std::string{ "this is a test string" });

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

		val.data.integral = context.gc.add(new int{ 1 });
		val2.data.integral = context.gc.add(new int{ 2 });

		add(context, "foo", val);

		AssertEqual(get(context, "foo", val.type), val, "Value");
		AssertNotEqual(get(context, "foo", val.type), val2, "Another value");
	}
	{
		context_t context;
		value_t val = { { type_id::integral } };
		value_t val2 = { { type_id::integral } };
		value_t val3 = { { type_id::integral } };

		val.data.integral = context.gc.add(new int{ 1 });
		val2.data.integral = context.gc.add(new int{ 1 });
		val3.data.integral = context.gc.add(new int{ 2 });

		add(context, "foo", val);

		AssertEqual(get(context, "foo", val.type), val2, "Value");
		AssertNotEqual(get(context, "foo", val.type), val3, "Another value");
	}
	{
		context_t context;
		value_t val = { { type_id::integral } };
		value_t val2 = { { type_id::integral } };
		value_t val3 = { { type_id::integral } };

		val.data.integral = context.gc.add(new int{ 1 });
		val2.data.integral = context.gc.add(new int{ 2 });
		val3.data.integral = context.gc.add(new int{ 3 });

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

		val.data.integral = context.gc.add(new int{ 1 });
		val2.data.string = context.gc.add(new std::string{ "this is a test string" });

		add(context, "foo", val);
		add(context, "foo", val2);

		AssertEqual(get(context, "foo", val.type), val, "Integral value");
		AssertEqual(get(context, "foo", val2.type), val2, "String value");
	}
	{
		context_t context;
		value_t val = { { type_id::integral } };
		value_t val2 = { { type_id::string } };

		val.data.integral = context.gc.add(new int{ 1 });
		val2.data.string = context.gc.add(new std::string{ "this is a test string" });

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

		val.data.integral = context.gc.add(new int{ 1 });
		val2.data.string = context.gc.add(new std::string{ "this is a test string" });

		add(context, "foo", val);
		add(context, "foo", val2);

		AssertThrows(name_error, {
			get(context, "foo",{ type_id::function });
		});
	}
	{
		context_t context;
		value_t val = { { type_id::integral } };

		val.data.integral = context.gc.add(new int{ 1 });

		add(context, "foo", val);

		AssertThrows(name_error, {
			get(context, "foo",{ type_id::real });
		});
	}
}

void run_context_tests() {
	TESTCASE
	test_add_variable_to_context();
	test_add_variable_to_context_with_one_name_and_different_types();
	test_get_variable_from_context();
	test_get_variable_from_context_with_one_name_and_different_types();
	test_get_variable_from_context_throws_name_error();
}