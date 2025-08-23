add_executable(social-network
  main.c
  io.c
  io.h
)
target_link_libraries(social-network
  PRIVATE social-network-core
)

add_executable(social-network-bonus
  bonus.c
  io.c
  io.h
)
target_link_libraries(social-network-bonus
  PRIVATE social-network-core
)
