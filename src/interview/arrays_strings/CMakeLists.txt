cmake_minimum_required(VERSION 2.8)
project( arrays_strings )

set(SOURCE_FILES 
	1.1_onlyUniqueChars
	1.2_reverseString
	1.3_isPermutation
	1.4_replaceChar
	1.5_stringCompression
	1.6_rotate90
	1.7_zeroRowsCols
	1.8_isRotation
	reverseWordOrder
	oilSpills
	findElemInRotatedArray
	bestProfitStock
)

foreach(file ${SOURCE_FILES})
	
	add_executable(${file} ${file}.cpp)
	target_link_libraries(${file} gtest_main utils)
	
endforeach()

