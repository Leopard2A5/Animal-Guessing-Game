/*
 * node.h
 *
 *  Created on: 29.10.2011
 *      Author: leopard2a5
 */

#ifndef NODE_H_
#define NODE_H_

#include <stdio.h>
#include <inttypes.h>
#include "element.h"

/**************************
 * data members
 **************************/
struct Node_data
{
  struct Element* yes;
  struct Element* no;
  char*           question;
};

/**************************
 * override methods
 **************************/
struct Node_override
{
  void (*delete)(void*);
  void (*save)  (void*, FILE*);
};

/**************************
 * Node struct
 **************************/
struct Node
{
  struct Element_op*    ops;
  struct Element_data*  data;
  struct Node_data*     node_data;
  struct Node_override* ovr;
};

void
load_node (void*, FILE*, struct Element*);

void
save_node(void*, FILE*);

struct Node*
new_node(struct Element*, char*);

#endif /* NODE_H_ */
