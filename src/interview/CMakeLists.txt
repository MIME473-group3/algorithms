cmake_minimum_required(VERSION 2.8)
project( interview )

include_directories( 
    ${gtest_INCLUDE_DIR} 
    ${CMAKE_CURRENT_SOURCE_DIR}
    
)

add_subdirectory(utils)
include_directories(${utils_SOURCE_DIR})
add_subdirectory(arrays_strings)
add_subdirectory(linked_lists)
add_subdirectory(stacks_queues)
add_subdirectory(moderate)