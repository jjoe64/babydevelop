/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* zeichenflaeche.cpp */

#include "zeichenflaeche.h"

/*  Konstruktor */
Zeichenflaeche::Zeichenflaeche(QWidget* elternObjekt = 0) : QWidget(elternObjekt)
{
   this->setGeometry(0, 0, 600, 200); //default

   this->setPalette(Qt::gray);
   this->setAutoFillBackground(true);

   nLinien = 0;
   nPunkte = 0;
   loeschModus = 0;
}


/* Destruktor */
Zeichenflaeche::~Zeichenflaeche ()
{
}


void Zeichenflaeche::paintEvent(QPaintEvent* dummy)
{
qWarning("ha ha ha");

   //Arbeistvariablen
   int farbe;

   //Die Linien zeichnen
   for(int z=0; z<nLinien; z++)
   {
      farbe = linie[z]->gibFarbe();
      //p.begin;
      QPainter p(this);
      QPen pen((Qt::GlobalColor)farbe, 0, Qt::SolidLine);
      p.setPen(pen);
      // x1, y1, x2, y2
      p.drawLine( linie[z]->gibX0(), linie[z]->gibY0(), linie[z]->gibX1(), linie[z]->gibY1() );
      //p.end;
   }

   //Die Punkte zeichnen
   for(int z=0; z<nPunkte; z++)
   {
      farbe = punkt[z]->gibFarbe();
      //p.begin;
      QPainter p( this );
      QPen pen((Qt::GlobalColor)farbe, 5, Qt::DashLine);
      p.setPen(pen);
      // x, y
      p.drawPoint( punkt[z]->gibX(), punkt[z]->gibY() );
      //p.end;
   }
}

void Zeichenflaeche::loeschen()
{
   //Objekte loeschen

   //Die Linien loeschen
   for(int z=nLinien; z>-1; z--)
   {
      delete linie[z];
   }
   nLinien = 0;

   //Die Punkte loeschen
   for(int z=nPunkte; z>-1; z--)
   {
      delete punkt[z];
   }
   nPunkte = 0;

   update();
}

void Zeichenflaeche::zeichneLinie(int x0, int y0, int x1, int y1, int farbe)
{
   linie[nLinien] = new Linie(x0, y0, x1, y1, farbe);
   nLinien++;

   update();
}

void Zeichenflaeche::zeichnePunkt(int x, int y, int farbe)
{
   punkt[nPunkte] = new Punkt(x, y, farbe);
   nPunkte++;

   update();
}
