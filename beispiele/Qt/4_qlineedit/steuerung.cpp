/* steuerung.cpp */

#include "steuerung.h"

/* Konstruktor */
Steuerung::Steuerung () : ProgrammFenster ()
{
   this->setWindowTitle("- QLineEdit-Beispiel -");
   this->resize(400,200);

   papier = new QLabel("", this);
   papier->setGeometry(10, 20, 300, 70);     //Lage und Groesse
   papier->setAlignment(Qt::AlignCenter); //Zentrierte Anordnung

   papier->setPalette(Qt::yellow);        // Hintergrundfarbe
   papier->setAutoFillBackground(true);   // Hintergrundfarbe automatisch zeichnen, wenn notwendig

   papier->show();

   eingabezeile = new QLineEdit("", this);
   eingabezeile->setGeometry(10, 100, 200, 30);

   taste = new QPushButton("Uebernehmen", this);
   taste->setGeometry(10, 150, 120, 30);
   taste->show();
   connect(taste,SIGNAL(clicked()),SLOT(uebernehmen()));

}

/* Destruktor */
Steuerung::~Steuerung ()
{
}

void Steuerung::uebernehmen()
{
   QString meinText = eingabezeile->text();
   papier->setText(meinText);
}
