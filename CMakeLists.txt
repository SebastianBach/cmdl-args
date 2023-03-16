cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(argument_parser VERSION 0.1 DESCRIPTION "A tool that generates C++ code that parses command line arguments." LANGUAGES CXX)
enable_testing()


if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message("build with GCC")
    add_compile_options(-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wold-style-cast -Wunused -Wpedantic -Wconversion -Werror)
endif()

add_subdirectory(src)
