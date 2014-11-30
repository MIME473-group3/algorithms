cmake_minimum_required(VERSION 2.8)
project( bits )

set(SOURCE_FILES 
    5.1_insertInto
    5.2_toFixedPointString
    5.3_nextSmallerGreater
)

foreach(file ${SOURCE_FILES})
	
	add_executable(${file} ${file}.cpp)
	target_link_libraries(${file} gtest_main utils)
	
endforeach()

