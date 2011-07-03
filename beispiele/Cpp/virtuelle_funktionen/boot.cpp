/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

#include "boot.h"

Boot::Boot() : Vehikel()
{
}

Boot::~Boot()
{
}

int Boot::passagiere()
{
   return passagieranzahl;
}

void Boot::nachricht()
{
   cout << "Nachricht vom Boot" << endl;
}


