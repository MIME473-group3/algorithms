cmake_minimum_required(VERSION 2.8)
project( moderate )

set(SOURCE_FILES 
    17.7_englishRepresentation
)

foreach(file ${SOURCE_FILES})
	
	add_executable(${file} ${file}.cpp)
	target_link_libraries(${file} gtest_main utils)
	
endforeach()

