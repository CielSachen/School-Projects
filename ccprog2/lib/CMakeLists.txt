add_library(utils STATIC utils.c)
target_include_directories(utils
  PUBLIC ${HEADER_DIR})

add_library(data_management STATIC data_management.c)
target_include_directories(data_management
  PUBLIC ${HEADER_DIR})
target_link_libraries(data_management
                      PUBLIC utils)

add_library(translation STATIC translation.c)
target_include_directories(translation
  PUBLIC ${HEADER_DIR})
target_link_libraries(translation
                      PUBLIC utils)
