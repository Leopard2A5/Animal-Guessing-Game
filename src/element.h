/*
 * ELEMENT.h
 *
 *  Created on: 29.10.2011
 *      Author: leopard2a5
 */

#ifndef ELEMENT_H_
#define ELEMENT_H_

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
  void (*save)  (void*, FILE*);
  void (*load)  (void*, FILE*);
  void (*delete)(void*);
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
init_element (void* this);

#endif /* ELEMENT_H_ */
