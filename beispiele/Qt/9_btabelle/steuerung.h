/* steuerung.h */

#ifndef STEUERUNG_H
#define STEUERUNG_H

#include "/opt/babyDevelop/programmfenster.h"

#include "btabelle.h"
#include <qicon.h>

class Steuerung : public ProgrammFenster
{
   Q_OBJECT
public:
   Steuerung(); //Konstruktor
  ~Steuerung(); //Destruktor

private:
   BTabelle* tabelle;

public slots:
   void auswertenKlick(int, int);
   void auswertenEnter();
};

#endif
