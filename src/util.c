/*
 * util.c
 *
 *  Created on: 30.10.2011
 *      Author: leopard2a5
 */

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>
#include "element.h"
#include "node.h"
#include "leaf.h"

/**
 * checks whether the given file has the correct header
 */
int
check_header(FILE* file)
{
  uint8_t header[4];
  fread(&header, sizeof(uint8_t), 4, file);

  if (memcmp(header, "AGG0", sizeof(uint8_t) * 4) == 0)
    {
      uint32_t ctrl;
      fread(&ctrl, sizeof(uint32_t), 1, file);
      ctrl = ntohl(ctrl);

      if (ctrl == 0x01020304)
        {
          return 1;
        }
    }

  return 0;
}

struct Element*
build_element_from_type_from_file(FILE* file)
{
  // read the type id
  uint8_t type;
  fread(&type, sizeof(uint8_t), 1, file);

  if (type == 0)
    {
      return (struct Element*) new_node(NULL, NULL);
    }
  else if (type == 1)
    {
      return (struct Element*) new_leaf(NULL, NULL);
    }
  else
    {
      printf("read unknown type %d", type);
      return NULL;
    }
}

struct Element*
load_tree(char* filepath)
{
  struct Element* root = NULL;
  FILE* file = fopen(filepath, "rb");

  if (file != NULL)
    {
      if (check_header(file))
        {
          root = build_element_from_type_from_file(file);

          // load element tree recursively
          root->ops->load(root, file, NULL);
        }
      else
        {
          printf("Header of file %s does not match AGG0", filepath);
        }

      fclose(file);
    }
  else
    {
      printf("Could not open file %s", filepath);
    }

  printf("\n\n");

  return root;
}

void
save_tree(char* filepath, struct Element* root)
{
  FILE* file = fopen(filepath, "wb");
  if (file != NULL)
    {
      // write the header
      fprintf(file, "AGG0");
      uint8_t ctrl[] = {0x01, 0x02, 0x03, 0x04};
      fwrite(ctrl, sizeof(uint8_t), 4, file);

      // save the tree recursively
      root->ops->save(root, file);

      fclose(file);
    }
  else
    {
      printf("Could not open file '%s' for writing", filepath);
    }
}

uint32_t
get_length_of_string(char* text)
{
  uint32_t length = 0;

  for (length = 0; length <= INT32_MAX; length++)
    {
      if (text[length] == '\0')
        {
          break;
        }
    }

  return length;
}

struct Node*
insert_new_leaf(struct Leaf* current, char* name, char* question)
{
  struct Node* parent = (struct Node*)current->data->parent;
  // build new node
  struct Node* node = new_node((struct Element*)parent, question);

  // tell the parent it's new child
  if (parent != NULL)
    {
      if (parent->node_data->yes == (struct Element*)current)
        {
          parent->node_data->yes = (struct Element*)node;
        }
      if (parent->node_data->no == (struct Element*)current)
        {
          parent->node_data->no = (struct Element*)node;
        }
    }

  // construct the new yes branch
  struct Leaf* yes = new_leaf((struct Element*)node, name);
  node->node_data->yes = (struct Element*)yes;

  // construct the new no branch
  struct Leaf* no  = new_leaf((struct Element*)node, current->leaf_data->name);
  node->node_data->no = (struct Element*)no;

  // free the memory for the now obsolete leaf
  current->ops->delete(current);

  return node;
}
