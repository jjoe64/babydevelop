// Einzelne Pixel setzen
//-----------------------

/* bug2.h */

#ifndef BUG2_H
#define BUG2_H

#include <qwidget.h>
#include <qlabel.h>
#include <qpixmap.h>

class BUG2 : public QLabel
{
   Q_OBJECT
public:
   BUG2(QWidget*); /* Konstruktor */
  ~BUG2();         /* Destruktor  */

public:
   void update();

public:
   QImage malflaeche;
};

#endif
