/*
 * structures.c
 *
 *  Created on: 29.10.2011
 *      Author: leopard2a5
 */

#include "structures.h"
#include <inttypes.h>
#include <stdlib.h>

/*
 * Element
 */
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
  int  (*save)  (struct Element*, FILE*);
  int  (*load)  (struct Element*, FILE*);
  void (*delete)(struct Element*);
};

struct Element_data
{
  uint8_t  type_id;
  struct Element* parent;
};

struct Element
{
  struct Element_op* ops;
  struct Element_data* data;
};

void
init_element (struct Element* this)
{
  this->ops->save    = &save;
  this->ops->load    = &load;
  this->ops->delete  = NULL;

  this->data->parent = NULL;
}

/*
 * Node
 */
struct Node_data
{
  struct Element* yes;
  struct Element* no;
  char*           question;
};

struct Node
{
  struct Element*      super;
  struct Node_data*    data;
};

void
delete_node (struct Element* this)
{
  if (this->data->type_id != TYPE_NODE)
    {
      printf("delete_node called on non-node element!!!");
    }
  else
    {
      struct Node* node = (struct Node*) this;

      node->data->no->ops->delete (node->data->no);
      node->data->yes->ops->delete(node->data->yes);
      free(node->data->question);
    }

  free(this);
}

struct Node*
new_node()
{
  struct Node* this = malloc(sizeof(struct Node));

  init_element(this->super);
  this->super->data->type_id = TYPE_NODE;

  this->super->ops->delete = &delete_node;

  this->data->question = NULL;
  this->data->yes      = NULL;
  this->data->no       = NULL;

  return this;
}

/*
 * Leaf
 */
struct Leaf_data
{
  char* name;
};

struct Leaf
{
  struct Element*   super;
  struct Leaf_data* data;
};

void
delete_leaf (struct Element* this)
{
  if (this->data->type_id != TYPE_LEAF)
    {
      printf("delete_leaf called on non-leaf element!!!");
    }
  else
    {
      struct Leaf* leaf = (struct Leaf*) this;

      free(leaf->data->name);
    }

  free(this);
}

struct Leaf*
new_leaf()
{
  struct Leaf* this = malloc(sizeof(struct Leaf));

  init_element(this->super);
  this->super->data->type_id = TYPE_LEAF;

  this->super->ops->delete = &delete_leaf;

  this->data->name = NULL;

  return this;
}
