cmake_minimum_required(VERSION 3.15...4.1)

project(convex-hull-calculator
  VERSION 1.0.0
  DESCRIPTION "A program that finds the convex hull from a set of points on a Cartesian plane."
  HOMEPAGE_URL "https://github.com/CielSachen/School-Projects/tree/main/ccdsalg/mco1#readme"
  LANGUAGES C
)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

add_compile_options(-Wall -Werror -Wextra -Wpedantic)

add_subdirectory(lib)
add_subdirectory(src)
