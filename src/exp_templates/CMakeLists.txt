cmake_minimum_required(VERSION 2.8)
project( exp_templates )

#	include relevant include/source dirs
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(templates templates.cpp)
add_executable(interpreter interpreter.cpp)

