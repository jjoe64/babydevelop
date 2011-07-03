/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* steuerung.cpp */

#include "steuerung.h"

#include <time.h>

/* Konstruktor */
Steuerung::Steuerung () : ProgrammFenster ()
{
   this->setGeometry(100, 100, 620, 327);
   this->setPalette(Qt::magenta);
   this->setAutoFillBackground(true);

   srand(time(0));

   meineZeichenflaeche = new Zeichenflaeche(this);
   meineZeichenflaeche->move(10, 10);
   meineZeichenflaeche->show();

   textFlaeche = new QLabel("", this);    //Screen für Textausgaben
   textFlaeche->setGeometry(100, 216, 510, 100);
   textFlaeche->setPalette(Qt::green);
   textFlaeche->setAutoFillBackground(true);
   textFlaeche->show();

   tasteZeichne = new QPushButton("Zeichne", this);   //Start_der_Berechnungen-Taste
   tasteZeichne->setGeometry(10, 215, 80, 30);
   tasteZeichne->show();
   connect(tasteZeichne, SIGNAL(clicked()), SLOT(zeichne()));

   tasteCls = new QPushButton("Cls",this);   //ClsTaste
   tasteCls->setGeometry(10, 250, 80, 30);
   tasteCls->show();
   connect(tasteCls, SIGNAL(clicked()), SLOT(cls()));

   tasteEnde = new QPushButton("Ende", this);   //Programmende-Taste
   tasteEnde->setGeometry(10, 285, 80, 30);
   tasteEnde->show();
   connect(tasteEnde, SIGNAL(clicked()), SLOT(ende()));
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
   meineZeichenflaeche->loeschen();
   textFlaeche->setText("");
}

void Steuerung::zeichne()
{
   //Arbeistvariablen
   int farbe;

   //x-Achse
   meineZeichenflaeche->zeichneLinie(10, 90, 575, 90, Qt::cyan);
   //y-Achse
   meineZeichenflaeche->zeichneLinie(10, 10, 10, 180, Qt::cyan);

   //Sinus-Funktion mit Punkten
   float x = 0, y;
   const float pi=3.142;
   const int anzahl = 100; //Anzahl der Berechnungen
   const float schrittweite = 2.0*pi/anzahl;

   for(int i=0; i<=anzahl; i++)
   {
      y = sin(x);
      farbe = rand()%17+2; //2...19
      if(farbe==5)farbe=12; //nicht Hintergrundfarbe
      meineZeichenflaeche->zeichnePunkt((int)(x*90.0)+10, 90-(int)(y*80.0), farbe);
      x = x + schrittweite;
   }

   textFlaeche->setText("<center><h3>Sinusfunktion<br>im Bereich von<br>0 bis 2*Pi</h3></center>");
}
