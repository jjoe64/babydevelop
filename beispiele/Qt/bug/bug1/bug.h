/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* zeichenflaeche.h */

#ifndef BUG_H
#define BUG_H

#include <qwidget.h>

#include <qpainter.h>
#include <qpen.h>
#include <qlist.h>

#include <qlabel.h>

class Linie; //Klassenprototyp
class Punkt; //Klassenprototyp

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class BUG : public QWidget
{
   Q_OBJECT
public:
   BUG(QWidget*);  //Konstruktor; Elternobjekt
  ~BUG();          //Destruktor

private:
   int hintergrundfarbe;
   int bildStatus; //0=aus, 1=ein

private:
   QList<Linie*> linie;
   QList<Punkt*> punkt;
   QLabel* bild;
   double  bildX;
   double  bildY;

private:
   void berechneXfaktor(); //Massstabsfaktoren
   void berechneYfaktor(); //

public slots:
   void loeschen();
   void zeichneLinie(double, double, double, double, int=2, int=0); //Farbe, Breite (optional)
   void zeichnePunkt(double, double, int=2, int=0); //Farbe, Durchmesser (optional)
   void zeichneBild(QString);
   void setzeBildX(double);
   void setzeBildY(double);

   void setzeBreite(int);  //Breite des Zeichenbereichs
   void setzeHoehe(int);   //Hoehe des Zeichenbereichs
   void setzeXmin(double); //mathematische Grenzen des Koordinatensystems
   void setzeXmax(double); //
   void setzeYmin(double); //
   void setzeYmax(double); //
   void setzeHintergrundfarbe(int); //Hintergrundfarbe setzen
   void setzeRandbreite(int);       //Randbreite setzen

protected slots:
   void paintEvent(QPaintEvent*);
};

//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
class Punkt
{
public:
   Punkt(double, double, int, int);  //Konstruktor; Farbe, Durchmesser
  ~Punkt();                          //Destruktor

private:
   double meinX;
   double meinY;
   int meineFarbe;
   int meinDurchmesser;

public:
   double gibX();
   double gibY();
   int gibFarbe();
   int gibDurchmesser();
};

//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
class Linie
{
public:
   Linie(double, double, double, double, int, int);  //Konstruktor; Farbe, Breite
  ~Linie();                                          //Destruktor

private:
   double meinX0;
   double meinY0;
   double meinX1;
   double meinY1;
   int meineFarbe;
   int meineBreite;

public:
   double gibX0();
   double gibY0();
   double gibX1();
   double gibY1();
   int gibFarbe();
   int gibBreite();
};

#endif
