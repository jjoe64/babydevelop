/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* vielenamen.cpp */

#include "vielenamen.h"

/* Konstruktor */
VieleNamen::VieleNamen()
{
   laenge = 8;
   breite = 8;
}

/* Destruktor */
VieleNamen::~VieleNamen()
{
}

VieleNamen::VieleNamen(int l)
{
   laenge=l;
   breite=8;
}

VieleNamen::VieleNamen(int l, int b)
{
   laenge=l;
   breite=b;
}

void VieleNamen::zeige()
{
   cout << "Flaeche = " << laenge*breite << endl;
}

void VieleNamen::zeige(int eins)
{
   cout << "Flaeche = " << laenge*breite << endl;
}

void VieleNamen::zeige(int eins, int zwei)
{
   cout << "Flaeche = " << laenge*breite << endl;
}

void VieleNamen::zeige(float zahl)
{
   cout << "Flaeche = " << laenge*breite << endl;
}
