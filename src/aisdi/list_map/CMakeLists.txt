cmake_minimum_required(VERSION 2.8)
project( liniowe )

#	include relevant include/source dirs
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

#	prepare a lib
add_library(lib_${PROJECT_NAME} asd.cc)

#	prepare aisdi's exe
add_executable(aisdi_${PROJECT_NAME} main.cc)
target_link_libraries(aisdi_${PROJECT_NAME} lib_${PROJECT_NAME} lib_timer ${liniowe_LIB})

#	Set up google test
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
enable_testing()

#	Compile gtest
add_executable(test_${PROJECT_NAME} test.cpp)
target_link_libraries(test_${PROJECT_NAME} gtest gtest_main lib_${PROJECT_NAME})
add_test(test_${PROJECT_NAME} test_${PROJECT_NAME})
add_custom_command(TARGET test_${PROJECT_NAME} POST_BUILD COMMAND test_${PROJECT_NAME})
