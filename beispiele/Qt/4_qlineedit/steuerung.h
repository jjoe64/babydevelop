/* steuerung.h */

#ifndef STEUERUNG_H
#define STEUERUNG_H

#include "/opt/babyDevelop/programmfenster.h"

#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>

class Steuerung : public ProgrammFenster
{
   Q_OBJECT
public:
   Steuerung (); /* Konstruktor */
  ~Steuerung (); /* Destruktor  */

private:
   QLabel*      papier;
   QLineEdit*   eingabezeile;
   QPushButton* taste;

private slots:
   void uebernehmen();
};

#endif
