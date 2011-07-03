/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* ---------------------------------------------------- */
/* Beachten Sie den Schalter EscapeSequenzen unter:     */
/* Bearbeiten->Einstellungen->EscapeSequenzen           */
/* ---------------------------------------------------- */

/* funktionen.c */

/*------------------------------------*/
/* EscapeSequenzen machen es moeglich */
/*------------------------------------*/

#include "funktionen.h"

/* Funktion Bildschirm loeschen */
void cls()
{
   printf("\033[2J");
}

/* Funktion: Cursor setzen */
void pos(int x, int y)
{
   printf("\033[%i;%if",y,x);
}

/* Funktion: Hintergrundfarbe setzen */
void bgcolor(int farbe)
{
   switch(farbe)
   {
      case  2:printf("\033[41m");break; /* rot     */
      case  3:printf("\033[42m");break; /* gruen   */
      case  5:printf("\033[44m");break; /* blau    */
      case 12:printf("\033[00m");break; /* normal  */
      default:printf("Fehler beim bgcolor-Farbcode");
   }
}

/* Funktion: Vordergrundfarbe setzen */
void fgcolor(int farbe)
{
   switch(farbe)
   {
      case  2:printf("\033[31m");break; /* rot     */
      case  3:printf("\033[32m");break; /* gruen   */
      case  5:printf("\033[34m");break; /* blau    */
      case 12:printf("\033[00m");break; /* normal  */
      default:printf("Fehler beim fgcolor-Farbcode");
   }
}
