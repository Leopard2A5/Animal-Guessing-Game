/*
 * structures.c
 *
 *  Created on: 28.10.2011
 *      Author: leopard2a5
 */

#include "structures.h"
#include <stdlib.h>

/******************************
 *          Element           *
 ******************************/

int
save (struct Element* this, FILE* file)
{
  return 0;
}

int
load (struct Element* this, FILE* file)
{
  return 0;
}

struct Element_op
{
  int (*save)(struct Element*, FILE*);
  int (*load)(struct Element*, FILE*);
};

struct Element_data
{
  uint8_t  type_id;
  struct Element* parent;
  char*    text;
};

struct Element
{
  struct Element_op* ops;
  struct Element_data* data;
};

/******************************
 *          Node              *
 ******************************/

struct Node_data
{
  struct Element* yes;
  struct Element* no;
};

struct Node
{
  struct Element_op*   ops;
  struct Element_data* data;
  struct Node_data*    ndata;
};

/******************************
 *          Leaf              *
 ******************************/

struct Leaf_data
{

};

struct Leaf
{
  struct Element_op*   ops;
  struct Element_data* data;
  struct Leaf_data*    ldata;
};

void
init_element (struct Element* this)
{
  this->ops->save = &save;
  this->ops->load = &load;
}

struct Node*
new_node()
{
  struct Node* this = malloc(sizeof(struct Node));
  init_element((struct Element*)this);
  this->data->type_id = TYPE_NODE;

  return this;
}

struct Leaf*
new_leaf()
{
  struct Leaf* this = malloc(sizeof(struct Leaf));
  init_element((struct Element*)this);
  this->data->type_id = TYPE_LEAF;

  return this;
}

