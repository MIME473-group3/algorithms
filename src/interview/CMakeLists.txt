cmake_minimum_required(VERSION 2.8)
project( interview )

include_directories( 
    ${gtest_INCLUDE_DIR} 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(utils Utils.cpp)

add_subdirectory(arrays_strings)
add_subdirectory(linked_lists)