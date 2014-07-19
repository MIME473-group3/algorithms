cmake_minimum_required(VERSION 2.8)
project( quicksort )

#	include relevant include/source dirs
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

#	Set up google test
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

#	Compile gtest
add_executable(test_${PROJECT_NAME} test.cpp)
target_link_libraries(test_${PROJECT_NAME} gtest_main)
add_custom_command(TARGET test_${PROJECT_NAME} POST_BUILD COMMAND test_${PROJECT_NAME})



add_executable(exe_template template.cpp)
