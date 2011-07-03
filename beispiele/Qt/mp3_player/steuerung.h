/* steuerung.h */

#ifndef STEUERUNG_H
#define STEUERUNG_H

#include "/opt/babyDevelop/programmfenster.h"

#include "suchen.h"
#include "gui.h"
#include "spielen.h"
#include <qdir.h>

class Steuerung : public ProgrammFenster
{
   Q_OBJECT
public:
   Steuerung (); /* Konstruktor */
  ~Steuerung (); /* Destruktor  */
private:
   GUI     *dasGUI;
   Suchen  *dieSuche;
   Spielen *dasSpielen;
public slots:
   void uebergibText(QString);
   void spieleLied(QString);
   void beende();
};

#endif
