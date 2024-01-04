#ifndef PREFIX_TREE_H
#define PREFIX_TREE_H

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main/include/constants_macros.h"

typedef enum {
  UINT8_T,
  UINT16_T,
  UINT32_T,
  UINT64_T,
  CHAR,
  END_OF_SEQ,
} pt_type;

int is_valid_pt_type(pt_type type);
const char * pt_type_to_string(pt_type type);
uint32_t sizeof_pt_type(pt_type type);

typedef struct PREFIX_TREE_T {
  struct PREFIX_TREE_T ** next;
  struct PREFIX_TREE_T * prev;
  void * value;
  pt_type type;
  uint16_t qty_children;
} prefix_tree;

prefix_tree * init_prefix_tree(pt_type type);
prefix_tree * read_stream_to_prefix_tree(prefix_tree * head, void * stream,
    void * iterator(void *));
prefix_tree * append_tree(prefix_tree * head, void * start, void * end);
void debug_prefix_tree(prefix_tree * pt, int depth);
void free_prefix_tree(prefix_tree * pt);

void * words(void * value);
void * min_ptr(int count, ...);

#endif
