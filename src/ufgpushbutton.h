/*-----------------*/
/* ufgpushbutton.h */
/*-----------------*/

#ifndef UFGPUSHBUTTON_H
#define UFGPUSHBUTTON_H

#include <qwidget.h>
#include <qpushbutton.h>
#include "ufgbasis.h"

#include <qevent.h>
#include <qrect.h>

#include <qlabel.h>

class UFGPushButton : public QPushButton, public UFGbasis
{
   Q_OBJECT
public:
   UFGPushButton(QWidget* parent=0,const int nummer=0,QString s=NULL); // Konstruktor
  ~UFGPushButton();                                                    // Destruktor

public slots:
   void mousePressEvent( QMouseEvent* );
   void mouseReleaseEvent( QMouseEvent* );
   void mouseMoveEvent( QMouseEvent* );

signals:
   void sendeNummer(int);

};

#endif
