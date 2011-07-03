/*---------------*/
/* ufglineedit.h */
/*---------------*/

#ifndef UFGLINEEDIT_H
#define UFGLINEEDIT_H

#include <qwidget.h>
#include <qlineedit.h>
#include "ufgbasis.h"

#include <qevent.h>
#include <qrect.h>

#include <qlabel.h>

class UFGLineEdit : public QLineEdit, public UFGbasis
{
   Q_OBJECT
public:
   UFGLineEdit(QWidget* parent=0,const int nummer=0,QString s=NULL); // Konstruktor
  ~UFGLineEdit();                                                    // Destruktor

public slots:
   void mousePressEvent( QMouseEvent* );
   void mouseReleaseEvent( QMouseEvent* );
   void mouseMoveEvent( QMouseEvent* );

signals:
   void sendeNummer(int);

};

#endif
