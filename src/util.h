/*
 * util.h
 *
 *  Created on: 30.10.2011
 *      Author: leopard2a5
 */

#ifndef UTIL_H_
#define UTIL_H_

#include "element.h"

struct Element*
load_tree(char* filepath);

void
save_tree(char* filepath, struct Element*);

struct Element*
build_element_from_type_from_file(FILE*);

uint32_t
get_length_of_string(char*);

#endif /* UTIL_H_ */
