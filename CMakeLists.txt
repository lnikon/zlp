cmake_minimum_required(VERSION 3.1..3.13)
project(zpl)

set(CMAKE_CXX_FLAGS "-g -std=c++17 -fsanitize=address -std=c11 -lasan ${CMAKE_CXX_FLAGS}")

add_subdirectory(compilation)
add_subdirectory(apps)

