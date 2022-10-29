cmake_minimum_required(VERSION 3.22)
project(CPP1_s21_matrixplus)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE TEST)

set(CMAKE_BUILD_TYPE DEBUG CACHE STRING "Тип компиляции проекта")
set(TARGET_LIBRARY s21_matrix_oop CACHE STRING "Название конечной библиотеки")
set(TARGET_TEST tests CACHE STRING "Название цели")

set(FLAGS "" CACHE STRING "Флаги по умолчанию")
set(TEST_FLAGS -Wall -Werror -Wextra -Wpedantic -fsanitize=address -g CACHE STRING "Аргументы для тестов")
set(COVERAGE_FLAGS --coverage CACHE STRING "Флаги для генерации покрытия")

set(SOURCE s21_matrix_oop.h core/constructor.cpp core/destructor.cpp arithmetic/merge.cpp arithmetic/mult.cpp comparison/eq.cpp other/transpose.cpp other/crop.cpp core/resize.cpp operators/operators.cpp other/determiant.cpp other/complements.cpp other/inverse.cpp)
file(GLOB TEST_SOURCE test/*.cpp)

if(CMAKE_BUILD_TYPE STREQUAL "TEST")
    set(FLAGS ${FLAGS} ${TEST_FLAGS})
endif()

if (CMAKE_BUILD_TYPE STREQUAL "CTEST")
    set(FLAGS ${FLAGS} ${TEST_FLAGS} ${COVERAGE_FLAGS})
endif()

message(${FLAGS})
include_directories(.)

add_library(${TARGET_LIBRARY} STATIC ${SOURCE})
target_compile_options(${TARGET_LIBRARY} PRIVATE ${FLAGS})
target_link_options(${TARGET_LIBRARY} PRIVATE ${FLAGS})



#find_package(GTest REQUIRED)
#include(GoogleTest)
#enable_testing()
#
#add_executable(${TARGET_TEST} ${TEST_SOURCE})
#target_compile_options(${TARGET_TEST} PRIVATE ${TEST_FLAGS})
#target_link_options(${TARGET_TEST} PRIVATE  -lgtest ${FLAGS})
#
#target_link_libraries(${TARGET_TEST} GTest::gtest_main ${TARGET_LIBRARY})
#
#gtest_discover_tests(tests)
