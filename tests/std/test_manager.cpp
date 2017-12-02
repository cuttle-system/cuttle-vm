#include <iostream>
#include "test_real.hpp"
//#include "test_integral.hpp"
//#include "test_string.hpp"
//#include "test_byte.hpp"

void run_std_tests() {
	std::cout << "----- testing standard library -----" << std::endl;
	run_real_tests();
	//run_integral_tests();
}