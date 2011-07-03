/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* ufgbild.h */

#ifndef UFGBILD_H
#define UFGBILD_H

#include <qpixmap.h>
#include <qlabel.h>
#include <qevent.h>

//#include <qwidget.h> //nicht nötig, da QLabel von QWidget abgeleitet ist

class UFGBild : public QLabel
{
   Q_OBJECT
public:
   UFGBild(QString bilddatei=0, QWidget *parent = 0);   //BildDatei, zugehöriges Eltern-Widget
  ~UFGBild();

private:
   int n_press;
   int n_move;
   int n_over;

public slots:
   void mousePressEvent( QMouseEvent* );
   void mouseMoveEvent ( QMouseEvent* );
   void mouseOverEvent ( QMouseEvent* );

};

#endif
