/* steuerung.h */

#ifndef STEUERUNG_H
#define STEUERUNG_H

#include "/opt/babyDevelop/programmfenster.h"

#include <qpushbutton.h>
#include <qpalette.h>

class Steuerung : public ProgrammFenster
{
   Q_OBJECT
public:
   Steuerung (); /* Konstruktor */
  ~Steuerung (); /* Destruktor  */

private:
   QPushButton* tasteBeenden;

private slots:
   void beenden();
};

#endif
