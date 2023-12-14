#pragma once

#include <iostream>
#include <filesystem>
#include <vector>

// For GCC and Clang, use experimental::filesystem
// For MSVC, the experimental namespace is not needed
#ifdef __cpp_lib_filesystem
  namespace fs = std::filesystem;
#elif __cpp_lib_experimental_filesystem
  namespace fs = std::experimental::filesystem;
#endif

namespace file {

static const std::string directory_path = ".";

auto get_all_sub_dirs(std::string) -> void;
auto get_current_level_dirs(void) -> std::vector<std::string>;

}
