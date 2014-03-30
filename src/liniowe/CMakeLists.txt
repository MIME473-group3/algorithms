cmake_minimum_required(VERSION 2.8)
project( liniowe )

#	include relevant include/source dirs
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

#	prepare a lib
add_library(liniowe_asd asd.cc timer.cc)

#	prepare aisdi's exe
add_executable(liniowe_aisdi main.cc)
target_link_libraries(liniowe_aisdi liniowe_asd ${aisdi_LIBS})

#	Set up google test
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
enable_testing()

#	Compile gtest
add_executable(liniowe_test test.cpp)
target_link_libraries(liniowe_test gtest gtest_main liniowe_asd)
add_test(liniowe_test liniowe_test)
add_custom_command(TARGET liniowe_test POST_BUILD COMMAND liniowe_test)
