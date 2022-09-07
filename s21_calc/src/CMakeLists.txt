cmake_minimum_required(VERSION 3.5)

project(calculator VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        qcustomplot.cpp
        mainwindow.h
        qcustomplot.h
        mainwindow.ui

        backend/calculator.c
        backend/string_to_polish.c
        backend/structs/ld_stack/core/add_to_ld_stack.c
        backend/structs/ld_stack/core/create_ld_stack.c
        backend/structs/ld_stack/core/free_ld_stack.c
        backend/structs/ld_stack/core/pop_ld_stack.c
        backend/structs/lex_stack/core/add_to_lex_stack.c
        backend/structs/lex_stack/core/create_lex_stack.c
        backend/structs/lex_stack/core/dump_lex_stack.c
        backend/structs/lex_stack/core/free_lex_stack.c
        backend/structs/lex_stack/core/pop_lex_stack.c
        backend/structs/lex_stack/core/reverse_stack.c
        backend/structs/lexeme/core/create_lexeme.c
        backend/structs/lexeme/core/free_lexeme.c
        backend/structs/lexeme/core/get_type_lexeme_from_string.c
        backend/structs/operators/comparison/char_is_operator.c
        backend/structs/operators/comparison/string_is_command.c
        backend/structs/operators/conversion/char_to_priority_operator.c
        backend/structs/operators/core/core.c
        backend/word_to_polish.c

        backend/calculator.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(calculator
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET calculator APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(calculator SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(calculator
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(calculator PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(calculator PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(calculator)
endif()
