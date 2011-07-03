/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* main.cpp */

/*-----------------------------------------------------------------------------*/
/* Bild anzeigen mit eigener Klasse                                            */
/* mousePressEvent() auf Bild in der Bild-Klasse weiterleiten nach Basisklasse */
/* mouseMoveEvent()  im Bild in der Bild-Klasse weiterleiten nach Basisklasse  */
/*                   und damit das Bild verschieben                            */
/* mouseMoveEvent()  in der Basisklasse bestimmt Startposition von Bild        */ /*-----------------------------------------------------------------------------*/

#include <qapplication.h>

#include "steuerung.h"

int main (int argc, char **argv)
{
   QApplication hauptfenster(argc, argv);
   Steuerung steuerung;
   steuerung.show();
   int rueckgabe = hauptfenster.exec();
   return rueckgabe;
}
