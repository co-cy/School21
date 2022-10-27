cmake_minimum_required(VERSION 3.22)
project(CPP1_s21_matrixplus)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(CPP1_s21_matrixplus
        s21_matrix_oop.h core/constructor.cpp core/destructor.cpp arithmetic/merge.cpp arithmetic/mult.cpp comparison/eq.cpp other/transpose.cpp other/crop.cpp core/resize.cpp core/size.cpp operators/operators.cpp other/determiant.cpp other/complements.cpp other/inverse.cpp)

add_subdirectory(tests)