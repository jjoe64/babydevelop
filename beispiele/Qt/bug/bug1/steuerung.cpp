/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* steuerung.cpp */

#include "steuerung.h"

#include <qapplication.h>
#include <time.h>

const double Pi = 3.142;

/* Konstruktor */
Steuerung::Steuerung() : ProgrammFenster()
{
   this->setGeometry(100, 100, 610, 327);
   this->setPalette(Qt::yellow);
   this->setAutoFillBackground(true);

   srand(time(0));

   meineGrafikflaeche = new BUG(this);
   meineGrafikflaeche->setzeBreite(570);
   meineGrafikflaeche->setzeHoehe(170);
   meineGrafikflaeche->setzeRandbreite(10);
   meineGrafikflaeche->move(10, 10);
   meineGrafikflaeche->show();

   meineGrafikflaeche->setzeXmin(0);
   meineGrafikflaeche->setzeXmax(2*Pi);
   meineGrafikflaeche->setzeYmin(-1);
   meineGrafikflaeche->setzeYmax(+1);
   meineGrafikflaeche->setzeHintergrundfarbe(Qt::gray);

   textFlaeche = new QLabel("", this);    //Screen für Textausgaben
   textFlaeche->setGeometry(100, 216, 500, 100);
   textFlaeche->setPalette(Qt::green);
   textFlaeche->setAutoFillBackground(true);
   textFlaeche->show();

   tasteZeichne = new QPushButton("Zeichne", this);   //Start_der_Berechnungen-Taste
   tasteZeichne->setGeometry(10, 215, 80, 30);
   tasteZeichne->show();
   connect(tasteZeichne, SIGNAL(clicked()), SLOT(zeichne()));

   tasteCls = new QPushButton("Cls", this);   //ClsTaste
   tasteCls->setGeometry(10, 250, 80, 30);
   tasteCls->show();
   connect(tasteCls, SIGNAL(clicked()), SLOT(cls()));

   tasteEnde = new QPushButton("Ende", this);   //Programmende-Taste
   tasteEnde->setGeometry(10, 285, 80, 30);
   tasteEnde->show();
   connect(tasteEnde, SIGNAL(clicked()), SLOT(ende()));

   timer = new QTimer(this);
   connect(timer, SIGNAL(timeout()), SLOT(weiter()));

   pos = 0;
}

/* Destruktor */
Steuerung::~Steuerung ()
{
}

void Steuerung::ende()
{
   qApp->quit();
}

void Steuerung::cls()
{
   timer->stop();
   meineGrafikflaeche->loeschen();
   textFlaeche->setText("");
   pos = 0;
}

void Steuerung::zeichne()
{
   //Arbeistvariablen
   int farbe;

   //x-Achse
   meineGrafikflaeche->zeichneLinie(0, 0, 2.0*Pi, 0, Qt::cyan, 2);
   //y-Achse
   meineGrafikflaeche->zeichneLinie(0, -1, 0, +1, Qt::cyan, 2);

   //Sinus-Funktion mit Punkten
   double x = 0, y;
   int anzahl = 100; //Anzahl der Berechnungen
   double schrittweite = 2.0*Pi/anzahl;

   for(double i=0; i<=2.0*Pi; i=i+schrittweite)
   {
      y = sin(x);
      farbe = rand()%17+2; //2...19
      if(farbe==Qt::gray)farbe=Qt::red; //nicht Hintergrundfarbe
      meineGrafikflaeche->zeichnePunkt(x, y, farbe, farbe); //letzter Parameter = Durchmesser
      x = x + schrittweite;
   }

   meineGrafikflaeche->zeichneBild("lotus_elise.png");
   meineGrafikflaeche->setzeBildX(0);
   meineGrafikflaeche->setzeBildY(0.25);

   timer->start(100);

   textFlaeche->setText("<center><h3>Sinusfunktion<br>im Bereich von<br>0 bis 2*Pi</h3></center>");
}

void Steuerung::weiter()
{
   meineGrafikflaeche->setzeBildX(pos);
   pos = pos + 0.1;
   if(pos>2*Pi)pos=0;
}

