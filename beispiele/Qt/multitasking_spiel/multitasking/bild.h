/* bild.h */

#ifndef BILD_H
#define BILD_H

#include <qlabel.h>
#include <qpixmap.h>

class Bild : public QLabel
{
   Q_OBJECT
public:
   Bild (QWidget *elternobjekt = 0, QString bilddatei=0);   /* Konstruktor */
  ~Bild ();                                                 /* Destruktor  */

};

#endif
