#include "include/prefix_tree.h"

int is_valid_pt_type(pt_type type) {
  switch(type) {
    case UINT8_T:
    case UINT16_T:
    case UINT32_T:
    case UINT64_T:
    case CHAR:
    case END_OF_SEQ: return 1;
    default:         return 0;
  }
}

const char * pt_type_to_string(pt_type type) {
  switch(type) {
    case UINT8_T:    return "uint8_t";
    case UINT16_T:   return "uint16_t";
    case UINT32_T:   return "uint32_t";
    case UINT64_T:   return "uint64_t";
    case CHAR:       return "char";
    case END_OF_SEQ: return "end of seq";
    default:         return NULL;
  }
}

uint32_t sizeof_pt_type(pt_type type) {
  switch(type) {
    case UINT8_T:    return sizeof(uint8_t);
    case UINT16_T:   return sizeof(uint16_t);
    case UINT32_T:   return sizeof(uint32_t);
    case UINT64_T:   return sizeof(uint64_t);
    case CHAR:       return sizeof(char);
    case END_OF_SEQ:
    default:         return 0;
  }
}

prefix_tree * init_prefix_tree(pt_type type) {
  prefix_tree * pt = calloc(1, sizeof(struct PREFIX_TREE_T));
  pt->next = NULL;
  pt->prev = NULL;
  pt->value = NULL;
  pt->type = type;
  pt->qty_children = 0;
  return pt;
}

prefix_tree * read_stream_to_prefix_tree(prefix_tree * head, void * stream,
    void * iterator(void *)) {
  void * next_stream = NULL;
  while((next_stream = iterator(stream)) != NULL)
    head = process_stream_sequence(head, stream, next_stream);
  return head;
}

prefix_tree * process_stream_sequence(prefix_tree * head, void * start,
    void * end) {
  prefix_tree * tmp = head;
  while(start > end) {
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
  }
  return head;
}

void * words(void * value) {
  if(*(char *)value == '\0')
    return NULL;
  return min_ptr(2, strchr((char *)value, ' '), strchr((char *)value, '\n'));
}

void * min_ptr(int count, ...) {
    va_list args;
    va_start(args, count);
    void * min = va_arg(args, void *);
    for(int i = 1; i < count; i++) {
        void * current = va_arg(args, void *);
        if (current < min)
            min = current;
    }
    va_end(args);
    return min;
}

void debug_prefix_tree(prefix_tree * pt, int depth) {
  if(pt) {
    PRINT_C_N(SPACE, depth)
    switch(pt->type) {
      case UINT8_T:    printf("%u",  *((uint8_t  *)pt->value)); break;
      case UINT16_T:   printf("%u",  *((uint16_t *)pt->value)); break;
      case UINT32_T:   printf("%u",  *((uint32_t *)pt->value)); break;
      case UINT64_T:   printf("%lu", *((uint64_t *)pt->value)); break;
      case CHAR:       printf("%c",  *((char     *)pt->value)); break;
      case END_OF_SEQ: printf("EOS");                           break;
    }
    if(pt->next) {
      for(uint16_t i = 0; i < pt->qty_children; i++)
        debug_prefix_tree(pt->next[i], depth + 1);
    }
  }
}

void free_prefix_tree(prefix_tree * pt) {
  if(pt) {
    switch(pt->type) {
      case UINT8_T:  free((uint8_t  *)pt->value); break;
      case UINT16_T: free((uint16_t *)pt->value); break;
      case UINT32_T: free((uint32_t *)pt->value); break;
      case UINT64_T: free((uint64_t *)pt->value); break;
      case CHAR:     free((char     *)pt->value); break;
      case END_OF_SEQ:                            break; // Nothing alloced
    }
    if(pt->next) {
      for(uint16_t i = 0; i < pt->qty_children; i++)
        free_prefix_tree(pt->next[i]);
      free(pt->next);
    }
    free(pt);
  }
}
