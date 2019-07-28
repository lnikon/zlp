cmake_minimum_required(VERSION 3.1..3.13)

set(COMMON_SRC "${CMAKE_SOURCE_DIR}/compilation/src/frontend/common")

set(COMMON_INC "${CMAKE_SOURCE_DIR}/compilation/include/frontend/common")

set(VM_INC "${CMAKE_SOURCE_DIR}/runtime/include/vm")

file(GLOB COMMON_CPP "${COMMON_SRC}/*.cpp")

file(GLOB COMMON_HPP "${COMMON_INC}/*.hpp")

set(CMAKE_CXX_FLAGS "-no-pie -std=c++17 ${CMAKE_CXX_FLAGS}")

add_library(common STATIC ${COMMON_CPP} ${COMMON_HPP})

target_include_directories(common PUBLIC ${COMMON_INC} ${VM_INC})

target_compile_features(common PUBLIC cxx_std_17)
