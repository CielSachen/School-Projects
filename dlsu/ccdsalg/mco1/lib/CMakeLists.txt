set(project_include_dir "${PROJECT_SOURCE_DIR}/include")
set(project_header_dir "${project_include_dir}/convex_hull")

add_library(convex-hull-core STATIC
  geometry.c
  "${project_header_dir}/geometry.h"
  graham_scan1.c
  "${project_header_dir}/graham_scan1.h"
  graham_scan2.c
  "${project_header_dir}/graham_scan2.h"
  sort.c
  "${project_header_dir}/sort.h"
  stack.c
  "${project_header_dir}/stack.h"
)
target_include_directories(convex-hull-core
  PUBLIC ${project_include_dir}
)
