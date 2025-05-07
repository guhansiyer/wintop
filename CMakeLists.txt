cmake_minimum_required(VERSION 3.10)
project(wintop)

set(CMAKE_C_STANDARD 99)
add_compile_options(/W3)

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(
    wintop
    src/main.c
    src/thread_inspector.c
    src/utils.c
)

target_link_libraries(wintop psapi)