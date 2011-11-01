/*
 * element.c
 *
 *  Created on: 29.10.2011
 *      Author: leopard2a5
 */

#include "element.h"
#include <inttypes.h>
#include <stdlib.h>

/**
 * writes the type id to the file
 */
void
save (void* pThis, FILE* file)
{
  struct Element* this = (struct Element*)pThis;

  // write the type id
  fwrite(&(this->data->type_id), sizeof(uint8_t), 1, file);
}

/**
 * frees for the element specific data allocated memory
 */
void
delete(void* pThis)
{
  struct Element* this = (struct Element*) pThis;
  free(this->ops);
  free(this->data);
  free(this);
}

/**
 * allocates memory and initializes element-specific data
 */
void
init_element (void* pThis, uint8_t type, struct Element* parent)
{
  struct Element* this = (struct Element*)pThis;
  this->ops  = malloc(sizeof(struct Element_op));
  this->data = malloc(sizeof(struct Element_data));

  this->ops->save    = &save;
  this->ops->load    = NULL;
  this->ops->delete  = &delete;

  this->data->type_id = type;
  this->data->parent  = parent;
}
