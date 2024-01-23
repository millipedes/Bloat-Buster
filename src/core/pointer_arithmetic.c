/**
* @file   pointer_arithmetic.c
* @breif  This file contains general pointer arithmetic functions for the core
* functionality of this library.
* @author Matthew C. Lindeman
* @date   January 22, 2024
* @bug    None.
* @todo   None Atm.
*/
#include "include/pointer_arithmetic.h"

/**
* This function takes in the number of pointers which is being passed to it and
* a variant number of pointers then returns the pointer with the lowest value.
* @param count - The number of arguments being passed to the function (self not
*                included).
* @return  min - The smallest pointer among pointers passed to it.
*/
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
