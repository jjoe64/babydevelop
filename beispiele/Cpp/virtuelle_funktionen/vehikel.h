/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

#ifndef VEHIKEL_H
#define VEHIKEL_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

class Vehikel
{
public:
    Vehikel();
   ~Vehikel();
   //virtual ~Vehikel();
private:
   int raeder;
   float gewicht;
public:
   virtual void nachricht();
};

#endif
