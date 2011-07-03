/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* beispiel.h */

#ifndef BEISPIEL_H
#define BEISPIEL_H

#include "/opt/babyDevelop/programmfenster.h"

#include "testfenster.h"

class Beispiel : public ProgrammFenster
{
   Q_OBJECT
public:
   Beispiel (); /* Konstruktor */
  ~Beispiel (); /* Destruktor  */
public:
   Testfenster* fenster;
};

#endif
