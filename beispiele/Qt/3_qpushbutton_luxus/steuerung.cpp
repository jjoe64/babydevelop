/* steuerung.cpp */

#include "steuerung.h"

/* Konstruktor */
Steuerung::Steuerung () : ProgrammFenster ()
{
   this->setWindowTitle("- QPushButton-Beispiel -");
   this->setGeometry(100,200,300,70);

   tasteBeenden = new QPushButton("Beenden",this);
   tasteBeenden->setGeometry(10,10,80,30);
   tasteBeenden->show();
   connect(tasteBeenden,SIGNAL(clicked()),SLOT(beenden()));
}

/* Destruktor */
Steuerung::~Steuerung ()
{
}

void Steuerung::beenden()
{
   qApp->exit(0);
}
