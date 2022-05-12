cmake_minimum_required(VERSION 3.22)
project(SimpleBashUtils C)
project(GREP C)

set(CMAKE_C_STANDARD 11)

include_directories(src)
include_directories(src/cat)
include_directories(src/grep)
include_directories(src/linked_list)

add_executable(GREP
        src/grep/grep.c
        src/grep/grep.h
        src/grep/grep_parser.c
        src/grep/more_string.c
        src/grep/privat_grep.h
        src/linked_list/linked_list.c
        src/linked_list/linked_list.h
        src/custom.h
        src/flag.h)

add_executable(SimpleBashUtils
        src/cat/cat.c
        src/cat/cat.h
        src/custom.h
        src/flag.h)