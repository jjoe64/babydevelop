/* steuerung.h */

#ifndef STEUERUNG_H
#define STEUERUNG_H

#include "/opt/babyDevelop/programmfenster.h"

#include <QLCDNumber>
#include <qtimer.h>

class Steuerung : public ProgrammFenster
{
   Q_OBJECT
public:
   Steuerung(); /* Konstruktor */
  ~Steuerung(); /* Destruktor  */
private:
   int n;
private:
   QLCDNumber* lcd;
   QTimer*     takt;
private slots:
   void weiter();
};

#endif
