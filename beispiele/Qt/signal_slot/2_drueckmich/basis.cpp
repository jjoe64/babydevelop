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

   r = new Rechts(0);
   r->show();
   connect(r, SIGNAL(sichtbarmachen(int)), SLOT(einschalten(int)));

   l = new Links(0);
   l->show();
   connect(l, SIGNAL(sichtbarmachen(int)), SLOT(einschalten(int)));
}

/* Destruktor */
Basis::~Basis()
{
}

void Basis::einschalten(int n)
{
   if(n==0)
   {
      r->show();
   }
   else
   {
      l->show();
   }
}

void Basis::ende()
{
   exit(0);
}
