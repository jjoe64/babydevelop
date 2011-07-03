/*------------*/
/* ufglabel.h */
/*------------*/

#ifndef UFGLABEL_H
#define UFGLABEL_H

#include <qwidget.h>
#include <qlabel.h>
#include "ufgbasis.h"

#include <qevent.h>
#include <qrect.h>

class UFGLabel : public QLabel, public UFGbasis
{
   Q_OBJECT
public:
   UFGLabel(QWidget* parent=0, const int nummer=0, QString s=NULL); // Konstruktor
  ~UFGLabel();                                                      // Destruktor

public slots:
   void mousePressEvent( QMouseEvent* );
   void mouseReleaseEvent( QMouseEvent* );
   void mouseMoveEvent( QMouseEvent* );

signals:
   void sendeNummer(int);

};

#endif
