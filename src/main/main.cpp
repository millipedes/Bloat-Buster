#include "file/include/file_graph.h"

int main(void) {

  auto dirs = file::get_current_level_dirs();
  for(const auto& d : dirs)
    std::cout << d << std::endl;

  return 0;
}
