/*-----------*/
/* ufgbild.h */
/*-----------*/

#ifndef UFGBILD_H
#define UFGBILD_H

#include <qwidget.h>

#include <qpixmap.h>
#include <qlabel.h>
#include <qevent.h>
#include <QSignalMapper>

class UFGBild : public QWidget
{
   Q_OBJECT
public:
   UFGBild(QWidget *parent = 0);
  ~UFGBild();

private:
   QLabel *bildLabel;

public slots:
   void zeigeBild( QPixmap );
   void mousePressEvent( QMouseEvent* );

signals:
   void mausKlick();
};

#endif
