add_library(graham_scan_utils SHARED geometry.c sort.c stack.c)
target_include_directories(graham_scan_utils
  PUBLIC ${HEADER_DIR})

add_library(graham_scan_slow SHARED graham_scan1.c)
target_include_directories(graham_scan_slow
  PUBLIC ${HEADER_DIR})
target_link_libraries(graham_scan_slow
                      PUBLIC graham_scan_utils)

add_library(graham_scan_fast SHARED graham_scan2.c)
target_include_directories(graham_scan_fast
  PUBLIC ${HEADER_DIR})
target_link_libraries(graham_scan_fast
                      PUBLIC graham_scan_utils)
