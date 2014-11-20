cmake_minimum_required(VERSION 2.8)
project( interview )

include_directories( ${gtest_INCLUDE_DIR} )



set(SOURCE_FILES 
	onlyUniqueChars
)

foreach(file ${SOURCE_FILES})
	
	add_executable(${file} ${file}.cpp)
	target_link_libraries(${file} gtest_main)
	add_custom_command(TARGET ${file} POST_BUILD COMMAND test)
	
endforeach()

