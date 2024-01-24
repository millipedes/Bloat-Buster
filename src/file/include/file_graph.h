/**
 * @file   file_graph.h
 * @breif  This file contains the function definitions for file_graph.c.
 * @author Matthew C. Lindeman
 * @date   January 23, 2024
 * @bug    None.
 * @todo   A lot.
 */
#ifndef FILE_GRAPH_H
#define FILE_GRAPH_H

#include <dirent.h>
#include <stdio.h>
#include <string.h>

#include "core/include/prefix_tree.h"
#include "core/include/string_lib.h"
#include "main/include/constants_macros.h"

prefix_tree * includes_from_directory(prefix_tree * head, const char * path);
prefix_tree * includes_from_file(prefix_tree * head, const char * file);

#endif
