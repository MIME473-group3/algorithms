cmake_minimum_required(VERSION 2.8)
project( linked_lists )

add_library(linked_list LinkedList.cpp)

set(SOURCE_FILES 
    2.1_removeDuplicates
)

foreach(file ${SOURCE_FILES})
	
	add_executable(${file} ${file}.cpp)
	target_link_libraries(${file} gtest_main utils linked_list)
	
endforeach()

