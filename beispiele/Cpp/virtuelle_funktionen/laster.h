/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

#ifndef LASTER_H
#define LASTER_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#include "vehikel.h"

class Laster : public Vehikel
{
public:
    Laster();
   ~Laster();
private:
   int passagieranzahl;
   float ladung;
public:
   int passagiere();
};

#endif
