/* analogclock.cpp */

#include "analogclock.h"

#include <QtGui>

 #include "analogclock.h"

 AnalogClock::AnalogClock(QWidget *parent) : QWidget(parent)
 {
     timer = new QTimer(this);
     connect(timer, SIGNAL(timeout()), SLOT(update()));
     timer->start(1000);

     this->setWindowTitle("Analog Clock");
     this->resize(200, 200);
 }

// Destruktor
AnalogClock::~AnalogClock()
{
}

void AnalogClock::paintEvent(QPaintEvent*)
{
   //Stundenzeiger
   QColor hourColor(127, 0, 127);
   static const QPoint hourHand[3] = {
         QPoint(7, 8),
         QPoint(-7, 8),
         QPoint(0, -40)
     };

   //Minutenzeiger
   QColor minuteColor(0, 127, 127, 191);
   static const QPoint minuteHand[3] = {
         QPoint(7, 8),
         QPoint(-7, 8),
         QPoint(0, -70)
     };

     int side   = qMin(width(), height());
     QTime time = QTime::currentTime();

     QPainter painter(this);
     painter.setRenderHint(QPainter::Antialiasing);
     painter.translate(width() / 2, height() / 2);
     painter.scale(side / 200.0, side / 200.0);

     painter.setPen(Qt::NoPen);
     painter.setBrush(hourColor);

     painter.save();
     painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
     painter.drawConvexPolygon(hourHand, 3);
     painter.restore();

     painter.setPen(hourColor);

   //5-Minuten-Skala
   for(int i = 0; i < 12; ++i)
   {
      painter.drawLine(88, 0, 96, 0);
      painter.rotate(30.0);
   }

     painter.setPen(Qt::NoPen);
     painter.setBrush(minuteColor);

     painter.save();
     painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
     painter.drawConvexPolygon(minuteHand, 3);
     painter.restore();

     painter.setPen(minuteColor);

   //Minutenskala ohne 5-Minuten-Skala
   for(int j = 0; j < 60; ++j)
   {
      if ((j % 5) != 0)
         painter.drawLine(92, 0, 96, 0);
      painter.rotate(6.0);
   }

}

