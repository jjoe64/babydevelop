/* steuerung.h */
/*
http://doc.trolltech.com/4.2/graphicsview.html
*/

#ifndef STEUERUNG_H
#define STEUERUNG_H

#include "/opt/babyDevelop/programmfenster.h"

#include <qpushbutton.h>

#include <qgraphicsscene.h>
#include <qgraphicsview.h>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QList>
#include <QPixmap>
#include <qtimer.h>
#include <qevent.h>
#include <QWidget>
#include <math.h>

#include "animatedpixmapitem.h"

class Steuerung : public ProgrammFenster
{
   Q_OBJECT
public:
   Steuerung(); /* Konstruktor */
  ~Steuerung(); /* Destruktor  */

public:
   QPushButton* tasteEnde;
   QTimer* timer;
   AnimatedPixmapItem* panzerSprite;
   int lfdFrame;
   int xrichtung;
   int yrichtung;
   qreal v, vx, vy; // Geschwindigkeit
   qreal winkel;

   QGraphicsScene* welt;
   QGraphicsView* fenster;

public slots:
   void beenden();
   void weiter();

   void keyReleaseEvent(QKeyEvent *e);    /* virtuelle Methode */
};

#endif
