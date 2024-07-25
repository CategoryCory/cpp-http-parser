cmake_minimum_required(VERSION 3.22)
add_library(parser STATIC parser.cpp)
target_include_directories(parser PUBLIC 
                           ${CMAKE_CURRENT_SOURCE_DIR}
                           ${CMAKE_CURRENT_SOURCE_DIR}/../string_utilities)
target_link_libraries(parser PUBLIC string_utilities)
target_compile_definitions(parser PRIVATE HTTP_PARSER_EXPORTS)