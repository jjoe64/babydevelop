/* analogclock.h */

#ifndef ANALOGCLOCK_H
#define ANALOGCLOCK_H

 #include <QWidget>

class AnalogClock : public QWidget

{
   Q_OBJECT
public:
   AnalogClock(QWidget *parent = 0); // Konstruktor
  ~AnalogClock(); // Destruktor
private:
   QTimer* timer;
 protected:
   void paintEvent(QPaintEvent*);
};

#endif
