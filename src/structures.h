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
#include <inttypes.h>

/*
 * Element
 */
struct Element;
struct Element_data;

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

int
load_node (struct Element*, FILE*);

struct Node*
new_node();

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

int
load_leaf (struct Element*, FILE*);

void
delete_leaf(struct Element*);

struct Leaf*
new_leaf();

#endif /* STRUCTURES_H_ */
