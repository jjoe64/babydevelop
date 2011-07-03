// Einzelne Pixel setzen
//-----------------------

/* steuerung.h */

#ifndef STEUERUNG_H
#define STEUERUNG_H

#include "/opt/babyDevelop/programmfenster.h"

#include <QImage>
#include <qtimer.h>
#include <stdlib.h>
#include <time.h>

#include "bug2.h"

class Steuerung : public ProgrammFenster
{
   Q_OBJECT
public:
   Steuerung(); /* Konstruktor */
  ~Steuerung(); /* Destruktor  */

private:
   BUG2*   bug;
   QTimer* takt;

private:
   void maleKreuz(int x, int y);

private slots:
   void tick();
};

#endif
