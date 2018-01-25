#include <iostream>
#include <fstream>
#include <string>
#include "test.hpp"
#include "test_real.hpp"
#include "context.hpp"
#include "std.hpp"
#include "std/real.cpp"

using namespace std;

inline void test_real_plus() {
	using namespace cuttle::vm;

	context_t context;

	populate(context);

	{
		value_t val1 = { { type_id::real },{ context.gc.add(new double{ 1.0 }) } };
		value_t val2 = { {type_id::real}, {context.gc.add(new double{ 2.0 })} };
		value_t expect = { {type_id::real}, {context.gc.add(new double{ 3.0 })} };
		value_t ret;

		real_plus_func(context, { val1, val2 }, ret);

		AssertEqual(ret, expect, "Return value");
	}
	{
		value_t val1 = { { type_id::real },{ context.gc.add(new double{ 100.01 }) } };
		value_t val2 = { { type_id::real },{ context.gc.add(new double{ 3.002 }) } };
		value_t expect = { { type_id::real },{ context.gc.add(new double{ 103.012 }) } };
		value_t ret;

		real_plus_func(context, { val1, val2 }, ret);

		AssertEqual(ret, expect, "Return value");
	}
}

inline void test_real_minus() {
	using namespace cuttle::vm;

	context_t context;

	populate(context);

	{
		value_t val1 = { { type_id::real },{ context.gc.add(new double{ 1.0 }) } };
		value_t val2 = { { type_id::real },{ context.gc.add(new double{ 2.0 }) } };
		value_t expect = { { type_id::real },{ context.gc.add(new double{ -1.0 }) } };
		value_t ret;

		real_minus_func(context, { val1, val2 }, ret);

		AssertEqual(ret, expect, "Return value");
	}
	{
		value_t val1 = { { type_id::real },{ context.gc.add(new double{ 100.02 }) } };
		value_t val2 = { { type_id::real },{ context.gc.add(new double{ 3.01 }) } };
		value_t expect = { { type_id::real },{ context.gc.add(new double{ 97.01 }) } };
		value_t ret;

		real_minus_func(context, { val1, val2 }, ret);

		AssertEqual(ret, expect, "Return value");
	}
}

inline void test_real_multiply() {
	using namespace cuttle::vm;

	context_t context;

	populate(context);

	{
		value_t val1 = { { type_id::real },{ context.gc.add(new double{ 1.0 }) } };
		value_t val2 = { { type_id::real },{ context.gc.add(new double{ 2.1 }) } };
		value_t expect = { { type_id::real },{ context.gc.add(new double{ 2.1 }) } };
		value_t ret;

		real_multiply_func(context, { val1, val2 }, ret);

		AssertEqual(ret, expect, "Return value");
	}
	{
		value_t val1 = { { type_id::real },{ context.gc.add(new double{ 100.02 }) } };
		value_t val2 = { { type_id::real },{ context.gc.add(new double{ 0.03 }) } };
		value_t expect = { { type_id::real },{ context.gc.add(new double{ 3.0006 }) } };
		value_t ret;

		real_multiply_func(context, { val1, val2 }, ret);

		AssertEqual(ret, expect, "Return value");
	}
}

inline void test_real_divide() {
	using namespace cuttle::vm;

	context_t context;

	populate(context);

	{
		value_t val1 = { { type_id::real },{ context.gc.add(new double{ 1.0 }) } };
		value_t val2 = { { type_id::real },{ context.gc.add(new double{ 2.0 }) } };
		value_t expect = { { type_id::real },{ context.gc.add(new double{ 0.5 }) } };
		value_t ret;

		real_divide_func(context, { val1, val2 }, ret);

		AssertEqual(ret, expect, "Return value");
	}
	{
		value_t val1 = { { type_id::real },{ context.gc.add(new double{ 29.0 }) } };
		value_t val2 = { { type_id::real },{ context.gc.add(new double{ 5.0 }) } };
		value_t expect = { { type_id::real },{ context.gc.add(new double{ 5.8 }) } };
		value_t ret;

		real_divide_func(context, { val1, val2 }, ret);

		AssertEqual(ret, expect, "Return value");
	}
}

inline void test_string_to_real() {
	using namespace cuttle::vm;

	context_t context;

	populate(context);

	{
		value_t val = { { type_id::string } };
		val.data.string = context.gc.add(new std::string{ "3.10" });
		value_t expect = { { type_id::real },{ context.gc.add(new double{ 3.1 }) } };
		value_t ret;

		string_to_real_func(context, { val }, ret);

		AssertEqual(ret, expect, "Return value");
	}
	{
		value_t val = { { type_id::string } };
		val.data.string = context.gc.add(new std::string{ "3" });
		value_t expect = { { type_id::real },{ context.gc.add(new double{ 3.0 }) } };
		value_t ret;

		string_to_real_func(context, { val }, ret);

		AssertEqual(ret, expect, "Return value");
	}
	{
		value_t val = { { type_id::string } };
		val.data.string = context.gc.add(new std::string{ "ads" });
		value_t expect = { { type_id::real },{ context.gc.add(new double{ 0.0 }) } };
		value_t ret;

		string_to_real_func(context, { val }, ret);

		AssertEqual(ret, expect, "Return value");
	}
}

inline void test_integral_to_real() {
	using namespace cuttle::vm;

	context_t context;

	populate(context);

	{
		value_t val = { { type_id::integral } };
		val.data.integral = context.gc.add(new long long{ 3 });
		value_t expect = { { type_id::real },{ context.gc.add(new double{ 3.0 }) } };
		value_t ret;

		integral_to_real_func(context, { val }, ret);

		AssertEqual(ret, expect, "Return value");
	}
}

void run_real_tests() {
	TESTCASE;
    test_real_plus();
	test_real_minus();
	test_real_multiply();
	test_real_divide();
	test_string_to_real();
	test_integral_to_real();
}