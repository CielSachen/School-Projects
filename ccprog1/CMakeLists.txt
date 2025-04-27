cmake_minimum_required(VERSION 3.15...4.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

project(TidesOfManila
        VERSION 1.0.0
        LANGUAGES C)

set(CMAKE_C_STANDARD 99)

add_compile_options(-Wall -Werror -Wextra -Wpedantic -O2)

set(HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(lib)
add_subdirectory(src)
