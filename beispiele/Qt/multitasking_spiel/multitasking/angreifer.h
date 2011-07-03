/* angreifer.h */

#ifndef ANGREIFER_H
#define ANGREIFER_H

#include "bild.h"
#include "konstanten"

class Angreifer : public Bild
{
   Q_OBJECT
public:
   Angreifer (QWidget *elternobjekt = 0, QString bilddatei=0);   /* Konstruktor */
  ~Angreifer ();                                                 /* Destruktor  */

private:
  double vx, vy;
  int    breite, hoehe;
  double posX, posY;

public:
   void setzeParameter(int, int, double, double);

public slots:
   void  bewege();
   QRect gibPosition();
};

#endif
