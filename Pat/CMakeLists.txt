cmake_minimum_required(VERSION 3.3)
project(Pat)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES  "Online Map.cpp")
add_executable(Pat ${SOURCE_FILES})