cmake_minimum_required(VERSION 3.5)
project(BDstar)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES BDString.cpp)
add_executable(BDstar ${SOURCE_FILES})