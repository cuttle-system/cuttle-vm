#include <iostream>
#include "test_real.hpp"
#include "test_boolean.hpp"
#include "test_array.hpp"
//#include "test_integral.hpp"
//#include "test_string.hpp"
//#include "test_byte.hpp"

void run_std_tests() {
	std::cout << "----- testing standard library -----" << std::endl;
	run_real_tests();
	run_boolean_tests();
//	run_array_tests();
	//run_integral_tests();
}