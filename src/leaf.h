/*
 * LEAF.h
 *
 *  Created on: 29.10.2011
 *      Author: leopard2a5
 */

#ifndef LEAF_H_
#define LEAF_H_

#define TYPE_NODE 0
#define TYPE_LEAF 1

#include <stdio.h>
#include "element.h"

struct Leaf_data
{
  char* name;
};

struct Leaf_override
{
  void (*delete)(void*);
};

struct Leaf
{
  struct Element_op*    ops;
  struct Element_data*  data;
  struct Leaf_data*     leaf_data;
  struct Leaf_override* ovr;
};

void
load_leaf (void*, FILE*, struct Element*);

void
delete_leaf(void*);

struct Leaf*
new_leaf(struct Element*, char*);

#endif /* LEAF_H_ */
