/*
 * structures.c
 *
 *  Created on: 29.10.2011
 *      Author: leopard2a5
 */

#include "leaf.h"
#include <stdlib.h>
#include <arpa/inet.h>

void
load_leaf (void* pThis, FILE* file, struct Element* parent)
{
  struct Leaf* this = (struct Leaf*)pThis;
  this->data->parent = parent;

  uint32_t length;
  fread(&length, sizeof(uint32_t), 1, file);
  length = ntohl(length);

  this->leaf_data->name = malloc(sizeof(char) * length);
  fread(this->leaf_data->name, sizeof(char), length, file);

//  printf("read leaf '%s'\n", this->leaf_data->name);
}

void
save_leaf(void* pThis, FILE* file)
{
  struct Leaf* this = (struct Leaf*)pThis;
  this->ovr->save(this, file);

  uint32_t length = get_length_of_string(this->leaf_data->name);
  uint32_t nlength = htonl(length);
  fwrite(&nlength, sizeof(uint32_t), 1, file);
  fwrite(this->leaf_data->name, sizeof(char), length, file);
}

void
delete_leaf (void* pThis)
{
  struct Leaf* this = (struct Leaf*)pThis;

  free(this->leaf_data->name);

  this->ovr->delete(this);
}

struct Leaf*
new_leaf(struct Element* parent, char* name)
{
  struct Leaf* this = malloc(sizeof(struct Leaf));
  this->ops         = malloc(sizeof(struct Element_op*));
  this->data        = malloc(sizeof(struct Element_data*));
  this->leaf_data   = malloc(sizeof(struct Leaf_data));
  this->ovr         = malloc(sizeof(struct Leaf_override));

  init_element(this, TYPE_LEAF, parent);

  this->ops->load          = &load_leaf;
  this->ovr->save          = this->ops->save;
  this->ops->save          = &save_leaf;
  this->ovr->delete        = this->ops->delete;
  this->ops->delete        = &delete_leaf;

  this->leaf_data->name = name;

  return this;
}
