/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* fenster.h */

#ifndef FENSTER_H
#define FENSTER_H

#include "/opt/babyDevelop/programmfenster.h"           //linux
//#include "/Developer/babyDevelop/programmfenster.h"   //mac

#include <qlabel.h>

class Fenster : public ProgrammFenster
{
   Q_OBJECT
public:
   Fenster(QWidget* parent=0);   /* Konstruktor */
  ~Fenster();                    /* Destruktor  */

public:
   QLabel* papier;

public slots:
   void mouseMoveEvent( QMouseEvent* );

signals:
   void sichtbarmachen();
};

#endif
