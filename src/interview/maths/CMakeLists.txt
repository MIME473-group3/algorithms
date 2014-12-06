cmake_minimum_required(VERSION 2.8)
project( bits )

set(SOURCE_FILES 
    7.7_seq357
    sqrt
)

foreach(file ${SOURCE_FILES})
	
	add_executable(${file} ${file}.cpp)
	target_link_libraries(${file} gtest_main utils)
	
endforeach()

