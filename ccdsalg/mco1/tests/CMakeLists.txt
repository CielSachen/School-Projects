FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/52eb8108c5bdec04579160ae17225d66034bd723.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

include(GoogleTest)

enable_testing()

add_executable(geometry_test geometry_test.cpp)
target_include_directories(geometry_test
  PRIVATE ${HEADER_DIR})
target_link_libraries(geometry_test
                      PRIVATE graham_scan_utils
                      PUBLIC GTest::gtest_main)
gtest_discover_tests(geometry_test)

add_executable(graham_scan_test graham_scan.cpp)
target_include_directories(graham_scan_test
  PRIVATE ${HEADER_DIR})
target_link_libraries(graham_scan_test
                      PRIVATE graham_scan_slow
                      PRIVATE graham_scan_fast
                      PUBLIC GTest::gtest_main)
gtest_discover_tests(graham_scan_test)

add_executable(sort_test sort_test.cpp)
target_include_directories(sort_test
  PRIVATE ${HEADER_DIR})
target_link_libraries(sort_test
                      PRIVATE graham_scan_utils
                      PUBLIC GTest::gtest_main)
gtest_discover_tests(sort_test)

add_executable(stack_test stack_test.cpp)
target_include_directories(stack_test
  PRIVATE ${HEADER_DIR})
target_link_libraries(stack_test
                      PRIVATE graham_scan_utils
                      PUBLIC GTest::gtest_main)
gtest_discover_tests(stack_test)
