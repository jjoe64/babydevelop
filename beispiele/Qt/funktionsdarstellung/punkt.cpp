/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* punkt.cpp */

#include "punkt.h"

/* Konstruktor */
Punkt::Punkt(int x, int y, int farbe)
{
   meinX = x;
   meinY = y;
   meineFarbe = farbe;   //file:///usr/share/qt4/doc/html/qt.html#GlobalColor-enum
}

/* Destruktor */
Punkt::~Punkt()
{
}

int Punkt::gibX()
{
   return meinX;
}

int Punkt::gibY()
{
   return meinY;
}

int Punkt::gibFarbe()
{
   return meineFarbe;
}
