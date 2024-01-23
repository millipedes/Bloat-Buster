/**
 * @file   string_lib.c
 * @breif  This file contains the functions which are are used to help the user
 * parse strings using this library.
 * @author Matthew C. Lindeman
 * @date   January 22, 2024
 * @bug    None.
 * @todo   A lot.
 */
#define _GNU_SOURCE // :( No X platform
#include "include/string_lib.h"

/**
 * This function is the identity function for void pointer.
 * @param  stream - The stream to return.
 * @return stream - The stream passed which is returned.
 */
void * identity(void * stream) {
  return stream;
}

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

/**
 * This function will return the character immediately after the string
 * "#include ", otherwise NULL.
 * @param stream - The stream to analyze.
 * @return NULL - "#include " is not in the stream.
 *           .\ - The address of the first character after the "#include ".
 */
void * includes(void * stream) {
  void * new_line = strchr((char *)stream, '\n');
  if(!new_line || *(char *)stream == '\0')
    return NULL;
  void * include = memmem(stream, new_line - stream, "#include ",
      sizeof("#include ") - 1);
  return include ? include + sizeof("#include ") - 1 : NULL;
}

/**
* This function will return the character immediately after '\n', otherwise
* NULL.
* @param stream - The stream to analyze.
* @return  NULL - '\n' is not in the stream.
*            .\ - The address of the first character after '\n'.
*/
void * new_line(void * stream) {
  void * new_line = strchr((char *)stream, '\n');
  if(!new_line || *(char *)stream == '\0')
    return NULL;
  return new_line + 1;
}
