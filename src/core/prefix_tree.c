/**
 * @file   prefix_tree.c
 * @brief  This file contains the functions related building/mainting the
 *         prefix_tree.
 * @author Matthew C. Lindeman
 * @date   January 22, 2024
 * @bug    None Known.
 * @todo   None Atm.
 */
#include "include/prefix_tree.h"

/**
 * This function will return the type of a particular prefix_tree type. This is
 * helpful with the pointer arithmetic.
 * @param type - The type of the prefix_tree which the user wishes to find size
 *               of.
 * @return  .\ - The size of the given type.
 */
size_t sizeof_pt_type(pt_type type) {
  switch(type) {
    case UINT8_T:    return sizeof(uint8_t);
    case UINT16_T:   return sizeof(uint16_t);
    case UINT32_T:   return sizeof(uint32_t);
    case UINT64_T:   return sizeof(uint64_t);
    case CHAR:       return sizeof(char);
    default:         return 0;
  }
}

/**
 * This function will initialize an empty prefix_tree with no members of the
 * given type.
 * @param type - The type to initialize the tree to.
 * @return  pt - The newly initialized prefix_tree.
 */
prefix_tree * init_prefix_tree(pt_type type) {
  prefix_tree * pt = calloc(1, sizeof(struct PREFIX_TREE_T));
  pt->next = NULL;
  pt->prev = NULL;
  pt->value = NULL;
  pt->type = type;
  pt->qty_children = 0;
  return pt;
}

/**
 * This function will take a head of a given prefix_tree and make a prefix_tree
 * from it given a stream and an iterator.  N.B. This iterator ought to return
 * the first character in the next desired start of the stream and NULL when the
 * parsing has reached its end.
 * @param     head - The head of the prefix_tree the user wishes to build.
 * @param   stream - The start of the stream which the user wishes to parse.
 * @param iterator - The iterator which ought to return the first occurance of
 *                   the next desired parse character.
 * @return    head - The newly built parse tree.
 */
prefix_tree * read_stream_to_prefix_tree(prefix_tree * head, void * stream,
    void * back(void *), void * front(void *)) {
  void * current_stream = stream;
  void * next_stream = stream;
  while(next_stream != NULL && current_stream != NULL) {
    current_stream = back(next_stream);
    next_stream = front(next_stream);
    if(current_stream == NULL || next_stream == NULL)
      break;
    head = process_stream_sequence(head, current_stream, next_stream);
  }
  return head;
}

/**
 * This function will process the stream from start to end with the given head
 * of the parse tree.
 * @param  head - The head of the parse tree.
 * @param start - The start of the subsequence of the stream.
 * @param   end - The end of the subsequence of the stream.
 * @return head - The head of the newly formed parse tree.
 */
prefix_tree * process_stream_sequence(prefix_tree * head, void * start,
    void * end) {
  prefix_tree * tmp = head;
  int child_index = -1;
  while(end != NULL && start < end - sizeof_pt_type(head->type)) {
    if((child_index = value_in_children(tmp, start)) != -1) {
      tmp = tmp->next[child_index];
    } else {
      prefix_tree * new_tail = init_prefix_tree(head->type);

      // Alloc for New Child
      tmp->qty_children++;
      if(tmp->next)
        tmp->next = realloc(tmp->next, tmp->qty_children
            * sizeof(struct PREFIX_TREE_T *));
      else
        tmp->next = calloc(1, sizeof(struct PREFIX_TREE_T *));

      // Link the List
      tmp->next[tmp->qty_children - 1] = new_tail;
      new_tail->prev = tmp;

      // Assign new_tail's value
      switch(head->type) {
        case UINT8_T:
          new_tail->value = calloc(1, sizeof(uint8_t));
          *(uint8_t *)(new_tail->value) = *(uint8_t *)(start);
          break;
        case UINT16_T:
          new_tail->value = calloc(1, sizeof(uint16_t));
          *(uint16_t *)(new_tail->value) = *(uint16_t *)(start);
          break;
        case UINT32_T:
          new_tail->value = calloc(1, sizeof(uint32_t));
          *(uint32_t *)(new_tail->value) = *(uint32_t *)(start);
          break;
        case UINT64_T:
          new_tail->value = calloc(1, sizeof(uint64_t));
          *(uint64_t *)(new_tail->value) = *(uint64_t *)(start);
          break;
        case CHAR:
          new_tail->value = calloc(1, sizeof(char));
          *(char *)(new_tail->value) = *(char *)(start);
          break;
        default:
          fprintf(stderr, "[APPEND_TREE]: Unrecognized Type\nExiting\n");
          exit(1);
      }

      tmp = new_tail;
    }

    start += sizeof_pt_type(tmp->type);
  }
  return head;
}

/**
 * This function will determine if a particular value is in the immediate child
 * of a prefix tree, if it is then it will return the int index of that child
 * otherwise it will return -1.
 * @param   head - The head of the prefix_tree to check children of.
 * @param stream - The stream to check against.
 * @return    -1 - Not Found.
 *          else - Found.
 */
int value_in_children(prefix_tree * head, void * stream) {
  if(head) {
    if(head->next) {
      for(int i = 0; i < (int)head->qty_children; i++) {
        switch(head->type) {
          case UINT8_T:
            if(*(uint8_t *)(head->next[i]->value) == *(uint8_t *)stream)
              return i;
            break;
          case UINT16_T:
            if(*(uint16_t *)(head->next[i]->value) == *(uint16_t *)stream)
              return i;
            break;
          case UINT32_T:
            if(*(uint32_t *)(head->next[i]->value) == *(uint32_t *)stream)
              return i;
            break;
          case UINT64_T:
            if(*(uint64_t *)(head->next[i]->value) == *(uint64_t *)stream)
              return i;
            break;
          case CHAR:
            if(*(char *)(head->next[i]->value) == *(char *)stream)
              return i;
            break;
          default:
            fprintf(stderr, "[APPEND_TREE]: Unrecognized Type\nExiting\n");
            exit(1);
        }
      }
    } else return -1;
  } else return -1;
  return -1;
}

/**
 * This function is used to debug a particular prefix_tree.
 * @param    pt - The prefix_tree which the user wishes to debug.
 * @param depth - The qty of spaces to be printed before the data of the
 *                prefix_tree (i.e. the user can see parent/children easier this
 *                way).
 * @return  N/a
 */
void debug_prefix_tree(prefix_tree * pt, int depth) {
  if(pt) {
    PRINT_C_N(SPACE, depth)
    if(pt->value) {
      switch(pt->type) {
        case UINT8_T:    printf("%u\n",  *((uint8_t  *)pt->value)); break;
        case UINT16_T:   printf("%u\n",  *((uint16_t *)pt->value)); break;
        case UINT32_T:   printf("%u\n",  *((uint32_t *)pt->value)); break;
        case UINT64_T:   printf("%lu\n", *((uint64_t *)pt->value)); break;
        case CHAR:       printf("%c\n",  *((char     *)pt->value)); break;
      }
    }
    if(pt->next) {
      for(uint16_t i = 0; i < pt->qty_children; i++)
        debug_prefix_tree(pt->next[i], depth + 1);
    }
  }
}

/**
 * This function will free a given prefix_tree.
 * @param   pt - The prefix_tree to be freed.
 * @return N/a
 */
void free_prefix_tree(prefix_tree * pt) {
  if(pt) {
    switch(pt->type) {
      case UINT8_T:  free((uint8_t  *)pt->value); break;
      case UINT16_T: free((uint16_t *)pt->value); break;
      case UINT32_T: free((uint32_t *)pt->value); break;
      case UINT64_T: free((uint64_t *)pt->value); break;
      case CHAR:     free((char     *)pt->value); break;
    }
    if(pt->next) {
      for(uint16_t i = 0; i < pt->qty_children; i++)
        free_prefix_tree(pt->next[i]);
      free(pt->next);
    }
    free(pt);
  }
}
