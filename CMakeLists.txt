cmake_minimum_required(VERSION 3.12)
project(bloat_buster)

# Source files
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(TEST_DIR "${CMAKE_SOURCE_DIR}/tests")
set(SRC_FILES
    ${SRC_DIR}/core/prefix_tree.c
    ${SRC_DIR}/core/string_lib.c
    ${SRC_DIR}/core/pointer_arithmetic.c
    ${SRC_DIR}/file/file_graph.c
)

# Include directories
include_directories(
    ${SRC_DIR}
)

add_executable(bloat_buster ${SRC_FILES} ${SRC_DIR}/main/main.c)

# test flags for executable (comment if performance is required)
target_compile_options(bloat_buster PRIVATE -Wall -Wextra -g)
