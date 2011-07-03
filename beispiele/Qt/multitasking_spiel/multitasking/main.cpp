/* main.cpp */

#include <qapplication.h>

#include "steuerung.h"

int main(int argc, char **argv)
{
   QApplication hauptfenster(argc, argv);
   Steuerung steuerung;
   steuerung.show();
   int rueckgabe = hauptfenster.exec ();
   return rueckgabe;
}
