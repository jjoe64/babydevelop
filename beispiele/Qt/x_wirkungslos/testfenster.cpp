/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* testfenster.cpp */

#include "testfenster.h"

/* Konstruktor */
Testfenster::Testfenster () : ProgrammFenster ()
{
   this->setWindowTitle("no closing :-)");

   // Farbsteuerung ist leider etwas aufwaendig
   // Palette des zu manipulierenden Objekts holen
   QPalette palette = this->palette();
   // gewünschte Werte ändern
   palette.setColor(QPalette::Background, Qt::yellow);
   // Palette setzen
   this->setPalette(palette);
   // automatisches Repaint aktivieren
   this->setAutoFillBackground(true);
}

/* Destruktor */
Testfenster::~Testfenster ()
{
}

/* nicht auf [X] reagieren         */
/* clicking the X title bar button */
void Testfenster::closeEvent(QCloseEvent *e)
{
   e->ignore();
}
