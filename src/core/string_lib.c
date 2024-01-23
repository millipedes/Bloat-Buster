#include "include/string_lib.h"

void * words(void * value) {
  if(*(char *)value == '\0')
    return NULL;
  void * space = strchr((char *)value, ' ');
  void * new_line = strchr((char *)value, '\n');
  return min_ptr(2, (space ? ++space : NULL), (new_line ? ++new_line : NULL));
}
