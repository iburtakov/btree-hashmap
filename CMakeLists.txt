cmake_minimum_required(VERSION 3.14)
project(map C)

set(CMAKE_C_STANDARD 99)

add_executable(map main.c hashmap.h btree.h map.h btree.c hashmap.c list.c list.h)