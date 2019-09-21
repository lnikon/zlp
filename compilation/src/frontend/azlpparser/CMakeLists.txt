cmake_minimum_required(VERSION 3.1..3.13)

## Begin COMMON_INC
set(COMMON_INC "${CMAKE_SOURCE_DIR}/compilation/src/frontend/common/")
## End COMMON_INC

##
set(PARSERS_PATH "${CMAKE_SOURCE_DIR}/compilation/src/frontend/parsers/")

set(STACK_INC "${PARSERS_PATH}/astackparser")
file(GLOB STACK_HPP "${STACK_INC}/*.hpp")

set(DATA_INC "${PARSERS_PATH}/adataparser")
file(GLOB DATA_HPP "${DATA_INC}/*.hpp")

set(CODE_INC "${PARSERS_PATH}/acodeparser")
file(GLOB CODE_HPP "${CODE_INC}/*.hpp")

set(MAIN_INC "${PARSERS_PATH}/amainparser")
file(GLOB MAIN_HPP "${MAIN_INC}/*.hpp")
##

##
set(VM_INC "${CMAKE_SOURCE_DIR}/runtime/src/vm/")
##

##
set(AZLPPARSER_SRC "${CMAKE_SOURCE_DIR}/compilation/src/frontend/azlpparser/")
set(AZLPPARSER_INC "${CMAKE_SOURCE_DIR}/compilation/src/frontend/azlpparser/")
file(GLOB AZLPPARSER_CPP "${AZLPPARSER_SRC}/*.cpp")
file(GLOB AZLPPARSER_HPP "${AZLPPARSER_INC}/*.hpp")

add_library(azlpparser STATIC ${AZLPPARSER_CPP} ${AZLPPARSER_HPP})
##

set(CMAKE_CXX_FLAGS "-no-pie -std=c++17 ${CMAKE_CXX_FLAGS}")

target_include_directories(azlpparser PUBLIC 	${AZLPPARSER_INC} 
						${COMMON_INC} 
						${VM_INC}
						${STACK_INC}
						${DATA_INC}
						${CODE_INC}
						${MAIN_INC})

if (MSVC_VERSION GREATER_EQUAL "1900")
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
    if (_cpp_latest_flag_supported)
        add_compile_options("/std:c++latest")
    endif()
endif()

target_compile_features(azlpparser PUBLIC cxx_std_17)

target_link_libraries(azlpparser PUBLIC common)
target_link_libraries(azlpparser PUBLIC astackparser)
target_link_libraries(azlpparser PUBLIC adataparser)
target_link_libraries(azlpparser PUBLIC acodeparser)
target_link_libraries(azlpparser PUBLIC amainparser)
