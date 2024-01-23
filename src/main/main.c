#include "core/include/string_lib.h"
#include "core/include/prefix_tree.h"

int main(void) {
  prefix_tree * head = init_prefix_tree(CHAR);
  // head = read_stream_to_prefix_tree(head, "#include \"somestring\"\nthis is a new line", includes, new_line);
  head = read_stream_to_prefix_tree(head, "#include \"somestring\"\n#include \"someotherstring\"\n", includes, new_line);
  // head = read_stream_to_prefix_tree(head, "Hello Helium i\nthis is a new line", identity, words);
  debug_prefix_tree(head, 0);
  free_prefix_tree(head);

  return 0;
}
