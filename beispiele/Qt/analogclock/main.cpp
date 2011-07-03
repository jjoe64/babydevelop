/* main.cpp */

#include <qapplication.h>

#include "analogclock.h"

int main(int argc, char **argv)
{
   QApplication meinProgramm(argc, argv);
   AnalogClock analogclock;
   analogclock.show();
   int rueckgabe = meinProgramm.exec();
   return rueckgabe;
}
