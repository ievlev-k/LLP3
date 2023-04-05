cmake_minimum_required(VERSION 3.21)
project(LLP1 C)

set(CMAKE_C_STANDARD 99)

add_executable(LLP1 main.c include/database_include.h include/file.h include/schema.h database.c file.c table.c schema.c struct/database.h struct/table.h struct/query.h include/table_include.h include/test.h include/data_types.h data_types.c test.c)
