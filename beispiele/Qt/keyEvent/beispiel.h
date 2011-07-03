/* beispiel.h */

#ifndef BEISPIEL_H
#define BEISPIEL_H

#include "/opt/babyDevelop/programmfenster.h"

#include <qevent.h>

class Beispiel : public ProgrammFenster
{
   Q_OBJECT
public:
   Beispiel(); /* Konstruktor */
  ~Beispiel(); /* Destruktor  */

private slots:
   void keyPressEvent(QKeyEvent *e);   /* virtuelle Methode */
};

#endif
