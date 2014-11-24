cmake_minimum_required(VERSION 2.8)
project( utils )

set(SOURCE_FILES 
    Utils.cpp
    StringBuilder.cpp
)

add_library(utils ${SOURCE_FILES})
