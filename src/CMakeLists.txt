cmake_minimum_required(VERSION 2.8)
project( aisdi  )

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -Wall -o3 -funroll-loops")

#	include relevant include/source dirs
include_directories(${CMAKE_SOURCE_DIR})


#	aisdi test lib
find_library(
	aisdi_LIBS 
	NAMES test_liniowe test_hash test_tree
	PATHS  /home/adam/workspace/aisdi/lib/aisdi
)

find_library(
	aisdi2_LIBS 
	NAMES test_liniowe2 test_hash3 test_tree
	PATHS  /home/adam/workspace/aisdi/lib/aisdi
)


add_subdirectory(gtest)
add_subdirectory(liniowe)
add_subdirectory(hash)
