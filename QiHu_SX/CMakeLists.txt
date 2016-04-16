cmake_minimum_required(VERSION 3.3)
project(QiHu_SX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Problem2.cpp)
add_executable(QiHu_SX ${SOURCE_FILES})