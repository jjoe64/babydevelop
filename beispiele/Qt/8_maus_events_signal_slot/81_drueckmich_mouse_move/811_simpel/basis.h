/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* basis.h */

#ifndef BASIS_H
#define BASIS_H

#include "/opt/babyDevelop/programmfenster.h"           //linux
//#include "/Developer/babyDevelop/programmfenster.h"   //mac

#include <qpushbutton.h>
#include <qmessagebox.h>

#include "fenster.h"

class Basis : public ProgrammFenster
{
   Q_OBJECT
public:
   Basis(); /* Konstruktor */
  ~Basis(); /* Destruktor  */

public:
   QPushButton* taste;

   Fenster  *meinFenster;

public slots:
   void meldung();
   void ende();
};

#endif
