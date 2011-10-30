/*
 * structures.h
 *
 *  Created on: 29.10.2011
 *      Author: leopard2a5
 */

#ifndef STRUCTURES_H_
#define STRUCTURES_H_

#define TYPE_NODE 0
#define TYPE_LEAF 1

#include <stdio.h>

/*
 * Element
 */
struct Element;
struct Element_op;
struct Element_data;

int
save (struct Element*, FILE*);

void
delete (struct Element*);

void
init_element (struct Element*);

/*
 * Node
 */
struct Node;
struct Node_data;

int
load_node (struct Element*, FILE*);

struct Node*
new_node();

/*
 * Leaf
 */
struct Leaf;
struct Leaf_data;

int
load_leaf (struct Element*, FILE*);

struct Leaf*
new_leaf();

#endif /* STRUCTURES_H_ */
