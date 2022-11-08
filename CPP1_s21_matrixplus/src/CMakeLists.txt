cmake_minimum_required(VERSION 3.22)
project(CPP1_s21_matrixplus)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(TARGET_LIBRARY s21_matrix_oop)
set(TARGET_TEST tests)

set(MORE_CXX_FLAGS "-std=c++17")
set(TESTFILE_FLAGS "")
set(TEST_FLAGS -Wall -Werror -Wextra -Wpedantic -fsanitize=address -fsanitize=leak -fsanitize=undefined -g)
set(COVERAGE_FLAGS --coverage)



set(SOURCE other/inverse.cpp other/determiant.cpp other/complements.cpp other/crop.cpp other/transpose.cpp arithmetic/merge.cpp arithmetic/mult.cpp operators/operators.cpp core/constructor.cpp core/resize.cpp core/destructor.cpp comparison/eq.cpp)
set(TEST_SOURCE test/sub_matrix.cpp test/construct.cpp test/eq_test.cpp test/mul_matrix.cpp test/mul_num.cpp test/transpose_matrix.cpp test/calc_matrix.cpp test/other.cpp test/sum_matrix.cpp test/inverse_matrix.cpp test/det_matrix.cpp)

if (CMAKE_BUILD_TYPE STREQUAL "TEST")
    set(MORE_CXX_FLAGS ${MORE_CXX_FLAGS} ${TEST_FLAGS} ${COVERAGE_FLAGS})
    set(TESTFILE_FLAGS ${TESTFILE_FLAGS} ${TEST_FLAGS})
endif()

include_directories(.)

add_library(${TARGET_LIBRARY} STATIC ${SOURCE})

target_compile_options(${TARGET_LIBRARY} PRIVATE ${CMAKE_CXX_FLAGS} ${MORE_CXX_FLAGS})
target_compile_features(${TARGET_LIBRARY} PRIVATE cxx_std_17)
target_link_options(${TARGET_LIBRARY} PRIVATE ${CMAKE_CXX_FLAGS} ${MORE_CXX_FLAGS})

find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(${TARGET_TEST} ${TEST_SOURCE})
target_compile_features(${TARGET_TEST} PRIVATE cxx_std_17)
target_compile_options(${TARGET_TEST} PRIVATE ${TESTFILE_FLAGS} ${CMAKE_CXX_FLAGS})

if (CMAKE_BUILD_TYPE STREQUAL "TEST")
    target_link_options(${TARGET_TEST} PRIVATE ${TESTFILE_FLAGS} ${COVERAGE_FLAGS})
else()
    target_link_options(${TARGET_TEST} PRIVATE ${TESTFILE_FLAGS})
endif()

target_link_libraries(${TARGET_TEST} ${TARGET_LIBRARY} GTest::gtest_main)

