cmake_minimum_required(VERSION 3.1..3.13)

file(GLOB MAIN_DRIVER_SRC "${CMAKE_SOURCE_DIR}/apps/main_driver/src")

file(GLOB MAIN_DRIVER_INC "${CMAKE_SOURCE_DIR}/apps/main_driver/include")

file(GLOB AZLPCODEGEN_INC "${CMAKE_SOURCE_DIR}/compilation/src/backend/azlpcodegen")

file(GLOB MAIN_DRIVER_CPP "${MAIN_DRIVER_SRC}/*.cpp")

if (MSVC_VERSION GREATER_EQUAL "1900")
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
    if (_cpp_latest_flag_supported)
        add_compile_options("/std:c++latest")
    endif()
endif()

set(CMAKE_CXX_FLAGS "-no-pie -g -std=c++17 ${CMAKE_CXX_FLAGS}")

#add_subdirectory(${CMAKE_SOURCE_DIR}/compilation/src/frontend/parsers/astackparser)
#add_subdirectory(${CMAKE_SOURCE_DIR}/compilation/src/frontend/parsers/adataparser)
#add_subdirectory(${CMAKE_SOURCE_DIR}/compilation/src/frontend/parsers/acodeparser)
#add_subdirectory(${CMAKE_SOURCE_DIR}/compilation/src/frontend/parsers/amainparser)

add_executable(main_driver ${MAIN_DRIVER_CPP})
target_include_directories(main_driver PUBLIC ${MAIN_DRIVER_INC} ${AZLPCODEGEN_INC})

target_link_libraries(main_driver PUBLIC astackparser)

target_link_libraries(main_driver PUBLIC adataparser)

target_link_libraries(main_driver PUBLIC acodeparser)

target_link_libraries(main_driver PUBLIC amainparser)

target_link_libraries(main_driver PUBLIC azlpparser)

target_link_libraries(main_driver PUBLIC zlpcodegen)

target_link_libraries(main_driver PUBLIC common)
