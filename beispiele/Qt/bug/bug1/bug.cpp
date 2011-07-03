/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* bug.cpp */

#include "bug.h"
#include <qmessagebox.h>

// Dateiglobale Variablen
int    breite, hoehe;
int    randbreite;
double xMin, xMax;
double yMin, yMax;
double xFaktor, yFaktor;

/*  Konstruktor */
BUG::BUG(QWidget* elternObjekt) : QWidget(elternObjekt)
{
   //Default
   this->setGeometry(0, 0, 100, 100);

   //Default
   hintergrundfarbe = Qt::gray;
   this->setPalette((Qt::GlobalColor)hintergrundfarbe);
   this->setAutoFillBackground(true);

   //Default
   xMin    = -1.0;
   xMax    = +1.0;
   yMin    = -1.0;
   yMax    = +1.0;
   randbreite = 0;

   this->berechneXfaktor();
   this->berechneYfaktor();

   bildStatus = 0;
}


/* Destruktor */
BUG::~BUG()
{
}

void BUG::paintEvent(QPaintEvent* dummy)
{
qWarning("ha ha ha");

   //Arbeistvariablen
   int farbe;
   int breite;
   int durchmesser;

   //Rand/Darstellungsbereich zeichnen
   if(randbreite != 0)
   {
      if(hintergrundfarbe == Qt::black)
         farbe = Qt::white;
      else
         farbe = Qt::black;

      //p.begin;
      QPainter p(this);
      QPen pen((Qt::GlobalColor)farbe, 0, Qt::SolidLine);
      p.setPen(pen);

      //Linie links zeichnen von unten nach oben
      // die +/-1 am Ende, dass die Randlinie 1 Pixel außerhalb des Zeichenbereichs liegt
      //              Position hier vvvv
      p.drawLine((randbreite+(int)((xMin-xMin)*xFaktor)-1),                            \
                (randbreite+hoehe+randbreite-(int)((yMin-yMin)*yFaktor)-randbreite+1), \
                (randbreite+(int)((xMin-xMin)*xFaktor)-1),                             \
                (randbreite+hoehe+randbreite-(int)((yMax-yMin)*yFaktor)-randbreite)-1);
      //Linie oben zeichnen von links nach rechts
      p.drawLine((randbreite+(int)((xMin-xMin)*xFaktor)-1),                            \
                (randbreite+hoehe+randbreite-(int)((yMax-yMin)*yFaktor)-randbreite-1), \
                (randbreite+(int)((xMax-xMin)*xFaktor)+1),                             \
                (randbreite+hoehe+randbreite-(int)((yMax-yMin)*yFaktor)-randbreite)-1);
      //Linie rechts zeichnen von oben nach unten
      p.drawLine((randbreite+(int)((xMax-xMin)*xFaktor)+1),                            \
                (randbreite+hoehe+randbreite-(int)((yMax-yMin)*yFaktor)-randbreite-1), \
                (randbreite+(int)((xMax-xMin)*xFaktor)+1),                             \
                (randbreite+hoehe+randbreite-(int)((yMin-yMin)*yFaktor)-randbreite)+1);
      //Linie unten zeichnen von links nach rechts
      p.drawLine((randbreite+(int)((xMin-xMin)*xFaktor)-1),                            \
                (randbreite+hoehe+randbreite-(int)((yMin-yMin)*yFaktor)-randbreite+1), \
                (randbreite+(int)((xMax-xMin)*xFaktor)+1),                             \
                (randbreite+hoehe+randbreite-(int)((yMin-yMin)*yFaktor)-randbreite)+1);
      //p.end;
   }

   //Die Linien zeichnen
   for(int z=0; z<linie.count(); z++)
   {
      breite = linie.at(z)->gibBreite();
      farbe  = linie.at(z)->gibFarbe();
      //p.begin;
      QPainter p(this);
      QPen pen((Qt::GlobalColor)farbe, breite, Qt::SolidLine);
      p.setPen(pen);
      // x1, y1, x2, y2
      p.drawLine(randbreite+(int)((linie.at(z)->gibX0()-xMin)*xFaktor),                             \
                 randbreite+hoehe+randbreite-(int)((linie.at(z)->gibY0()-yMin)*yFaktor)-randbreite, \
                 randbreite+(int)((linie.at(z)->gibX1()-xMin)*xFaktor),                             \
                 randbreite+hoehe+randbreite-(int)((linie.at(z)->gibY1()-yMin)*yFaktor)-randbreite);
      //p.end;
   }

   //Die Punkte zeichnen
   for(int z=0; z<punkt.count(); z++)
   {
      durchmesser = punkt.at(z)->gibDurchmesser();
      farbe = punkt.at(z)->gibFarbe();
      //p.begin;
      QPainter p( this );
      QPen pen((Qt::GlobalColor)farbe, durchmesser, Qt::DashLine);
      p.setPen(pen);
      // x, y
      p.drawPoint(randbreite+(int)((punkt.at(z)->gibX()-xMin)*xFaktor), \
                  randbreite+hoehe+randbreite-(int)((punkt.at(z)->gibY()-yMin)*yFaktor)-randbreite);
      //p.end;
   }

   //Bild zeichnen
   if(bildStatus != 0)
   {
      bild->move(randbreite+(int)((bildX-xMin)*xFaktor), randbreite+hoehe+randbreite-(int)((bildY-yMin)*yFaktor)-randbreite);
   }
}

void BUG::loeschen()
{
   //Objekte loeschen

   //Die Linien loeschen
   for(int z=linie.count(); z>0; z--)
   {
      delete linie.at(z-1);
   }
   linie.clear();

   //Die Punkte loeschen
   for(int z=punkt.count(); z>0; z--)
   {
      delete punkt.at(z-1);
   }
   punkt.clear();

   if(bildStatus==1)
      delete bild;
   bildStatus = 0;

   update();
}

