/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* main.c */

#include <stdio.h>

#include "nix.h"
#include "nur_hin.h"
#include "nur_zurueck.h"
#include "hin_und_zurueck.h"

int main()
{
   nix();
   nur_hin(99);
   printf("Rueckgabe von nur_zurueck = %i\n",nur_zurueck());
   printf("Rueckgabe von hin_und_zurueck(3,4) = %i\n",hin_und_zurueck(3,4));
   return 0;
}
