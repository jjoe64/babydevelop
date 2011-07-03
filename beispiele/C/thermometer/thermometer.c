/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* ---------------------------------------------------- */
/* Beachten Sie den Schalter EscapeSequenzen unter:     */
/* Bearbeiten->Einstellungen->EscapeSequenzen           */
/* ---------------------------------------------------- */

/* thermometer.c */

#include "thermometer.h"

/* Thermometer und Skala anzeigen */
void thermometer (int temp, int pos_x, int pos_y)
{
   pos(pos_x,pos_y+2);
   printf("-30       -20       -10        0         10        20        30        40        50");
   pos(pos_x,pos_y+3);
   printf("-|----+----|----+----|----+----|----+----|----+----|----+----|----+----|----+----|-");
   int zaehler;
   for(zaehler=-30;zaehler<=temp;zaehler=zaehler+1)       /* Farbsteuerung */
   {
      pos(pos_x+zaehler+30+1,pos_y+4);   //Cursor setzen
      if(zaehler<0)         /* unter Null Grad -> blau */
      {
         bgcolor(blau);
         fgcolor(blau);
      }
      else if(zaehler<30)   /* zwischen Null und 30 Grad -> grün */
      {
         bgcolor(gruen);
         fgcolor(gruen);
      }
      else                  /* ab 30 Grad -> rot */
      {
         bgcolor(rot);
         fgcolor(rot);
      }
      printf(" ");   //Balkenstueck zeichnen
   }
   bgcolor(normal);         /* Normaldarstellung */
   fgcolor(normal);
}
