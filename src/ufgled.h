/*----------*/
/* ufgled.h */
/*----------*/

#ifndef UFGLED_H
#define UFGLED_H

#include <qwidget.h>
#include "ufgbasis.h"
#include "bled.h"

#include <QMouseEvent>

#include <qlabel.h>

class UFGLed : public BLed, public UFGbasis
{
   Q_OBJECT
public:
   UFGLed(QWidget* parent=0, const int nummer=0, QString s="Qt::green"); // Konstruktor
  ~UFGLed();                                                             // Destruktor

public slots:
   void mousePressEvent( QMouseEvent* );
   void mouseReleaseEvent( QMouseEvent* );
   void mouseMoveEvent( QMouseEvent* );

signals:
   void sendeNummer(int);

};

#endif
