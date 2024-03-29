cmake_minimum_required(VERSION 3.1..3.13)

set(ZLPCODEGEN_SRC "${CMAKE_SOURCE_DIR}/compilation/src/backend/zlpcodegen/")

set(ZLPCODEGEN_INC "${CMAKE_SOURCE_DIR}/compilation/src/backend/zlpcodegen/")

set(AZLPPARSER_INC "${CMAKE_SOURCE_DIR}/compilation/src/frontend/azlpparser/")

set(COMMON_INC "${CMAKE_SOURCE_DIR}/compilation/src/frontend/common/")

set(VM_INC "${CMAKE_SOURCE_DIR}/runtime/src/vm/")

file(GLOB ZLPCODEGEN_CPP "${ZLPCODEGEN_SRC}/*.cpp")

file(GLOB ZLPCODEGEN_HPP "${ZLPCODEGEN_INC}/*.hpp")

set(CMAKE_CXX_FLAGS "-no-pie -std=c++17 ${CMAKE_CXX_FLAGS}")

if (MSVC_VERSION GREATER_EQUAL "1900")
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
if (_cpp_latest_flag_supported)
add_compile_options("/std:c++latest")
endif()
endif()

add_library(zlpcodegen STATIC ${ZLPCODEGEN_CPP} ${ZLPCODEGEN_HPP})

## pthread support
find_package (Threads)
target_link_libraries(zlpcodegen PUBLIC ${CMAKE_THREAD_LIBS_INIT})
## END pthread suppors

target_include_directories(zlpcodegen PUBLIC ${ZLPCODEGEN_INC} ${AZLPPARSER_INC} ${COMMON_INC} ${VM_INC})

target_compile_features(zlpcodegen PUBLIC cxx_std_17)

target_link_libraries(zlpcodegen PUBLIC common)

target_link_libraries(zlpcodegen PUBLIC azlpparser)

