/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* linie.cpp */

#include "linie.h"

/* Konstruktor */
Linie::Linie(int x0, int y0, int x1, int y1, int farbe)
{
   meinX0 = x0;
   meinY0 = y0;
   meinX1 = x1;
   meinY1 = y1;
   meineFarbe = farbe;   //file:///usr/share/qt4/doc/html/qt.html#GlobalColor-enum
}

/* Destruktor */
Linie::~Linie()
{
}

int Linie::gibX0()
{
   return meinX0;
}

int Linie::gibY0()
{
   return meinY0;
}

int Linie::gibX1()
{
   return meinX1;
}

int Linie::gibY1()
{
   return meinY1;
}

void Linie::setzeFarbe(int farbe)
{
   meineFarbe = farbe;
}

int Linie::gibFarbe()
{
   return meineFarbe;
}
