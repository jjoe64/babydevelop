/* suchen.cpp */

#include "suchen.h"

//Globale Variablen
extern QString aktuellerPfad;

/* Konstruktor */
Suchen::Suchen (QString begriff) : ProgrammFenster ()
{
   derBegriff = begriff;
   QString heimatVerzeichnis = QDir::homePath();
   QString befehl = "find "+heimatVerzeichnis+" -iname *"+derBegriff+"*.mp3 > "+aktuellerPfad+"/liste.txt";
   system(befehl.toLatin1().data());
   qWarning("Suchen::Abgesetzer Befehl = %s", befehl.toLatin1().data());
} 

/* Destruktor */
Suchen::~Suchen ()
{
}
