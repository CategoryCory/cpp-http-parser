cmake_minimum_required(VERSION 3.22)
add_library(string_utilities STATIC string_utilities.cpp)
target_include_directories(string_utilities PUBLIC 
                           ${CMAKE_CURRENT_SOURCE_DIR}
                           ${CMAKE_CURRENT_SOURCE_DIR}/../types)
target_compile_definitions(string_utilities PRIVATE STRING_UTILITIES_EXPORTS)