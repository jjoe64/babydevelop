/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* Steuerung.h */

#ifndef STEUERUNG_H
#define STEUERUNG_H

#include "/opt/babyDevelop/programmfenster.h"

#include "ufgbild.h"
#include <QMouseEvent>

class Steuerung : public ProgrammFenster
{
   Q_OBJECT
public:
   Steuerung(); /* Konstruktor */
  ~Steuerung(); /* Destruktor  */

private:
   int n_press;
   int n_move;
   int n_over;

private:
   UFGBild *meinBild;

private slots:
   void mousePressEvent( QMouseEvent* );
   void mouseMoveEvent ( QMouseEvent* );
   void mouseOverEvent ( QMouseEvent* );
};

#endif

