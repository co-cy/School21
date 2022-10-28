# 'Google_test' is the subproject name
project(tests)

add_executable(tests eq_test.cpp)
target_link_libraries(tests gtest gtest_main)