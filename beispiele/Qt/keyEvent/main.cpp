/* main.cpp */

#include <qapplication.h>

#include "beispiel.h"

int main(int argc, char **argv)
{
   QApplication meinProgramm(argc, argv);
   Beispiel beispiel;
   beispiel.show();
   int rueckgabe = meinProgramm.exec();
   return rueckgabe;
}
