cmake_minimum_required(VERSION 3.22)

# Set project name and specify language
project(http_parser VERSION 0.1 LANGUAGES CXX)

# Set C Standard and flags
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -O2")

# Add project subdirectories
add_subdirectory(src/parser)
add_subdirectory(src/string_utilities)

# Find required packages
# find_package(PkgConfig REQUIRED)
# pkg_check_modules(GLIB REQUIRED glib-2.0)

# Include required directories
# include_directories(${GLIB_INCLUDE_DIRS})

# Add executable file
add_executable(main src/main.cpp)

# Add target libraries and include directories
target_link_libraries(main PUBLIC parser string_utilities)
target_include_directories(main PUBLIC 
                           "${PROJECT_SOURCE_DIR}/src/parser"
                           "${PROJECT_SOURCE_DIR}/src/string_utilities")

# Add GLib compiler flags
# target_compile_options(main PRIVATE ${GLIB_CFLAGS_OTHER} ${GIO_CFLAGS_OTHER})