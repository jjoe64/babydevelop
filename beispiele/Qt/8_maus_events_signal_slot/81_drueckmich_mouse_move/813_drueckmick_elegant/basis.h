/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* basis.h */

#ifndef BASIS_H
#define BASIS_H

#include "/opt/babyDevelop/programmfenster.h"

#include <qpushbutton.h>

#include "fenster.h"

class Basis : public ProgrammFenster
{
   Q_OBJECT
public:
   Basis(); /* Konstruktor */
  ~Basis(); /* Destruktor  */

public:
   QPushButton* taste;
   Fenster*     meinLinkesFenster;
   Fenster*     meinRechtesFenster;

public slots:
   void einschalten(int);
   void ende();
};

#endif
