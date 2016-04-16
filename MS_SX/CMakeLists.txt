cmake_minimum_required(VERSION 3.5)
project(MS_SX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Problem2_Trie.cpp)
add_executable(MS_SX ${SOURCE_FILES})