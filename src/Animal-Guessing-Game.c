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
void
start_game(void);

void
cls(void)
{
  printf("\033[2J"); //terminalsequenz zum loeschen des inhalts
}

char
read_single_Char(void)
{
  char input[100];
  scanf("%99s", &input[0]);
  input[0]=toupper(input[0]); // um gross/kleinschreibung zu eliminieren
  return input[0];
}

void
read_animal_name(char* input)
{
  printf("Please enter the animal name:");
  scanf("%99s",  &input[0]);
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
      if (answer=='Y') start_game(); //
      if (answer=='N') ; // Tier hinzufuegen prüfen ob element == root
    }
}

void
start_game(void)
{
  read_animal_name(animal);
  printf("%s",animal);
  if (root == NULL)
  {
    //leeres Leaf mit dem vom benutzer eingegebenen Namen anlegen
    //struct Leaf* element = new_leaf(root, animal);
  } else
  {
    printf("Daten vorhanden\n");
  }
  running_game(root);
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
    printf("[3] Abort\n");
    printf(">");
    input=read_single_Char();
    switch(input)
    {
      case '1':
        start_game();
        break;
      case '2':
        printf("Save\n");
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
