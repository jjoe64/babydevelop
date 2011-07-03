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
   int n_move;

public slots:
   void mouseMoveEvent( QMouseEvent* );
   void mousePressEvent( QMouseEvent* );

signals:
   void mausBewegung(int, int);
   void mausKlick();
};

#endif
