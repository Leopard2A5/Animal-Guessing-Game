/*
 * structures.h
 *
 *  Created on: 27.10.2011
 *      Author: leopard2a5
 */

#ifndef STRUCTURES_H_
#define STRUCTURES_H_

#include <stdint.h>
#include <stdio.h>

/******************************
 *          Element           *
 ******************************/
struct Element;

int save(struct Element* this, FILE* file)
{
  return 0;
};

int load(struct Element* this, FILE* file)
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

/***************************
 *            Node         *
 **************************/
struct Node;

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

/*********************
 *       Leaf        *
 ********************/
struct Leaf;

struct Leaf_data
{

};

struct Leaf
{
  struct Element_op*   ops;
  struct Element_data* data;
  struct Leaf_data*    ldata;
};

#endif /* STRUCTURES_H_ */
