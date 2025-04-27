add_library(console STATIC console.c)
target_include_directories(console
  PUBLIC ${HEADER_DIR})

add_library(prompts STATIC prompts.c)
target_include_directories(prompts
  PUBLIC ${HEADER_DIR})
target_link_libraries(prompts
                      PUBLIC console
                      PUBLIC trading)

add_library(text_graphics STATIC text_graphics.c)
target_include_directories(text_graphics
  PUBLIC ${HEADER_DIR})
target_link_libraries(text_graphics
                      PUBLIC console
                      PUBLIC prompts
                      PUBLIC trading)

add_library(trading STATIC trading.c)
target_include_directories(trading
  PUBLIC ${HEADER_DIR})

add_library(weather STATIC weather.c)
target_include_directories(weather
  PUBLIC ${HEADER_DIR})
