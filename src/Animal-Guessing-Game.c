/*
 ============================================================================
 Name        : Animal-Guessing-Game.c
 Author      : R.Perschon; C.Dresske
 Version     :
 Description : Main program with UI
 ============================================================================
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "element.h"
#include "node.h"
#include "leaf.h"
#include "util.h"
#include <string.h>

struct Element* root;
char animal[100];
char question[100];
int nbytes = 100;

void
start_game(void);
void
game_menu(void);

void
cls(void)
{ /*Terminalsequence to clear screen*/
  printf("\033[2J");
}

/* flushes first \n from Input-Stream */
void
eatToNL(FILE * inputStream)
{
  int c;
  while ((c = getc(inputStream)) != EOF)
    if (c == '\n')
      break;
}

char
read_single_Char(void)
{
  char input[100];
  do
    {
      printf("\n>");
      scanf("%99s", &input[0]);
      input[0] = toupper(input[0]); /*eliminates lower/uppercase problems*/
      eatToNL(stdin);
    }
  while (!((input[0] == 'N') | (input[0] == 'Y') | (input[0] == '1')
      | (input[0] == '2') | (input[0] == '3')));
  return input[0];
}

void
read_animal_name(char* input)
{
  printf("Please enter an animal name:\n");
  printf(">");
  scanf("%99s", &input[0]);
  eatToNL(stdin);
}

void
read_animal_characteristics(char* input)
{
  printf("Please enter a question to distinguish:\n");
  printf(">");
  getline(&input, &nbytes, stdin);
  input[strlen(input) - 1] = '\0'; /*erases useless \n from char array*/
}

void
running_game(struct Element* element)
{
  char answer;
  if ((element -> data -> type_id) == 0) /*if node*/
    {
      struct Node* actual_element = (struct Node*) element;
      printf("%s [Y/N]", actual_element -> node_data -> question);
      answer = read_single_Char();
      if (answer == 'Y')
        running_game(actual_element->node_data->yes);
      if (answer == 'N')
        running_game(actual_element->node_data->no);
    }
  if ((element -> data -> type_id) == 1) /*if leaf*/
    {
      struct Leaf* actual_element = (struct Leaf*) element;
      printf("Was it a %s ?[Y/N]", actual_element ->leaf_data ->name);
      answer = read_single_Char();
      if (answer == 'Y')
        {
          printf("%s was found!\nContinue [Y]",
              actual_element ->leaf_data ->name);
          read_single_Char();
          game_menu(); //
        }
      if (answer == 'N')
        { /*insert a new animal and rebuild the tree*/
          read_animal_name(animal);
          read_animal_characteristics(question);
          struct Node* tmpNode = insert_new_leaf((struct Leaf*) element,
              copy_string(animal), copy_string(question));
          if (root == element) /*change root if only one leaf was present*/
            root = (struct Element*) tmpNode;
        }
    }
}

void
start_game(void)
{
  if (root == NULL)
    { /*in case tree was empty*/
      read_animal_name(animal);
      struct Leaf* leaf = new_leaf(NULL, copy_string(animal));
      root = (struct Element*) leaf;
    }
  running_game(root);
}

void
save_game(void)
{
  printf("Please enter filename:\n");
  printf(">");
  char filename[100];
  scanf("%99s", &filename[0]);
  eatToNL(stdin);
  save_tree(filename, root);
  game_menu();
}

void
game_menu(void)
{
  cls();
  char input;
  do
    {
      printf("Animal Guessing Game - Menu\n\n");
      printf("[1] Start a new Game\n");
      printf("[2] Save\n");
      printf("[3] Exit");
      input = read_single_Char();
      switch (input)
        {
      case '1':
        start_game();
        break;
      case '2':
        save_game();
        break;
      case '3':
        printf("Quitting program!\n");
        exit(0);
        break;
      default:
        printf("Wrong Input!\n");
        ;
        break;
        }
    }
  while (input != '3');
}

int
main(int argc, char* argv[])
{
  cls();
  if (argc > 1)
    {
      root = load_tree(argv[1]);
    }
  game_menu();
  return EXIT_SUCCESS;
}
