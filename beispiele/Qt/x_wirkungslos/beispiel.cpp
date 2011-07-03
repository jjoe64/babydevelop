/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* beispiel.cpp */

#include "beispiel.h"

/* Konstruktor */
Beispiel::Beispiel() : ProgrammFenster()
{
   this->setGeometry(10, 10, 200, 130);
   this->setWindowTitle("Hauptfenster");

   fenster = new Testfenster();
   fenster->setGeometry(175, 0, 220, 70);
   fenster->show();
}

/* Destruktor */
Beispiel::~Beispiel ()
{
}
