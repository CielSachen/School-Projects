add_library(game_backend SHARED console.c prompts.c text_graphics.c trading.c weather.c)
target_include_directories(game_backend
  PUBLIC ${HEADER_DIR})

