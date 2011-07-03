/* animatedpixmapitem.h */

#ifndef ANIMATEDPIXMAPITEM_H
#define ANIMATEDPIXMAPITEM_H

 #include <QGraphicsItem>
#include <qtimer.h>

class AnimatedPixmapItem : public QGraphicsItem
{ 
public:
   AnimatedPixmapItem(const QList<QPixmap> &animation, QGraphicsScene *scene = 0); // Konstruktor
  ~AnimatedPixmapItem ();   // Destruktor

private:
   struct Frame
   {
      QPixmap pixmap;
      QPainterPath shape;
      QRectF boundingRect;
   };

   int currentFrame;
   qreal vx, vy;
   QList<Frame> frames;

public:
   void advance(int phase);
   const QPixmap image(int frame);
   void setFrame(int frame);
   void setVelocity(qreal xvel, qreal yvel);
   const int frame();
   const int frameCount();
   const qreal xVelocity();
   const qreal yVelocity();
   QRectF boundingRect() const;
   QPainterPath shape() const;
   void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif
