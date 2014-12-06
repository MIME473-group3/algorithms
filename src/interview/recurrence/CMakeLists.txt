cmake_minimum_required(VERSION 2.8)
project( recurrence )

set(SOURCE_FILES 
    9.5_generatePermutations
    9.6_validParentheses
    9.8_possibleChanges
    9.9_chessQueenPuzzle
    9.10_stackOfBoxes
    9.11_waysOfParentesising
    expressionParser
)

foreach(file ${SOURCE_FILES})
	
	add_executable(${file} ${file}.cpp)
	target_link_libraries(${file} gtest_main utils)
	
endforeach()

