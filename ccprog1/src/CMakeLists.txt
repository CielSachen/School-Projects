add_library(game_backend STATIC
  console.c
  console.h
  prompts.c
  prompts.h
  text_graphics.c
  text_graphics.h
  trading.c
  trading.h
  weather.c
  weather.h
)

add_executable(tides_of_manila main.c)
target_link_libraries(tides_of_manila
  PRIVATE game_backend
)
