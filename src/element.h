/*
 * element.h
 *
 *  Created on: 29.10.2011
 *      Author: leopard2a5
 */

#ifndef ELEMENT_H_
#define ELEMENT_H_

/**************************
 * constant Type IDs
 **************************/
#define TYPE_NODE 0
#define TYPE_LEAF 1

/**************************
 * includes
 **************************/
#include <stdio.h>
#include <inttypes.h>

/**************************
 * Structs
 **************************/
struct Element;
struct Element_data;

/**************************
 * "methods"
 **************************/
struct Element_op
{
  /**
   * saves the element-specific data to the file
   */
  void (*save)  (void*, FILE*);

  /**
   * abstract function
   * load the object data from the given file
   */
  void (*load)  (void*, FILE*, struct Element*);

  /**
   * free allocated memory
   */
  void (*delete)(void*);
};

/**************************
 * Data members
 **************************/
struct Element_data
{
  uint8_t  type_id;
  struct Element* parent;
};

/**************************
 * The element "class"
 **************************/
struct Element
{
  struct Element_op* ops;
  struct Element_data* data;
};

/**************************
 * "class methods"
 **************************/
void
init_element (void* this, uint8_t type, struct Element* parent);

#endif /* ELEMENT_H_ */
