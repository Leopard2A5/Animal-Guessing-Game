/*
 * util.h
 *
 *  Created on: 30.10.2011
 *      Author: leopard2a5
 */

#ifndef UTIL_H_
#define UTIL_H_

#include "element.h"
#include "leaf.h"

/**
 * loads a tree of element objects from the given file
 * and returns a pointer to the element or NULL
 */
struct Element*
load_tree(char* filepath);

/**
 * saves the given element and it's children to the given file
 */
void
save_tree(char* filepath, struct Element*);

/**
 * initializes a new element subtype according to
 * the type id read from the next 8 bits of the given file
 */
struct Element*
build_element_from_type_from_file(FILE*);

/**
 * copies as string
 */
char*
copy_string(char*);

/**
 * inserts a new leaf into the tree
 */
struct Node*
insert_new_leaf(struct Leaf*, char*, char*);

#endif /* UTIL_H_ */
