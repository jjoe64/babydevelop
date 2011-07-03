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
   blatt->setGeometry(10, 10, 40, 40);
   blatt->setStyleSheet("background-color: lightgrey");
   blatt->show();
   blatt->setFrameStyle(1);

   textAnzeige = new QLabel("<center>Start druecken</center>", this);
   textAnzeige->setGeometry(60, 10, 130, 40);
   textAnzeige->setStyleSheet("background-color: lightgreen");
   textAnzeige->show();
   textAnzeige->setFrameStyle(51); // QFrame::Shape:Panel=2 || QFrame::Shadow:Sunken=48
                                   // ergibt 51
   taste = new QPushButton("Start", this);
   taste->setGeometry(100, 100, 60, 40);
   taste->setStyleSheet("background-color: lightblue");
   taste->show();
   connect(taste, SIGNAL(clicked()), SLOT(losgehts()));

   zeit        = 10;
   erzeugeNr   = 0;
   alleErzeugt = 0;
   lastVerschiebe=-1;

   zaehler = new QTimer(this);
   connect(zaehler, SIGNAL(timeout()), SLOT(abwaerts()));

   n_move  = 0;

   maus_x = 50;
   maus_y = 50;

   this->setMouseTracking(true); //move auch bei nicht gedrückter Maustaste
                                 //aber nicht über anderem Objekt
   //vgl.: file:///usr/share/qt4/doc/html/qmouseevent.html#details

   //Anmerkung:
   //   Soll auch maus-move-Bewegung über weiteren Objekten
   //   von steuerung verarbeitet werden, so müssen die
   //   Objekte ihre mouse-move-Ereignisse an steuerung senden
}

/* Destruktor */
Steuerung::~Steuerung ()
{
}

void Steuerung::mouseMoveEvent(QMouseEvent* e)
{
   qWarning("Steuerung-move %i", n_move);
   n_move++;
   maus_x = e->x();
   maus_y = e->y();
}

void Steuerung::abwaerts()
{
   blatt->setText("<center>"+QString::number(zeit)+"</center>");
   zeit = zeit-1;

   if(zeit<0)
   {
      meinBild[erzeugeNr] = new UFGBild(erzeugeNr, "tux.png", this); //BildDatei laden
      meinBild[erzeugeNr]->adjustSize();  //Bild-aufnehmendes Objekt an Bildgröße anpassen
      meinBild[erzeugeNr]->move(maus_x-meinBild[erzeugeNr]->width()/2, maus_y-meinBild[erzeugeNr]->height()/2);
      meinBild[erzeugeNr]->show();
      connect(meinBild[erzeugeNr], SIGNAL(mausBewegung(int, int, int)), SLOT(verschiebe(int, int, int)));
      connect(meinBild[erzeugeNr], SIGNAL(mausKlick(int)), SLOT(mausKlickVerarbeitung(int)));
      zaehler->stop();
      textAnzeige->setText("<center>Verschiebe und<br>Klicke Bild</center>");
   }
}

void Steuerung::losgehts()
{
   zaehler->start(1000);
   taste->setEnabled(false);
   textAnzeige->setText("<center>Maus bewegen</center>");
}

void Steuerung::verschiebe(int nr, int x, int y)
{
   meinBild[nr]->move(meinBild[nr]->x()+x, meinBild[nr]->y()+y);
}

void Steuerung::mausKlickVerarbeitung(int nr)
{
   if(alleErzeugt != 1)   //weitere Bild-Objekte erzeugen
   {
      if( (erzeugeNr<5) && (nr==erzeugeNr) ) //"&& (nr==erzeugeNr)" nur um Fehleingaben (Klick bei Move) abzufangen
      {
         textAnzeige->setText("<center>Verschiebe Maus</center>");
         disconnect(meinBild[nr], SIGNAL(mausBewegung(int, int, int)), this, SLOT(verschiebe(int, int, int)));
         erzeugeNr++;   //nächstes Objekt
         if(erzeugeNr<5)
         {
            zaehler->start(1000);
            blatt->setText("<center>: )</center>");
         }
         else
         {
            blatt->setText("Ende");
            alleErzeugt = 1;
            textAnzeige->setText("<center>Verschiebe und<br>Klicke Bild</center>");
         }
         zeit = 10;
      }
   }
   else   //bereits erzeugte Bild-Objekte verschieben
   {
      if(lastVerschiebe == nr)
      {
         disconnect(meinBild[lastVerschiebe], SIGNAL(mausBewegung(int, int, int)), this, SLOT(verschiebe(int, int, int)));
      }
      if(nr != lastVerschiebe)
      {
         connect(meinBild[nr], SIGNAL(mausBewegung(int, int, int)), this, SLOT(verschiebe(int, int, int)));
         lastVerschiebe=nr;
      }
   }
}
