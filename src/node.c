/*
 * structures.c
 *
 *  Created on: 29.10.2011
 *      Author: leopard2a5
 */

#include "node.h"
#include <stdlib.h>
#include "util.h"
#include <arpa/inet.h>

void
load_node (void* pThis, FILE* file, struct Element* parent)
{
  struct Node* this = (struct Node*)pThis;
  this->data->parent = parent;

  uint32_t length;
  fread(&length, sizeof(uint32_t), 1, file);
  length = ntohl(length);

  this->node_data->question = malloc(sizeof(char) * length);
  fread(this->node_data->question, sizeof(char), length, file);

  // read yes branch
  this->node_data->yes = build_element_from_type_from_file(file);
  this->node_data->yes->ops->load(this->node_data->yes, file, (struct Element*)this);

  // read no branch
  this->node_data->no = build_element_from_type_from_file(file);
  this->node_data->no->ops->load(this->node_data->no, file, (struct Element*)this);

//  printf("read node '%s'\n", this->node_data->question);
}

void
save_node(void* pThis, FILE* file)
{
  struct Node* this = (struct Node*)pThis;
  this->ovr->save(this, file);

  uint32_t length = get_length_of_string(this->node_data->question);
  uint32_t nlength = htonl(length);
  fwrite(&nlength, sizeof(uint32_t), 1, file);
  fwrite(this->node_data->question, sizeof(char), length, file);

  this->node_data->yes->ops->save(this->node_data->yes, file);
  this->node_data->no->ops->save(this->node_data->no, file);
}

void
delete_node(void* pThis)
{
  struct Node* this = (struct Node*) pThis;

  this->node_data->no->ops->delete(this->node_data->no);
  this->node_data->yes->ops->delete(this->node_data->yes);
  free(this->node_data->question);

  this->ovr->delete(this);
}

struct Node*
new_node(struct Element* parent, char* question)
{
  struct Node* this = malloc(sizeof(struct Node));
  init_element(this, TYPE_NODE, parent);

  this->node_data   = malloc(sizeof(struct Node_data));
  this->ovr         = malloc(sizeof(struct Node_override));

  this->ops->load          = &load_node;
  this->ovr->save          = this->ops->save;
  this->ops->save          = &save_node;
  this->ovr->delete        = this->ops->delete;
  this->ops->delete        = &delete_node;

  this->node_data->question = question;
  this->node_data->yes      = NULL;
  this->node_data->no       = NULL;

  return this;
}
