/*
 * NODE.h
 *
 *  Created on: 29.10.2011
 *      Author: leopard2a5
 */

#ifndef NODE_H_
#define NODE_H_

#define TYPE_NODE 0
#define TYPE_LEAF 1

#include <stdio.h>
#include <inttypes.h>
#include "element.h"

struct Node_data
{
  struct Element* yes;
  struct Element* no;
  char*           question;
};

struct Node_override
{
  void (*delete)(void*);
};

struct Node
{
  struct Element_op*    ops;
  struct Element_data*  data;
  struct Node_data*     node_data;
  struct Node_override* ovr;
};

void
load_node (void*, FILE*, struct Element*);

struct Node*
new_node(struct Element*, char*);

#endif /* NODE_H_ */
