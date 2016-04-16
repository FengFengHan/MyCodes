cmake_minimum_required(VERSION 3.3)
project(Temp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES hiho3.cpp)
add_executable(Temp ${SOURCE_FILES})