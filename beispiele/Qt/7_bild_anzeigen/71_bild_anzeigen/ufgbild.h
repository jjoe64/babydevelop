/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* ufgbild.h */

#ifndef UFGBILD_H
#define UFGBILD_H

#include <qlabel.h>
#include <qpixmap.h>
//#include <qwidget.h> //nicht nötig, da QLabel von QWidget abgeleitet ist

class UFGBild : public QLabel
{
   Q_OBJECT
public:
   UFGBild(QString bilddatei=0, QWidget *elternobjekt = 0);   /* Konstruktor */
  ~UFGBild();                                                 /* Destruktor  */
};

#endif
