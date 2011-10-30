/*
 ============================================================================
 Name        : Animal-Guessing-Game.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

int
main(int argc, char* argv[])
{
  puts("Animal Guessing Game"); /* prints Animal Guessing Game */
  FILE *datei;
  printf("Anzahl Argumente %d.\n",argc);
  if (argc > 1)         //es wurde ein argument uebergeben
  {
    datei = fopen (argv[1], "r+");
    if (datei == NULL) //falls dieser dateinamen nicht existiert
      {
        printf("Fehler beim Oeffnen der Datei.\n");
        char answer='0';
        while (!((answer == 'y') | (answer == 'n')))
        {
          printf("Neue Datei anlegen [y/n]:");
          answer = getchar(); /*nicht die richtige art einzulesen
                              schleife wird mehrfach durchlaufen s
                              obald mehrere zeichen eingegeben*/
          if (answer == 'y')
          {
            //dateinamen fragen und argument als vorschlag nutzen
            printf("Bitte Dateinamen angeben [%s]:\n",argv[1]);
            //neuen namen einlesen und dateistream oeffnen
          }
        }
      }
    else
    {
      //versuche dateiinhalt lesen und baum bauen
    }
  }

  //spiel spielen
  //speicheroption integrieren

  //Dateistream schliessen
  if (datei != NULL)
  fclose (datei);
  printf("Programmende.\n");
  return EXIT_SUCCESS;
}
