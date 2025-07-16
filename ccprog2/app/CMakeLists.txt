add_executable(simple_translator main.c)
target_include_directories(simple_translator
  PRIVATE ${HEADER_DIR})
target_link_libraries(simple_translator
                      PRIVATE data_management
                      PRIVATE translation
                      PRIVATE utils)
