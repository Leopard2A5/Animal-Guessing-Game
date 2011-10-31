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
#include "structures.h"
#include "util.h"

struct Element* root;

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
start_game(void)
{
  printf("Please enter an animal:\n");
  char animal[100];
  scanf("%99s", &animal[0]);
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
  } while (input != 3);
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
