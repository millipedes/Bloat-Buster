#include "core/include/prefix_tree.h"

int main(void) {

  prefix_tree * head = init_prefix_tree(CHAR);
  head = read_stream_to_prefix_tree(head, "hello world i exist", words);
  debug_prefix_tree(head, 0);
  free_prefix_tree(head);

  return 0;
}
