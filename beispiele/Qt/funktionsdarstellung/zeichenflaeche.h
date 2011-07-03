/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* zeichenflaeche.h */

#ifndef ZEICHENFLAECHE_H
#define ZEICHENFLAECHE_H

#include <qwidget.h>

#include <qpainter.h>
#include <qpen.h>
#include "linie.h"
#include "punkt.h"

class Zeichenflaeche : public QWidget
{
   Q_OBJECT
public:
   Zeichenflaeche(QWidget*);  /* Konstruktor, Elternobjekt */
  ~Zeichenflaeche();          /* Destruktor                */

private:
   QString stiftfarbe;
   QString blattfarbe;
   int nLinien;
   int nPunkte;
   int loeschModus;

private:
   Linie* linie[555];
   Punkt* punkt[555];

public slots:
   void loeschen();
   void zeichneLinie(int, int, int, int, int);
   void zeichnePunkt(int, int, int);

protected slots:
   void paintEvent(QPaintEvent*);
};

#endif
