cmake_minimum_required(VERSION 3.13)
project(example)

add_subdirectory(src)

add_executable(example example.c)
target_link_libraries(example trashcan)
