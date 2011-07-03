/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* basis.cpp */

#include "basis.h"

#include <qmessagebox.h>

/* Konstruktor */
Basis::Basis() : ProgrammFenster()
{
   this->setGeometry(195, 200, 140, 72);

   taste = new QPushButton("Ende", this);
   taste->setGeometry(20, 10, 100, 50);
   taste->show();
   connect(taste, SIGNAL(clicked()), SLOT(ende()));

   meinFenster = new Fenster(0);
   meinFenster->show();
   connect(meinFenster, SIGNAL(sichtbarmachen()), SLOT(meldung()));
}

/* Destruktor */
Basis::~Basis()
{
}

void Basis::meldung()
{
   QMessageBox::information(this, "- Eine Meldung -", "Ich habe die Maus gesehen :-)");
}

void Basis::ende()
{
   exit(0);
}
