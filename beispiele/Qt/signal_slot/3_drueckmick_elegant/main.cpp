/* main.cpp */

#include <qapplication.h>

#include "basis.h"

int main(int argc, char **argv)
{
   QApplication meinProgramm(argc, argv);
   Basis basis;
   basis.show();
   int rueckgabe = meinProgramm.exec();
   return rueckgabe;
}