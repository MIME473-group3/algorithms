cmake_minimum_required(VERSION 2.8)
project( exp_templates )

#	include relevant include/source dirs
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(misc misc.cpp)
add_executable(interpreter interpreter.cpp)
add_executable(compiler compiler.cpp)
add_executable(initializer initializer.cpp)
