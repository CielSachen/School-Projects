cmake_minimum_required(VERSION 3.15...4.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

project(ConvexHull
        VERSION 1.0.0
        DESCRIPTION "The first major course output (MCO1) for CCDSALG."
        HOMEPAGE_URL "https://github.com/CielSachen/School-Projects/tree/main/ccdsalg/mco1#readme")

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Werror -Wextra -Wpedantic -O2)

set(HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(app)
add_subdirectory(src)

include(FetchContent)

include(CTest)

add_subdirectory(tests)
