cmake_minimum_required(VERSION 3.1..3.13)

set(ADATAPARSER_SRC "${CMAKE_SOURCE_DIR}/compilation/src/frontend/parsers/adataparser")

set(ADATAPARSER_INC "${CMAKE_SOURCE_DIR}/compilation/src/frontend/parsers/adataparser")

set(COMMON_INC "${CMAKE_SOURCE_DIR}/compilation/src/frontend/common/")

set(VM_INC "${CMAKE_SOURCE_DIR}/runtime/src/vm/")

file(GLOB ADATAPARSER_CPP "${ADATAPARSER_SRC}/*.cpp")

file(GLOB ADATAPARSER_HPP "${ADATAPARSER_INC}/*.hpp")

add_library(adataparser STATIC ${ADATAPARSER_CPP} ${ADATAPARSER_HPP})

set(CMAKE_CXX_FLAGS "-no-pie -std=c++17 ${CMAKE_CXX_FLAGS}")

target_include_directories(adataparser PUBLIC ${ADATAPARSER_INC} ${COMMON_INC} ${VM_INC})

if (MSVC_VERSION GREATER_EQUAL "1900")
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
    if (_cpp_latest_flag_supported)
        add_compile_options("/std:c++latest")
    endif()
endif()

target_compile_features(adataparser PUBLIC cxx_std_17)

target_link_libraries(adataparser PUBLIC common)
