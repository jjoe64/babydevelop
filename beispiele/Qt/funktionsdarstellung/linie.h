/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* linie.h */

#ifndef LINIE_H
#define LINIE_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

class Linie
{
public:
   Linie(int, int, int, int, int);  /* Konstruktor */
  ~Linie();                         /* Destruktor  */

private:
   int meinX0;
   int meinY0;
   int meinX1;
   int meinY1;
   int meineFarbe;

public:
   int  gibX0();
   int  gibY0();
   int  gibX1();
   int  gibY1();
   void setzeFarbe(int);
   int  gibFarbe();
};

#endif
