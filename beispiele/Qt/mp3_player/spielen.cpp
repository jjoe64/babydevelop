/* spielen.cpp */

#include "spielen.h"

/* Konstruktor */
Spielen::Spielen (QString lied) : ProgrammFenster ()
{
   QString befehl = "xmms -p '"+lied+"'";
   qWarning("Abgesetzer Befehl = %s", befehl.toLatin1().data());
//   system(befehl.toLatin1().data());
   fp = popen(befehl.toLatin1().data(), "r");
}

/* Destruktor */
Spielen::~Spielen ()
{
   pclose(fp);
}
