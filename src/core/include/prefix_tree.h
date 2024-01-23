/**
 * @file   prefix_tree.h
 * @brief  This file contains the function definitions for prefix_tree.c.
 * @author Matthew C. Lindeman
 * @date   January 22, 2024
 * @bug    None Known.
 * @todo   None Atm.
 */
#ifndef PREFIX_TREE_H
#define PREFIX_TREE_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "main/include/constants_macros.h"

typedef enum {
  UINT8_T,
  UINT16_T,
  UINT32_T,
  UINT64_T,
  CHAR,
} pt_type;

size_t sizeof_pt_type(pt_type type);

typedef struct PREFIX_TREE_T {
  struct PREFIX_TREE_T ** next;
  struct PREFIX_TREE_T * prev;
  void * value;
  pt_type type;
  size_t qty_children;
} prefix_tree;

prefix_tree * init_prefix_tree(pt_type type);
prefix_tree * read_stream_to_prefix_tree(prefix_tree * head, void * stream,
    void * back(void *), void * front(void *));
prefix_tree * process_stream_sequence(prefix_tree * head, void * start,
    void * end);
int value_in_children(prefix_tree * head, void * stream);
void debug_prefix_tree(prefix_tree * pt, int depth);
void free_prefix_tree(prefix_tree * pt);

#endif
