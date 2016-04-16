cmake_minimum_required(VERSION 3.3)
project(MGJ_SX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Problem1.cpp test.cpp)
add_executable(MGJ_SX ${SOURCE_FILES})