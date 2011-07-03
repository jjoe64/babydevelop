/* steuerung.cpp */

#include "steuerung.h"

/* Konstruktor */
Steuerung::Steuerung () : ProgrammFenster ()
{
   this->setWindowTitle("- Farbsteuerung -");
   this->setGeometry(100, 200, 300, 90);

   tasteBeenden = new QPushButton("Beenden",this);
   tasteBeenden->setGeometry(10, 10, 80, 30);
   tasteBeenden->show();
   connect(tasteBeenden,SIGNAL(clicked()),SLOT(beenden()));


   // Hintergrund des Programmfensters gelb machen
   //----------------------------------------------
   this->setStyleSheet( "background-color: yellow;" );
   //this->setAutoFillBackground(true); // Hintergrund automatisch zeichnen, wenn notwendig


   // Farbe des QPushButtons einstellen
   //-----------------------------------
   // vgl.: http://doc.qt.nokia.com/4.5/stylesheet-examples.html#customizing-the-foreground-and-background-colors
   tasteBeenden->setStyleSheet( "color: red;" "background-color: lightgreen;" );
   //tasteBeenden->setAutoFillBackground(true); // Hintergrund automatisch zeichnen, wenn notwendig

}

/* Destruktor */
Steuerung::~Steuerung ()
{
}

void Steuerung::beenden()
{
   //qApp->exit(0);
   //exit(0);
   close();
}
