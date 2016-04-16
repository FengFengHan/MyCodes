cmake_minimum_required(VERSION 3.5)
project(hiho)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES 1062LCA_1.cpp)
add_executable(hiho ${SOURCE_FILES})