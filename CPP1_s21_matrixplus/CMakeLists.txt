cmake_minimum_required(VERSION 3.22)
project(CPP1_s21_matrixplus)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(CPP1_s21_matrixplus
        src/s21_matrix_oop.h src/core/constructor.cpp src/core/destructor.cpp src/arithmetic/merge.cpp src/arithmetic/mult.cpp src/comparison/eq.cpp src/main.cpp src/other/transpose.cpp src/other/crop.cpp src/core/resize.cpp src/core/size.cpp src/operators/operators.cpp src/other/determiant.cpp src/other/complements.cpp src/other/inverse.cpp)
