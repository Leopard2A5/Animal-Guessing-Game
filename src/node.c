/*
 * node.c
 *
 *  Created on: 29.10.2011
 *      Author: leopard2a5
 */

#include "node.h"
#include <stdlib.h>
#include "util.h"
#include <arpa/inet.h>

/**
 * loads a node from the file
 */
void
load_node (void* pThis, FILE* file, struct Element* parent)
{
  struct Node* this = (struct Node*)pThis;
  this->data->parent = parent;

  // get the length and convert to host byte order
  uint32_t length;
  fread(&length, sizeof(uint32_t), 1, file);
  length = ntohl(length);

  // allocate memory for the question and read it
  this->node_data->question = malloc(sizeof(char) * length);
  fread(this->node_data->question, sizeof(char), length, file);

  // load child elements recursively

  // read yes branch
  this->node_data->yes = build_element_from_type_from_file(file);
  this->node_data->yes->ops->load(this->node_data->yes, file, (struct Element*)this);

  // read no branch
  this->node_data->no = build_element_from_type_from_file(file);
  this->node_data->no->ops->load(this->node_data->no, file, (struct Element*)this);

//  printf("read node '%s'\n", this->node_data->question);
}

/**
 * writes this node to the file
 */
void
save_node(void* pThis, FILE* file)
{
  struct Node* this = (struct Node*)pThis;
  // write element-specific data
  this->ovr->save(this, file);

  // get the length and convert to little-endian
  uint32_t length = get_length_of_string(this->node_data->question);
  uint32_t nlength = htonl(length);
  // write the length
  fwrite(&nlength, sizeof(uint32_t), 1, file);
  // write the question
  fwrite(this->node_data->question, sizeof(char), length, file);

  // write child elements recursively
  this->node_data->yes->ops->save(this->node_data->yes, file);
  this->node_data->no->ops->save(this->node_data->no, file);
}

/**
 * free allocated memory
 */
void
delete_node(void* pThis)
{
  struct Node* this = (struct Node*) pThis;

  // free child memory recursively
  this->node_data->no->ops->delete(this->node_data->no);
  this->node_data->yes->ops->delete(this->node_data->yes);

  // free node specific memory
  free(this->node_data->question);
  free(this->ovr);

  // call super function
  this->ovr->delete(this);
}

/**
 * init a new Node
 */
struct Node*
new_node(struct Element* parent, char* question)
{
  struct Node* this = malloc(sizeof(struct Node));
  // init element data
  init_element(this, TYPE_NODE, parent);

  // allocate node specific memory
  this->node_data   = malloc(sizeof(struct Node_data));
  this->ovr         = malloc(sizeof(struct Node_override));

  this->ops->load          = &load_node;

  // override save
  this->ovr->save          = this->ops->save;
  this->ops->save          = &save_node;

  // override delete
  this->ovr->delete        = this->ops->delete;
  this->ops->delete        = &delete_node;

  this->node_data->question = question;
  this->node_data->yes      = NULL;
  this->node_data->no       = NULL;

  return this;
}
