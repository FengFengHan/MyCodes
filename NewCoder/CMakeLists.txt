cmake_minimum_required(VERSION 3.5)
project(NewCoder)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Problem4.cpp)
add_executable(NewCoder ${SOURCE_FILES})