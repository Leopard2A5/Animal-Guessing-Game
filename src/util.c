/*
 * util.c
 *
 *  Created on: 30.10.2011
 *      Author: leopard2a5
 */

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <arpa/inet.h>
#include "element.h"
#include "node.h"
#include "leaf.h"

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
  FILE* file = fopen(filepath, "rb");
  if (file != NULL)
    {
      if (check_header(file))
        {
          struct Element* root = build_element_from_type_from_file(file);

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

  return NULL;
}
