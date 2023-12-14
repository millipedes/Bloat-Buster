cmake_minimum_required(VERSION 3.12)
project(bloat_buster)

set(CMAKE_CXX_STANDARD 17)

# Source files
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(TEST_DIR "${CMAKE_SOURCE_DIR}/tests")
set(SRC_FILES
    ${SRC_DIR}/file/file_graph.cpp
)

# Include directories
include_directories(
    ${SRC_DIR}
)

# Add executable
add_executable(bloat_buster ${SRC_FILES} ${SRC_DIR}/main/main.cpp)

# test flags for executable (comment if performance is required)
target_compile_options(bloat_buster PRIVATE -Wall -Wextra -g)
