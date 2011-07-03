/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

#ifndef AUTO_H
#define AUTO_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#include "vehikel.h"

class Auto : public Vehikel
{
public:
    Auto();
   ~Auto();
private:
   int passagieranzahl;
public:
   void nachricht();
};

#endif
