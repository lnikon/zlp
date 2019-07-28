cmake_minimum_required(VERSION 3.1..3.13)

set(AZLPPARSER_SRC "${CMAKE_SOURCE_DIR}/compilation/src/frontend/azlpparser/")

set(AZLPPARSER_INC "${CMAKE_SOURCE_DIR}/compilation/include/frontend/azlpparser/")

set(COMMON_INC "${CMAKE_SOURCE_DIR}/compilation/include/frontend/common/")

set(VM_INC "${CMAKE_SOURCE_DIR}/runtime/include/vm/")

file(GLOB AZLPPARSER_CPP "${AZLPPARSER_SRC}/*.cpp")

file(GLOB AZLPPARSER_HPP "${AZLPPARSER_INC}/*.hpp")

add_library(azlpparser STATIC ${AZLPPARSER_CPP} ${AZLPPARSER_HPP})

set(CMAKE_CXX_FLAGS "-no-pie -std=c++17 ${CMAKE_CXX_FLAGS}")

target_include_directories(azlpparser PUBLIC ${AZLPPARSER_INC} ${COMMON_INC} ${VM_INC})

if (MSVC_VERSION GREATER_EQUAL "1900")
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
    if (_cpp_latest_flag_supported)
        add_compile_options("/std:c++latest")
    endif()
endif()

target_compile_features(azlpparser PUBLIC cxx_std_17)

