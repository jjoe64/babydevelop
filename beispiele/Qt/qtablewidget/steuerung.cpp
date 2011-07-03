/* steuerung.cpp */

#include "steuerung.h"

/* Konstruktor */
Steuerung::Steuerung() : ProgrammFenster()
{
   this->setGeometry(10, 10, 300, 300);

   t=new Tabelle(10, 10, this);
   t->move(20, 20);
}

/* Destruktor */
Steuerung::~Steuerung()
{
}
