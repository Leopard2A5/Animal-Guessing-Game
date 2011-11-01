/*
 * leaf.c
 *
 *  Created on: 29.10.2011
 *      Author: leopard2a5
 */

#include "leaf.h"
#include "util.h"
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

/**
 * loads a leaf from the given file
 */
void
load_leaf (void* pThis, FILE* file, struct Element* parent)
{
  struct Leaf* this = (struct Leaf*)pThis;
  this->data->parent = parent;

  // get the length of the name to read
  uint32_t length;
  fread(&length, sizeof(uint32_t), 1, file);
  length = ntohl(length);

  // allocate memory and read the name
  this->leaf_data->name = malloc(sizeof(char) * length);
  fread(this->leaf_data->name, sizeof(char), length, file);

//  printf("read leaf '%s'\n", this->leaf_data->name);
}

/**
 * writes this leaf to the file
 * also calls element::save
 */
void
save_leaf(void* pThis, FILE* file)
{
  struct Leaf* this = (struct Leaf*)pThis;
  // write element specific data
  this->ovr->save(this, file);

  // get the length of the name
  uint32_t length = strlen(this->leaf_data->name);
  // convert to little-endian
  uint32_t nlength = htonl(length);

  // write the length
  fwrite(&nlength, sizeof(uint32_t), 1, file);
  // write the name
  fwrite(this->leaf_data->name, sizeof(char), length, file);
}

/**
 * frees the allocated memory for this leaf
 */
void
delete_leaf (void* pThis)
{
  struct Leaf* this = (struct Leaf*)pThis;

  // free leaf specific memory
  free(this->leaf_data->name);

  // free element specific memory
  this->ovr->delete(this);
}

/**
 * initializes a new leaf
 */
struct Leaf*
new_leaf(struct Element* parent, char* name)
{
  struct Leaf* this = malloc(sizeof(struct Leaf));
  // initialize element
  init_element(this, TYPE_LEAF, parent);

  // allocate memory for the leaf
  this->leaf_data   = malloc(sizeof(struct Leaf_data));
  this->ovr         = malloc(sizeof(struct Leaf_override));

  this->ops->load          = &load_leaf;

  // override save
  this->ovr->save          = this->ops->save;
  this->ops->save          = &save_leaf;

  // override delete
  this->ovr->delete        = this->ops->delete;
  this->ops->delete        = &delete_leaf;

  this->leaf_data->name = name;

  return this;
}
