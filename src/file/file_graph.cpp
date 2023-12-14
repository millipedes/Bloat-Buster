#include "include/file_graph.h"

namespace file {

auto get_current_level_dirs(void) -> std::vector<std::string> {
  std::vector<std::string> dirs;

  try {
    for (const auto& entry : fs::directory_iterator(file::directory_path)) {
      if(fs::is_directory(entry)) {
        dirs.push_back(entry.path().string());
      } // else if(fs::is_regular_file(entry)) {
        // std::cout << "FILE:" << entry.path().string() << std::endl;
      // }
    }
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  return dirs;
}

} // namespace file
