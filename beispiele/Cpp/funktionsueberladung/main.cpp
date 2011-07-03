/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* main.cpp */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#include "vielenamen.h"

int main()
{
   /* ------------------------------------- */
   VieleNamen klein, mittel(10), gross(12,15);
   /* ------------------------------------- */

   int bip=144;
   float pi=3.142;
   float lohn=12.5;
   
   klein.zeige();
   klein.zeige(100);
   klein.zeige(bip,100);
   klein.zeige(lohn);
   
   mittel.zeige();
   gross.zeige(pi);

   return 0;
}
