cmake_minimum_required(VERSION 3.21)
project(LLP2 C)

set(CMAKE_C_STANDARD 99)

add_executable(LLP2 include/ast.h ast.c show_tree.c include/show_tree.h)
