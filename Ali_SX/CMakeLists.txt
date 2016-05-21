cmake_minimum_required(VERSION 3.5)
project(Ali_SX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Problem1.cpp)
add_executable(Ali_SX ${SOURCE_FILES})