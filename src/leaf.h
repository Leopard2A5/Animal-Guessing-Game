/*
 * leaf.h
 *
 *  Created on: 29.10.2011
 *      Author: leopard2a5
 */

#ifndef LEAF_H_
#define LEAF_H_

#include <stdio.h>
#include "element.h"

/**************************
 * Data members
 **************************/
struct Leaf_data
{
  char* name;
};

/**************************
 * Override function pointers
 **************************/
struct Leaf_override
{
  void (*delete)(void*);
  void (*save)  (void*, FILE*);
};

/**************************
 * Leaf struct
 **************************/
struct Leaf
{
  struct Element_op*    ops;
  struct Element_data*  data;
  struct Leaf_data*     leaf_data;
  struct Leaf_override* ovr;
};

/**************************
 * class methods
 **************************/
void
load_leaf (void*, FILE*, struct Element*);

void
save_leaf(void*, FILE*);

void
delete_leaf(void*);

struct Leaf*
new_leaf(struct Element*, char*);

#endif /* LEAF_H_ */
