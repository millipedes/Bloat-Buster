#include "include/pointer_arithmetic.h"

void * min_ptr(int count, ...) {
  va_list args;
  va_start(args, count);
  void * min = va_arg(args, void *);
  for(int i = 1; i < count; i++) {
    void * current = va_arg(args, void *);
    if(current != NULL && current < min)
      min = current;
  }
  va_end(args);
  return min;
}
