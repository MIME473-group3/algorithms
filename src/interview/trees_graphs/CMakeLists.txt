cmake_minimum_required(VERSION 2.8)
project( trees_graph )

add_library(tree_graph Graph.cpp)

set(SOURCE_FILES 
    4.1_isBalanced
    4.2_pathBetweenTwoNodes
    sumBetweenStrings
    taskScheduler
)

foreach(file ${SOURCE_FILES})
	
	add_executable(${file} ${file}.cpp)
	target_link_libraries(${file} gtest_main utils tree_graph)
	
endforeach()

