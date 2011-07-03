/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* punkt.h */

#ifndef PUNKT_H
#define PUNKT_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

class Punkt
{
public:
   Punkt(int, int, int);  /* Konstruktor */
  ~Punkt();               /* Destruktor  */

private:
   int meinX;
   int meinY;
   int meineFarbe;

public:
   int gibX();
   int gibY();
   int gibFarbe();
};

#endif
