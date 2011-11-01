/*
 ============================================================================
 Name        : Animal-Guessing-Game.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "element.h"
#include "node.h"
#include "leaf.h"
#include "util.h"

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
{
  printf("\033[2J"); //terminalsequenz zum loeschen des inhalts
}

/* Flushes first \n from Input-Stream */
void eatToNL(FILE * inputStream)
{
  int c;
  while ((c = getc(inputStream)) != EOF)
    if (c == '\n') break;
}

char
read_single_Char(void)
{
  char input[100];
  printf(">");
  scanf("%99s", &input[0]);
  input[0]=toupper(input[0]); // um gross/kleinschreibung zu eliminieren
  eatToNL(stdin);
  return input[0];
}

void
read_animal_name(char* input)
{
  printf("Please enter an animal name:\n");
  printf(">");
  scanf("%99s",  &input[0]);
  eatToNL(stdin);
}

void
read_animal_characteristics(char* input)
{
  printf("Please enter a question to distinguish:\n");
  printf(">");
  getline (&input, &nbytes, stdin);
  input[strlen(input)-1] = '\0'; //ersetzt das abschliessende
                                 //\n durch ein null-byte
}

void
running_game(struct Element* element)
{
  char answer;
  if ((element -> data -> type_id) == 0)
    {
      struct Node* actual_element = (struct Node*) element;
      printf("%s \n", actual_element -> node_data -> question );
      answer = read_single_Char();
      if (answer=='Y') running_game(actual_element->node_data->yes);
      if (answer=='N') running_game(actual_element->node_data->no);
    }
  if ((element -> data -> type_id) == 1)
    {
      struct Leaf* actual_element = (struct Leaf*) element;
      printf("War es ein %s ?\n", actual_element ->leaf_data ->name);
      answer = read_single_Char();
      if (answer=='Y') game_menu(); //
      if (answer=='N')
      {
        read_animal_name(animal); // Tier hinzufuegen prüfen ob element == root
        read_animal_characteristics(question);
        struct Node* tmpNode = insert_new_leaf((struct Leaf*) element, animal, question);
        if (root==element)  root=tmpNode;
      }
    }
}

void
start_game(void)
{
  if (root == NULL)
  {
    read_animal_name(animal);
    struct Node* node = new_leaf(NULL,animal);
    root = (struct Element* ) node;
  }
  running_game(root);
}

void
save_game(void)
{
  printf("Please enter filename:\n");
  printf(">");
  char filename[100];
  scanf("%99s",  &filename[0]);
  eatToNL(stdin);
  save_tree(filename, root);
  game_menu();
}

void
game_menu(void)
{
  char input;
  do
  {
    printf("Animal Guessing Game - Menu\n\n");
    printf("[1] Start a new Game\n");
    printf("[2] Save\n");
    printf("[3] Exit\n");
    input=read_single_Char();
    switch(input)
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
        printf("Wrong Input!\n"); ;
        break;
    }
  } while (input != '3');
}

int
main(int argc, char* argv[])
{
  cls();
  if(argc>1)
    {
     root = load_tree(argv[1]);
    }
  game_menu();
  return EXIT_SUCCESS;
}
