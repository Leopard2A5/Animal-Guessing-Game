/*
 * util.h
 *
 *  Created on: 30.10.2011
 *      Author: leopard2a5
 */

#ifndef UTIL_H_
#define UTIL_H_

#include "element.h"

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
 * utility function to compute the length of the given char*
 */
uint32_t
get_length_of_string(char*);

#endif /* UTIL_H_ */
