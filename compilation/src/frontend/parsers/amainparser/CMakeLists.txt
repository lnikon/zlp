cmake_minimum_required(VERSION 3.1..3.13)

set(AMAINPARSER_SRC "${CMAKE_SOURCE_DIR}/compilation/src/frontend/parsers/amainparser")

set(AMAINPARSER_INC "${CMAKE_SOURCE_DIR}/compilation/src/frontend/parsers/amainparser")

set(COMMON_INC "${CMAKE_SOURCE_DIR}/compilation/src/frontend/common/")

set(VM_INC "${CMAKE_SOURCE_DIR}/runtime/src/vm/")

file(GLOB AMAINPARSER_CPP "${AMAINPARSER_SRC}/*.cpp")

file(GLOB AMAINPARSER_HPP "${AMAINPARSER_INC}/*.hpp")

add_library(amainparser STATIC ${AMAINPARSER_CPP} ${AMAINPARSER_HPP})

set(CMAKE_CXX_FLAGS "-no-pie -std=c++17 ${CMAKE_CXX_FLAGS}")

target_include_directories(amainparser PUBLIC ${AMAINPARSER_INC} ${COMMON_INC} ${VM_INC})

if (MSVC_VERSION GREATER_EQUAL "1900")
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
    if (_cpp_latest_flag_supported)
        add_compile_options("/std:c++latest")
    endif()
endif()

target_compile_features(amainparser PUBLIC cxx_std_17)

target_link_libraries(amainparser PUBLIC common)
