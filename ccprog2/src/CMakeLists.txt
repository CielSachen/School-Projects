add_library(utils STATIC utils.c utils.h)

add_library(data_management STATIC data_management.c data_management.h)
target_link_libraries(data_management
  PUBLIC utils
)

add_library(translation STATIC translation.c translation.h)
target_link_libraries(translation
  PUBLIC data_management
)

add_executable(simple_translator main.c)
target_link_libraries(simple_translator
  PRIVATE data_management
  PRIVATE translation
  PRIVATE utils
)
