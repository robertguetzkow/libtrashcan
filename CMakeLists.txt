cmake_minimum_required(VERSION 3.10)
project(example)

add_subdirectory(src)

add_executable(example example.c)
if(APPLE)
	find_library(COCOA COCOA)
	find_library(COREFOUNDATION CoreFoundation)
	target_link_libraries(example trashcan ${COCOA} ${COREFOUNDATION})
else()
	target_link_libraries(example trashcan)
endif()
