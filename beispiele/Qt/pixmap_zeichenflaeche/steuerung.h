/* steuerung.h */

#ifndef STEUERUNG_H
#define STEUERUNG_H

#include "/opt/babyDevelop/programmfenster.h"
#include <qpushbutton.h>
#include <qlabel.h>
#include <qpixmap.h>
#include <qpainter.h>

class Steuerung : public ProgrammFenster
{
   Q_OBJECT
public:
   Steuerung(); /* Konstruktor */
  ~Steuerung(); /* Destruktor  */

private:
   QLabel* container;
   QPushButton* taste;

private slots:
   void anpassen();
};

#endif
