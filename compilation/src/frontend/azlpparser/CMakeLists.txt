cmake_minimum_required(VERSION 3.1..3.13)

set(AZLPPARSER_SRC "${CMAKE_SOURCE_DIR}/compilation/src/frontend/azlpparser/")

set(AZLPPARSER_INC "${CMAKE_SOURCE_DIR}/compilation/include/frontend/azlpparser/")

set(COMMON_INC "${CMAKE_SOURCE_DIR}/compilation/include/frontend/common/")

set(VM_INC "${CMAKE_SOURCE_DIR}/runtime/include/vm/")

file(GLOB AZLPPARSER_CPP "${AZLPPARSER_SRC}/*.cpp")

file(GLOB AZLPPARSER_HPP "${AZLPPARSER_INC}/*.hpp")

add_library(azlpparser STATIC ${AZLPPARSER_CPP} ${AZLPPARSER_HPP})

target_include_directories(azlpparser PUBLIC ${AZLPPARSER_INC} ${COMMON_INC} ${VM_INC})

target_compile_features(azlpparser PUBLIC cxx_std_17)