void BUG::zeichneLinie(double x0, double y0, double x1, double y1, int farbe, int dicke)
{
   Linie* neueLinie = new Linie(x0, y0, x1, y1, farbe, dicke);
   linie.append(neueLinie);
   update();
}

void BUG::zeichnePunkt(double x, double y, int farbe, int dicke)
{
   Punkt* neuerPunkt = new Punkt(x, y, farbe, dicke);
   punkt.append(neuerPunkt);
   update();
}

void BUG::zeichneBild(QString bilddatei)
{
   if(bildStatus != 0) return;  //Bild schon sichtbar

   bildX = xMin;
   bildY = yMin;
   bild  = new QLabel(this);
   QPixmap b;
   b.load (bilddatei);
   bild->setGeometry( 0, 0, b.width(), b.height() );
   bild->move(randbreite+(int)((bildX-xMin)*xFaktor), randbreite+hoehe+randbreite-(int)((bildY-yMin)*yFaktor)-randbreite);
   bild->setPixmap( b );
   bild->show();
   bildStatus = 1;
//   ueberlauf = 0;

   update();
}

void BUG::setzeBildX(double x)
{
   bildX = x;
   update();
}

void BUG::setzeBildY(double y)
{
   bildY = y;
}

void BUG::setzeXmin(double xm)
{
   xMin = xm;
   if(xMin > xMax)
   {
      QMessageBox::warning(this, "- Warnung -", "xMin > xMax\nSetze xMax auf xMin + 100");
      xMax = xMin + 100.0;
   }
   this->berechneXfaktor();
   this->loeschen();
}

void BUG::setzeXmax(double xm)
{
   xMax = xm;
   if(xMax < xMin)
   {
      QMessageBox::warning(this, "- Warnung -", "xMax < xMin\nSetze xMin auf xMax - 100");
      xMin = xMax - 100.0;
   }
   this->berechneXfaktor();
   this->loeschen();
}

void BUG::setzeYmin(double ym)
{
   yMin = ym;
   if(yMin > yMax)
   {
      QMessageBox::warning(this, "- Warnung -", "yMin > yMax\nSetze yMax auf yMin + 100");
      yMax = yMin + 100.0;
   }
   this->berechneYfaktor();
   this->loeschen();
}

void BUG::setzeYmax(double ym)
{
   yMax = ym;
   if(yMax < yMin)
   {
      QMessageBox::warning(this, "- Warnung -", "yMax < yMin\nSetze yMin auf yMax - 100");
      yMin = yMax - 100.0;
   }
   this->berechneYfaktor();
   this->loeschen();
}

void BUG::berechneXfaktor()
{
   xFaktor = (double)breite / (double)(xMax - xMin);
}

void BUG::berechneYfaktor()
{
   yFaktor = (double)hoehe  / (double)(yMax - yMin);
}

void BUG::setzeHintergrundfarbe(int f)
{
   hintergrundfarbe = f;
   this->setPalette((Qt::GlobalColor)hintergrundfarbe);
   this->setAutoFillBackground(true);
   this->loeschen();
}

void BUG::setzeRandbreite(int r)
{
   randbreite = r;
   this->setzeBreite(breite);
   this->setzeHoehe(hoehe);
}

void BUG::setzeBreite(int b)
{
   if(b<100)
   {
      QMessageBox::warning(this, "- Warnung -", "Breite mind. 100 Pixel!\nSetze Breite auf 100 Pixel.");
      breite = 100;
   }
   else
      breite = b;
   this->setGeometry(this->x(), this->y(), randbreite+breite+randbreite, randbreite+hoehe+randbreite);
   this->berechneXfaktor();
   this->loeschen();
}

void BUG::setzeHoehe(int h)
{
   if(h<100)
   {
      QMessageBox::warning(this, "- Warnung -", "Hoehe mind. 100 Pixel!\nSetze Hoehe auf 100 Pixel.");
      hoehe = 100;
   }
   else
      hoehe = h;
   this->setGeometry(this->x(), this->y(), randbreite+breite+randbreite, randbreite+hoehe+randbreite);
   this->berechneYfaktor();
   this->loeschen();
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
/* Konstruktor */
Punkt::Punkt(double x, double y, int farbe, int durchmesser)
{
   meinX = x;
   meinY = y;
   meineFarbe      = farbe;   //file:///usr/share/qt4/doc/html/qt.html#GlobalColor-enum
   meinDurchmesser = durchmesser;
}

/* Destruktor */
Punkt::~Punkt()
{
}

double Punkt::gibX()
{
   return meinX;
}

double Punkt::gibY()
{
   return meinY;
}

int Punkt::gibFarbe()
{
   return meineFarbe;
}

int Punkt::gibDurchmesser()
{
   return meinDurchmesser;
}

//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
/* Konstruktor */
Linie::Linie(double x0, double y0, double x1, double y1, int farbe, int breite)
{
   meinX0 = x0;
   meinY0 = y0;
   meinX1 = x1;
   meinY1 = y1;
   meineFarbe  = farbe;   //file:///usr/share/qt4/doc/html/qt.html#GlobalColor-enum
   meineBreite = breite;
}

/* Destruktor */
Linie::~Linie()
{
}

double Linie::gibX0()
{
   return meinX0;
}

double Linie::gibY0()
{
   return meinY0;
}

double Linie::gibX1()
{
   return meinX1;
}

double Linie::gibY1()
{
   return meinY1;
}

int Linie::gibFarbe()
{
   return meineFarbe;
}

int Linie::gibBreite()
{
   return meineBreite;
}
