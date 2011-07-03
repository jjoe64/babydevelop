/* steuerung.cpp */

#include "steuerung.h"

/* Konstruktor */
Steuerung::Steuerung () : ProgrammFenster ()
{
   this->setWindowTitle("- QLabel-Beispiel -");
   this->setGeometry(100, 200, 270, 110);

   papier_links = new QLabel("Hallo links",this);
   papier_links->setGeometry(20,20,100,70);

   //-------------------------------------------------------------------------
   // Farbsteuerung Variante 1 (einfacher)
   // Nachteil: Kann z.B. Hintergrundfarbe von QPushButton-Objekten mitändern
   //-------------------------------------------------------------------------

   papier_links->setPalette(Qt::yellow);        // Hintergrundfarbe
   papier_links->setAutoFillBackground(true);   // Hintergrundfarbe automatisch zeichnen, wenn notwendig
   papier_links->setAlignment(Qt::AlignCenter); // Zentrierte Anordnung
   papier_links->show();


   //-------------------------------------------------------------------------
   // Komplexere Farbsteuerung ist leider etwas aufwaendiger
   //-------------------------------------------------------------------------
/*
   QColor farbe_gelb;                         // Gelb soll es sein
      farbe_gelb.setRgb(252,255,0);           // yellow
      QPalette palette_gelb;                  // Bestimmt die Behandlung z.B. Aufhellen beim Ueberfahren mit der Maus
      palette_gelb.setColor(QPalette::Window, farbe_gelb);
   papier_links->setAutoFillBackground(true); // Hintergrund automatisch zeichnen, wenn notwendig
   papier_links->setPalette(palette_gelb);
*/
   //------------------------------------------------------------------------
   papier_rechts = new QLabel("Hallo rechts",this);
   papier_rechts->setGeometry(150,20,100,70);
   papier_rechts->setAlignment(Qt::AlignCenter); // Zentrierte Anordnung
   papier_rechts->setPalette(Qt::red);           // Hintergrundfarbe
   papier_rechts->setAutoFillBackground(true);   // Hintergrundfarbe automatisch zeichnen, wenn notwendig
   papier_rechts->show();
}

/* Destruktor */
Steuerung::~Steuerung ()
{
}
