# :zap: A Brief Introduction

## What Does This Library Do?
This library is used for data analysis, particularly pattern recognition. It is
written to maximize flexability and minimize user investment in making a custom
pattern parser.

## Why Did I Write This Library?
For projects which I am involved in I am required to do various parsing tasks
and would really just like to automate this process:
  - Byte Analysis on Sensor Output
  - Dependency Management for Refactoring

## How Does This Library Do What It Does
Fundementally this Library uses a [prefix tree](https://en.wikipedia.org/wiki/Trie).
However this prefix tree has some enhancements to make it super generic and
general purpose. All children are [doubly linked](https://en.wikipedia.org/wiki/Doubly_linked_list)
and each tree has a type:
```
typedef struct PREFIX_TREE_T {
  struct PREFIX_TREE_T ** next; // link(s|?) forward
  struct PREFIX_TREE_T * prev;  // link back
  void * value;                 // value
  pt_type type;                 // type
  size_t qty_children;          // Weight of edge to child
} prefix_tree;

```
Okay, big deal it has a type. Well from the motivation section an avid reader
would have noticed the byte analysis on sensor output requirement of this
library. Well let's look at what types we have:
```
typedef enum {
  UINT8_T,
  UINT16_T,
  UINT32_T,
  UINT64_T,
  CHAR,
} pt_type;

```
This core functions of thie prefix tree allow for seamless analysis of text and
raw byte of sizes: 8, 16, 32, and 64. So it this adds significant genericity to
this library.

# :microscope: Example (With Motivation)
Let's put the byte analysis behind us for now and say that you are a user who
wants to analyze some raw text and take some stats:
```
prefix_tree * head = init_prefix_tree(CHAR);
```
With our structure set up, what type of problem are we looking to solve? We need
some `char *` which contains the text which we want to analyze and past that all
we need is some way to break it up. Let's simplify things a litle and say that
our analysis sequence is "Hello World\nHilbert Worms Work". Last thing is the
iterator. This library requires the iterator to return where the begining of the
next stream starts if it should continue to be parsed or `NULL` otherwise.  For
words this looks like this:
```
void * words(void * stream) {
  if(*(char *)stream == '\0')
    return NULL;
  void * space = strchr((char *)stream, ' ');
  void * new_line = strchr((char *)stream, '\n');
  return min_ptr(2, (space ? ++space : NULL), (new_line ? ++new_line : NULL));
}
```
And just like that we call:
```
head = read_stream_to_prefix_tree(head, "Hello World\nHilbert Worms Work", words);
```
And we have the string separated out by words. Don't forget to free:
```
free_prefix_tree(head);
```
