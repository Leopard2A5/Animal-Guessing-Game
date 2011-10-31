/*
 * structures.c
 *
 *  Created on: 29.10.2011
 *      Author: leopard2a5
 */

#include "element.h"
#include <inttypes.h>
#include <stdlib.h>

/*
 * Element
 */
void
save (void* pThis, FILE* file)
{

}

void
delete(void* pThis)
{
  struct Element* this = (struct Element*) pThis;
  free(this->ops);
  free(this->data);
  free(this);
}

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
  this->data->parent = parent;
}
