cmake_minimum_required(VERSION 3.15)
project(tree_hashmap)

set(CMAKE_CXX_STANDARD 14)

add_executable(tree_hashmap main.c btree.c btree.h hashmap.c hashmap.h map.h)