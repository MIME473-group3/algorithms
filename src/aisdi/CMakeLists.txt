cmake_minimum_required(VERSION 2.8)
project( aisdi )


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

add_subdirectory(timer)

include_directories(${timer_SOURCE_DIR})

add_subdirectory(list_map)
add_subdirectory(hash_map)
add_subdirectory(tree_map)