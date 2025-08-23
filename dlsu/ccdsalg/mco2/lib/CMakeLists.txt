set(project_include_dir "${PROJECT_SOURCE_DIR}/include")
set(project_header_dir "${project_include_dir}/social_network")

add_library(social-network-core STATIC
  graph.c
  "${project_header_dir}/graph.h"
  traversal.c
  "${project_header_dir}/traversal.h"
  queue.c
  "${project_header_dir}/queue.h"
)
target_include_directories(social-network-core
  PUBLIC ${project_include_dir}
)
