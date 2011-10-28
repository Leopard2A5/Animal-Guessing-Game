/*
 * structures.h
 *
 *  Created on: 27.10.2011
 *      Author: leopard2a5
 */

#ifndef STRUCTURES_H_
#define STRUCTURES_H_

#define TYPE_NODE 0
#define TYPE_LEAF 1

#include <stdint.h>
#include <stdio.h>

/******************************
 *          Element           *
 ******************************/
struct Element;
struct Element_op;
struct Element_data;

void
init_element (struct Element*);

struct Node*
new_node();

struct Leaf*
new_leaf();

int
save (struct Element*, FILE*);

int
load (struct Element*, FILE*);

/***************************
 *            Node         *
 **************************/
struct Node;
struct Node_data;

/*********************
 *       Leaf        *
 ********************/
struct Leaf;
struct Leaf_data;

#endif /* STRUCTURES_H_ */
