cmake_minimum_required(VERSION 3.1..3.13)
project(zpl)

set(CMAKE_CXX_FLAGS "-g -std=c++17 ${CMAKE_CXX_FLAGS}")

add_subdirectory(compilation)
add_subdirectory(apps)

