/**
* @file   string_lib.c
* @breif  This file contains the functions which are are used to help the user
* parse strings using this library.
* @author Matthew C. Lindeman
* @date   January 22, 2024
* @bug    None.
* @todo   A lot.
*/
#include "include/string_lib.h"

/**
* This function is used to parse words (i.e. breaks off of '\n's and ' 's). It
* will return the first occurance of a character immediately after a '\n' or a
* ' '.  If there are no '\n's or ' ' in the sequence then it will return NULL.
*
* N.B. This function will not work on Windows (i.e. files which have "\r\n"
* denoting new lines). If someone would like to fix that I will accept a PR.
*
* @param stream - The stream which will be parsed.
* @return   .\ - The character immediately after the first ' 'or '\n'. If there
*                is no '\n' or ' ' remaining in the stream then it will return
*                NULL.
*/
void * words(void * stream) {
  if(*(char *)stream == '\0')
    return NULL;
  void * space = strchr((char *)stream, ' ');
  void * new_line = strchr((char *)stream, '\n');
  return min_ptr(2, (space ? ++space : NULL), (new_line ? ++new_line : NULL));
}
