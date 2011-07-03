/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* main.cpp */

/*-----------------------------------------------------------------------------*/
/* Bild anzeigen mit eigener Klasse                                            */
/* mousePressEvent() auf Bild in der Bild-Klasse weiterleiten nach Basisklasse */
/* mouseMoveEvent()  von Bild in der Bild-Klasse weiterleiten nach Basisklasse */
/*                   und damit Bild verschieben                                */
/* mouseMoveEvent()  in der Basisklasse und damit Bild verschieben             */ /*-----------------------------------------------------------------------------*/

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
