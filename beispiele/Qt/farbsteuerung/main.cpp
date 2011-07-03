/* main.cpp */

#include <QApplication>

#include "steuerung.h"

int main(int argc, char **argv)
{
   QApplication meinProgramm(argc, argv);
   Steuerung steuerung;
   steuerung.show();
   int rueckgabe = meinProgramm.exec ();
   return rueckgabe;
}
