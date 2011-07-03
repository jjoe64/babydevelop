/* spieler.h */

#ifndef SPIELER_H
#define SPIELER_H

#include "bild.h"
#include <QMouseEvent>

class Spieler : public Bild
{
   Q_OBJECT
public:
   Spieler (QWidget *elternobjekt = 0, QString bilddatei=0);   /* Konstruktor */
  ~Spieler ();                                                 /* Destruktor  */

   int x0, y0;
   int xgm, ygm;

public slots:
   void mousePressEvent( QMouseEvent* );
   void mouseMoveEvent ( QMouseEvent* );

signals:
   void startBotschaft();
};

#endif
