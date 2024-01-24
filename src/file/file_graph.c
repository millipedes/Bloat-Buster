/**
 * @file   file_graph.c
 * @breif  This file contains the functions which are are used to help the user
 * with parsing files using the prefix_tree data structure.
 * @author Matthew C. Lindeman
 * @date   January 23, 2024
 * @bug    None.
 * @todo   A lot.
 */
#include "include/file_graph.h"

/**
 * This file will search all files at path includes then it will recursively
 * search all directories in that direcorty (minus anything prefaced with '.'.
 * @param  head - The initiailized prefix_tree which will contain all of the
 *                includes in the directory and its subdirectories.
 * @param  path - That path to search.
 * @return head - The newly formed head prefix_tree with all of the include
 *                paths.
 */
prefix_tree * includes_from_directory(prefix_tree * head, const char * path) {
  DIR * dir = opendir(path);

  if(!dir) {
    fprintf(stderr, "[INCLUDES_FROM_DIRECTORY]: Unable to open directory `%s`, "
        "check permissions?\nExiting\n", path);
    exit(1);
  }

  struct dirent * current_entry = NULL;
  while((current_entry = readdir(dir)) != NULL) {
    if(current_entry->d_name[0] != '.') {
      char buf[MAX_PATH_LEN] = {0};
      snprintf(buf, sizeof(buf), "%s/%s", path, current_entry->d_name);
      if(current_entry->d_type == DT_REG) {
        head = includes_from_file(head, buf);
      } else if(current_entry->d_type == DT_DIR) {
        head = includes_from_directory(head, buf);
      }
    }
  }

  closedir(dir);
  return head;
}

/**
 * This function will search a file with a given name for any include statements
 * and will return the head with the include statements properly incerted.
 * @param  head - The head of the prefix_tree.
 * @param  file - The name of the file which will be searched
 * @return head - The head of the prefix_tree with all of the include paths from
 *                the file.
 */
prefix_tree * includes_from_file(prefix_tree * head, const char * file) {
  FILE * fp = fopen(file, "r");
  if(!fp) {
    fprintf(stderr, "[INCLUDES_FROM_FILE]: Unable to open file `%s`, "
        "check permissions?\nExiting\n", file);
    exit(1);
  }

  char buf[MAX_PATH_LEN] = {0};
  while(fgets(buf, MAX_PATH_LEN, fp))
    head = read_stream_to_prefix_tree(head, buf, includes, new_line);
  fclose(fp);
  return head;
}
