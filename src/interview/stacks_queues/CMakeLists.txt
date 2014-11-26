cmake_minimum_required(VERSION 2.8)
project( stacks_queues )

add_library(stack_queue Stack.cpp)

set(SOURCE_FILES 
    3.4_hanoiTowers
)

foreach(file ${SOURCE_FILES})
	
	add_executable(${file} ${file}.cpp)
	target_link_libraries(${file} gtest_main utils stack_queue)
	
endforeach()

