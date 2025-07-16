add_executable(tides_of_manila main.c)
target_include_directories(tides_of_manila
  PRIVATE ${HEADER_DIR})
target_link_libraries(tides_of_manila
                      PRIVATE game_backend)
