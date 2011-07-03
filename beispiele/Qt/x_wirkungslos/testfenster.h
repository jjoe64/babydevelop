/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* testfenster.h */

#ifndef TESTFENSTER_H
#define TESTFENSTER_H

#include "/opt/babyDevelop/programmfenster.h"

#include <QCloseEvent>

class Testfenster : public ProgrammFenster
{
   Q_OBJECT
public:
   Testfenster ();   /* Konstruktor */
  ~Testfenster ();   /* Destruktor  */

private:
   void closeEvent(QCloseEvent *e);   //nicht auf [X] reagieren

};

#endif
