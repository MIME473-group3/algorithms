cmake_minimum_required(VERSION 2.8)
project( interview )

include_directories( ${gtest_INCLUDE_DIR} )



set(SOURCE_FILES 
	1.1_onlyUniqueChars
	1.2_reverseString
	1.3_isPermutation
	1.4_replaceChar
	1.5_stringCompression
)

foreach(file ${SOURCE_FILES})
	
	add_executable(${file} ${file}.cpp)
	target_link_libraries(${file} gtest_main)
	#add_custom_command(TARGET ${file} POST_BUILD COMMAND test)
	
endforeach()

