add_executable(convex-hull-slow
  main1.c
  io.c
  io.h
)
target_link_libraries(convex-hull-slow
  PRIVATE convex-hull-core
)

add_executable(convex-hull-fast
  main2.c
  io.c
  io.h
)
target_link_libraries(convex-hull-fast
  PRIVATE convex-hull-core
)
