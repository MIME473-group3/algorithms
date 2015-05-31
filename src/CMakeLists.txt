cmake_minimum_required(VERSION 2.8)
project( algorithms )

#    Set CMake Install Path
set (CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR} CACHE PATH "default install path" FORCE )

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_COMPILER_FLAGS} -std=c++11)

#       CMake module path for custom module finding
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/modules)

#	include relevant include/source dirs
include_directories(${CMAKE_SOURCE_DIR})

find_package(Glog)
include_directories(${GLOG_INCLUDE_DIRS})

add_subdirectory(gtest)


add_subdirectory(aisdi)
add_subdirectory(sorting_algos)
add_subdirectory(interview)

add_executable(count_ones count_ones.cpp)
add_executable(1Dto3D 1Dto3D.cpp)
target_link_libraries(1Dto3D gtest gtest_main)
 
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})