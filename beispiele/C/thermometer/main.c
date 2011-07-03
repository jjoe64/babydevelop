/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* ---------------------------------------------------- */
/* Beachten Sie den Schalter EscapeSequenzen unter:     */
/* Bearbeiten->Einstellungen->EscapeSequenzen           */
/* ---------------------------------------------------- */

/* main.c */

/*---------------------*/
/* Projekt: Termometer */
/*---------------------*/

#include <stdio.h>

#include "funktionen.h"

#define blau    5    /* PräcompilerAnweisungen */
#define gruen   3
#define rot     2
#define normal 12

int main ()
{
   int temp;         /* Deklarationen */
   int pos_x, pos_y;
   pos_x=5;
   pos_y=10;

   cls();
   pos(1,1);
   printf("Bildschirmgroesse mind. 87x14 Zeichen\n");
   printf("Wertebereich: -30...50 und 99");

   while(1)          /* Endlosschleife ;-) */
   {
      pos(pos_x,pos_y);      /* Temperatureingabe */
      printf("                         ");
      pos(pos_x,pos_y);
      printf("Temperatur = ");
      scanf("%i",&temp);
          fflush(stdin);
          getchar();

      if(temp==99)   /* ProgrammAbbruch */
      {
         break;
      }
      cls();
      thermometer(temp,5,10);
   }
   pos(1,22);
}
