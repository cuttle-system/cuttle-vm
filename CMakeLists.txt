cmake_minimum_required(VERSION 3.0.2)

project(CuttleVM VERSION 0.1 LANGUAGES CXX)

include(CMakeToolsHelpers OPTIONAL)

file(GLOB SRCS "src/*.cpp")
file(GLOB_RECURSE TEST_SRCS "tests/*.cpp" "tests/std/*.cpp")

file(GLOB HEADERS "src/*.hpp")
file(GLOB_RECURSE TEST_HEADERS "tests/*.hpp")

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS_DEBUG
  "${CMAKE_CXX_FLAGS_DEBUG} -std=c++14")
set(CMAKE_CXX_FLAGS_RELEASE
  "${CMAKE_CXX_FLAGS_RELEASE} -std=c++14")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS_DEBUG
            "${CMAKE_CXX_FLAGS_DEBUG} -Wextra")
    set(CMAKE_CXX_FLAGS_RELEASE
            "${CMAKE_CXX_FLAGS_RELEASE} -Wextra")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi")
    #set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
    #set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Ox")
    #set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
endif()


add_library(cuttle_vm SHARED ${SRCS} ${HEADERS} src/parse_error.hpp)
add_executable(cuttle_vm_tests ${TEST_SRCS} ${HEADERS} ${TEST_HEADERS})

target_include_directories(cuttle_vm PRIVATE "src/")
target_include_directories(cuttle_vm_tests PRIVATE "src/" "tests/" "tests/cuttle-test/src/")

target_link_libraries(cuttle_vm_tests cuttle_vm)
