/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

#ifndef BOOT_H
#define BOOT_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#include "vehikel.h"

class Boot : public Vehikel
{
public:
    Boot();
   ~Boot();
private:
   int passagieranzahl;
public:
   int passagiere();
   void nachricht();
};

#endif
