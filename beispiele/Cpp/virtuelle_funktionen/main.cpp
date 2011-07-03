/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* main.cpp */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#include "vehikel.h"
#include "auto.h"
#include "laster.h"
#include "boot.h"

int main()
{
/* ----------------- */
   Vehikel *hochrad;
/* ----------------- */

   hochrad = new Vehikel();
   hochrad->nachricht();
   delete hochrad;

   hochrad = new Auto();
   hochrad->nachricht();
   delete hochrad;

   hochrad = new Laster();
   hochrad->nachricht();
   delete hochrad;

   hochrad = new Boot();
   hochrad->nachricht();
   delete hochrad;
}
