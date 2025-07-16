add_library(utils SHARED utils.c)
target_include_directories(utils
  PUBLIC ${HEADER_DIR})

add_library(data_management SHARED data_management.c)
target_include_directories(data_management
  PUBLIC ${HEADER_DIR})
target_link_libraries(data_management
                      PUBLIC utils)

add_library(translation SHARED translation.c)
target_include_directories(translation
  PUBLIC ${HEADER_DIR})
target_link_libraries(translation
                      PUBLIC data_management)
