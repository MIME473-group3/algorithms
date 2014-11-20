cmake_minimum_required(VERSION 2.8)
project( timer )

#	include relevant include/source dirs
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

#	prepare a lib
add_library(lib_${PROJECT_NAME} timer.cc)