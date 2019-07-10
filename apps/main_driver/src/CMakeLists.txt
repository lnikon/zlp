cmake_minimum_required(VERSION 3.1..3.13)

file(GLOB MAIN_DRIVER_SRC "${CMAKE_SOURCE_DIR}/apps/main_driver/src")

file(GLOB MAIN_DRIVER_INC "${CMAKE_SOURCE_DIR}/apps/main_driver/include")

file(GLOB MAIN_DRIVER_CPP "${MAIN_DRIVER_SRC}/*.cpp")

add_executable(main_driver ${MAIN_DRIVER_CPP})
target_include_directories(main_driver PUBLIC ${MAIN_DRIVER_INC})

target_link_libraries(main_driver PUBLIC azlpparser)

target_link_libraries(main_driver PUBLIC common)

# target_link_libraries(main_driver PUBLIC vm)
