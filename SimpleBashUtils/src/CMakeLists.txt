cmake_minimum_required(VERSION 3.22)
project(s21_cat C)
project(s21_grep C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(cat)
include_directories(grep)
include_directories(linked_list)

add_executable(s21_grep
        grep/grep.c
        grep/grep.h
        grep/grep_parser.c
        grep/more_string.c
        grep/privat_grep.h
        linked_list/linked_list.c
        linked_list/linked_list.h
        custom.h
        flag.h)

add_executable(s21_cat
        cat/cat.c
        cat/cat.h
        custom.h
        flag.h)