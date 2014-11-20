cmake_minimum_required(VERSION 2.8)
project( hash )

#	include relevant include/source dirs
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3")

#	Set up google test
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
enable_testing()

#	Compile gtest
add_executable(test_${PROJECT_NAME} test.cpp)
target_link_libraries(test_${PROJECT_NAME} gtest gtest_main)
add_test(test_${PROJECT_NAME} test_${PROJECT_NAME})
add_custom_command(TARGET test_${PROJECT_NAME} POST_BUILD COMMAND test_${PROJECT_NAME})
