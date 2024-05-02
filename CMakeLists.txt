cmake_minimum_required(VERSION 3.13)
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)
project(pico_codan)
pico_sdk_init()

file(GLOB_RECURSE SRC "src/*.cpp")
file(GLOB_RECURSE LIB "lib/*.cpp" "lib/*.c")

add_executable(${PROJECT_NAME} ${SRC} ${LIB})

target_link_libraries(${PROJECT_NAME} pico_stdlib pico_multicore)

target_include_directories(${PROJECT_NAME} PRIVATE "lib/")

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)
pico_add_extra_outputs(${PROJECT_NAME})