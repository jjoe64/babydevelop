/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* fenster.h */

#ifndef FENSTER_H
#define FENSTER_H

#include "/opt/babyDevelop/programmfenster.h"

#include <qlabel.h>

class Fenster : public ProgrammFenster
{
   Q_OBJECT
public:
   Fenster(QWidget*,int);   /* Konstruktor */
  ~Fenster();               /* Destruktor  */

public:
   int meineNummer;

public:
   QLabel* papier;

public slots:
   void mouseMoveEvent( QMouseEvent* );

signals:
   void sichtbarmachen(int);
};

#endif
