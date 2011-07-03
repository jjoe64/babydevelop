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

   // Ein Bild
   QPixmap bild("tux.png"); 

   container = new QLabel(this);
   container->setGeometry(10, 10, 180, 130);

   // Hintergrund des Containers gelb machen
   // Palette des zu manipulierenden Objekts holen
   QPalette palette = container->palette();
   // gewünschte Werte ändern
   palette.setColor(QPalette::Background, Qt::yellow);
   // Palette setzen
   container->setPalette(palette);
   // automatisches Repaint aktivieren
   container->setAutoFillBackground(true);

   // Bild anzeigen
   container->setPixmap(bild);
   container->adjustSize(); // Zeichenflaeche auf Bildgroesse anpassen
   container->move(50, 30);
   container->show(); 
}

/* Destruktor */
Steuerung::~Steuerung()
{
}
