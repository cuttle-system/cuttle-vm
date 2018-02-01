#include <iostream>
#include "std/test_manager.hpp"
#include "test_file_access.hpp"
#include "test_context.hpp"
#include "test_interpreter.hpp"

void run_tests() {
    run_file_access_tests();
	run_context_tests();
	run_interpreter_tests();
	//
	run_std_tests();
}