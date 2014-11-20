cmake_minimum_required(VERSION 2.8)
project( name )

#    Set CMake Install Path
set (CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR} CACHE PATH "default install path" FORCE )

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_COMPILER_FLAGS} -std=c++11)

#       CMake module path for custom module finding
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/modules)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

#	include relevant include/source dirs
include_directories(${CMAKE_SOURCE_DIR})

find_package(Glog)
include_directories(${GLOG_INCLUDE_DIRS})

#	aisdi test lib
find_library(
	liniowe_LIB
	NAMES test_liniowe #test_liniowe2
	PATHS ${CMAKE_SOURCE_DIR}/../lib/aisdi
)

find_library(
	hash_LIB
	NAMES test_hash
	PATHS ${CMAKE_SOURCE_DIR}/../lib/aisdi
)

find_library(
	hash3_LIB
	NAMES test_hash3
	PATHS ${CMAKE_SOURCE_DIR}/../lib/aisdi
)

find_library(
	tree_LIB
	NAMES test_tree
	PATHS ${CMAKE_SOURCE_DIR}/../lib/aisdi
)

add_subdirectory(gtest)
add_subdirectory(timer)

include_directories(${timer_SOURCE_DIR})

add_subdirectory(liniowe)
add_subdirectory(hash)
add_subdirectory(tree)
add_subdirectory(sort)

add_executable(count_ones count_ones.cpp)
