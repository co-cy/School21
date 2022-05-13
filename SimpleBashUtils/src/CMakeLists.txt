cmake_minimum_required(VERSION 3.22)

project(s21_cat C)
project(s21_grep C)

set(CMAKE_C_STANDARD 11)

include_directories(cat)
include_directories(grep)
include_directories(linked_list)

add_executable(s21_cat
        cat/cat.c
        cat/cat.h)

add_executable(s21_grep
        grep/grep.c
        grep/grep.h
        linked_list/linked_list.c
        linked_list/linked_list.h
        custom.h
        flag.h)

set_target_properties(s21_grep PROPERTIES RUNTIME_OUTPUT_DIRECTORY grep)
set_target_properties(s21_cat PROPERTIES RUNTIME_OUTPUT_DIRECTORY cat)
