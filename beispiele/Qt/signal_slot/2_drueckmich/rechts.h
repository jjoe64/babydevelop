/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* rechts.h */

#ifndef RECHTS_H
#define RECHTS_H

#include "/opt/babyDevelop/programmfenster.h"           //linux
//#include "/Developer/babyDevelop/programmfenster.h"   //mac

#include <qlabel.h>

class Rechts : public ProgrammFenster
{
   Q_OBJECT
public:
   Rechts(QWidget*);   /* Konstruktor */
  ~Rechts();           /* Destruktor  */

public:
   QLabel* papier;

public slots:
   void mouseMoveEvent( QMouseEvent* );

signals:
   void sichtbarmachen(int);
};

#endif
