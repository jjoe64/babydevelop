/* steuerung.cpp */

#include "steuerung.h"

/* Konstruktor */
Steuerung::Steuerung() : ProgrammFenster()
{
   lcd = new QLCDNumber(this);
   lcd->setGeometry(20, 20, 170, 70);
   lcd->show();

   takt = new QTimer(this);
   takt->start(777);
   connect(takt, SIGNAL( timeout() ), SLOT( weiter() ) );

   n = 0;
   lcd->display(n);
}

/* Destruktor */
Steuerung::~Steuerung()
{
}

void Steuerung::weiter()
{
   n = n + 1;
   lcd->display(n);
}
