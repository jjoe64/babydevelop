/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* steuerung.cpp */

#include "steuerung.h"

/* Konstruktor */
Steuerung::Steuerung () : ProgrammFenster ()
{
   this->setGeometry(50, 50, 200, 200);
   this->setStyleSheet("background-color: yellow");

   blatt = new QLabel("", this);
   blatt->setGeometry(10, 10, 30, 30);
   blatt->setStyleSheet("background-color: lightgrey");
   blatt->show();

   taste = new QPushButton("Start", this);
   taste->setGeometry(100, 100, 60, 40);
   taste->setStyleSheet("background-color: lightblue");
   taste->show();
   connect(taste, SIGNAL(clicked()), SLOT(losgehts()));

   zeit = 10;

   zaehler = new QTimer(this);
   connect(zaehler, SIGNAL(timeout()), SLOT(abwaerts()));

   n_move  = 0;

   maus_x=50;
   maus_y=50;

   this->setMouseTracking(true); //move auch bei nicht gedrückter Maustaste
                                 //aber nicht über anderem Objekt
   //vgl.: file:///usr/share/qt4/doc/html/qmouseevent.html#details

   //Anmerkung:
   //   Soll auch maus-move-Bewegung über weiteren objekten
   //   von steuerung verarbeitet werden, so müssen die
   //   Objekte ihre mouse-move-Bewegung an die steuerung senden
}

/* Destruktor */
Steuerung::~Steuerung ()
{
}

void Steuerung::mouseMoveEvent(QMouseEvent* e)
{
   qWarning("Steuerung-move %i", n_move);
   n_move++;
   maus_x=e->x();
   maus_y=e->y();
}

void Steuerung::abwaerts()
{
   blatt->setText("<center>"+QString::number(zeit)+"</center>");
   zeit=zeit-1;

   if(zeit<0)
   {
      meinBild = new UFGBild("tux.png", this);   // BildDatei laden
      meinBild->adjustSize();                    // Bild-aufnahmendes Objekt an Bildgröße anpassen
      meinBild->move(maus_x-meinBild->width()/2, maus_y-meinBild->height()/2);
      meinBild->show();
      connect(meinBild, SIGNAL(mausbewegung(int, int)), SLOT(verschiebe(int, int)));
      connect(meinBild, SIGNAL(mausklick()), SLOT(mausloesen()));
      zaehler->stop();
   }
}

void Steuerung::losgehts()
{
   taste->setEnabled(false);
   zaehler->start(1000);
}

void Steuerung::verschiebe(int x, int y)
{
   meinBild->move(meinBild->x()+x, meinBild->y()+y);
}

void Steuerung::mausloesen()
{
   disconnect(meinBild, SIGNAL(mausbewegung(int, int)), this, SLOT(verschiebe(int, int)));
}
