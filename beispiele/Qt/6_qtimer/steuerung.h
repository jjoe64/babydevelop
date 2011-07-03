/* steuerung.h */

#ifndef STEUERUNG_H
#define STEUERUNG_H

#include "/opt/babyDevelop/programmfenster.h"

#include "bled.h"
#include <qpushbutton.h>
#include <qtimer.h>

class Steuerung : public ProgrammFenster
{
   Q_OBJECT
public:
   Steuerung (); /* Konstruktor */
  ~Steuerung (); /* Destruktor  */

private:
   BLed* lampe;
   QPushButton* tasteEin;
   QPushButton* tasteAus;
   QTimer* takt;

private slots:
   void ein();
   void aus();
   void schalten();
};

#endif
