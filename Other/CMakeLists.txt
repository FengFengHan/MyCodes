cmake_minimum_required(VERSION 3.5)
project(Other)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES BDStar_D.cpp)
add_executable(Other ${SOURCE_FILES})