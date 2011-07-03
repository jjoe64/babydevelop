/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* basis.cpp */

#include "basis.h"

/* Konstruktor */
Basis::Basis() : ProgrammFenster()
{
   this->setGeometry(195, 200, 140, 72);

   taste = new QPushButton("Ende",this);
   taste->setGeometry(20, 10, 100, 50);
   taste->show();
   connect(taste, SIGNAL(clicked()), SLOT(ende()));

   meinLinkesFenster = new Fenster(0, 0);
   meinLinkesFenster->show();
   connect(meinLinkesFenster, SIGNAL(sichtbarmachen(int)), SLOT(einschalten(int)));

   meinRechtesFenster = new Fenster(0, 1);
   meinRechtesFenster->show();
   connect(meinRechtesFenster, SIGNAL(sichtbarmachen(int)), SLOT(einschalten(int)));
}

/* Destruktor */
Basis::~Basis()
{
}

void Basis::einschalten(int n)
{
   if(n==0)
   {
      meinRechtesFenster->show();
   }
   else
   {
      meinLinkesFenster->show();
   }
}

void Basis::ende()
{
   exit(0);
}
