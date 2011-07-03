/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* steuerung.cpp */

#include "steuerung.h"

/* Konstruktor */
Steuerung::Steuerung() : ProgrammFenster()
{
   this->setGeometry(10, 10, 200, 150);

   // Hintergrund des Programmfensters gruen machen
   // Palette des zu manipulierenden Objekts holen
   QPalette paletteP = this->palette();
   // gewünschte Werte ändern
   paletteP.setColor(QPalette::Background, Qt::green);
   // Palette setzen
   this->setPalette(paletteP);
   // automatisches Repaint aktivieren
   this->setAutoFillBackground(true);

   meinBild = new UFGBild("tux.png", this);   // BildDatei, Wo soll das Bild sein?
   meinBild->adjustSize();                    // Antwort: Hier in dieser Klasse
   meinBild->move(10, 30);
   meinBild->show();
}

/* Destruktor */
Steuerung::~Steuerung()
{
}
