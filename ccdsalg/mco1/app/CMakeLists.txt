add_executable(convex_hull_slow main1.c utils.c utils.h)
target_include_directories(convex_hull_slow
  PRIVATE ${HEADER_DIR})
target_link_libraries(convex_hull_slow
                      PRIVATE graham_scan_slow
                      PRIVATE graham_scan_utils)

add_executable(convex_hull_fast main2.c utils.c utils.h)
target_include_directories(convex_hull_fast
  PRIVATE ${HEADER_DIR})
target_link_libraries(convex_hull_fast
                      PRIVATE graham_scan_fast
                      PRIVATE graham_scan_utils)
