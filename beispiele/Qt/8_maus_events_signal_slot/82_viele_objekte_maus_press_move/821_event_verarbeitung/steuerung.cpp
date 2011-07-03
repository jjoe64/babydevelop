/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* steuerung.cpp */

#include "steuerung.h"

/* Konstruktor */
Steuerung::Steuerung () : ProgrammFenster ()
{
   this->setGeometry(50,50,200,120);
   this->setStyleSheet("background-color: yellow");

   meinBild = new UFGBild("tux.png", this);   // BildDatei, Wo soll das Bild erscheinen?
   meinBild->adjustSize();                    // Antwort: Hier in dieser Klasse
   meinBild->move(10, 30);
   meinBild->show();

   n_press = 0;
   n_move  = 0;
   n_over  = 0;

this->setMouseTracking(true); //move auch bei nicht gedrückter maustaste
                                //aber nicht über anderem objekt
   //vgl.: file:///usr/share/qt4/doc/html/qmouseevent.html#details
//Anmerkung:
// Soll auch maus-move-bewegung über weiteren objekten
// von steuerung verarbeitet werden, so müssen die
// objekte ihre mouse-move-bewegung an die steuerung senden

//this->grabMouse(); //move nur bei gedrückter maus
                     //auch wenn über anderem objekt
}

/* Destruktor */
Steuerung::~Steuerung ()
{
}

void Steuerung::mousePressEvent( QMouseEvent* e )
{
   qWarning("Steuerung-press %i", n_press);
   n_press++;
}

void Steuerung::mouseMoveEvent( QMouseEvent* e )
{
   qWarning("Steuerung-move %i", n_move);
   n_move++;
}

void Steuerung::mouseOverEvent( QMouseEvent* e )
{
   qWarning("Steuerung-over %i", n_over);
   n_over++;
}
