/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* links.h */

#ifndef LINKS_H
#define LINKS_H

#include "/opt/babyDevelop/programmfenster.h"

#include <qlabel.h>

class Links : public ProgrammFenster
{
   Q_OBJECT
public:
   Links(QWidget*);   /* Konstruktor */
  ~Links();           /* Destruktor  */

public:
   QLabel* papier;

public slots:
   void mouseMoveEvent( QMouseEvent* );

signals:
   void sichtbarmachen(int);
};

#endif
