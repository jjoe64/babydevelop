/* animatedpixmapitem.cpp */

#include "animatedpixmapitem.h"

 #include <QtGui/qbitmap.h>
 #include <QtGui/qpainter.h>


/* Konstruktor */

AnimatedPixmapItem::AnimatedPixmapItem(const QList<QPixmap> &animation, QGraphicsScene *scene)
                  : QGraphicsItem(0, scene), currentFrame(0), vx(0), vy(0)
{
   for(int i = 0; i < animation.size(); ++i)
   {
      QPixmap pixmap = animation.at(i);
      Frame frame;
      frame.pixmap = pixmap;
      frame.shape = QPainterPath();
      frame.boundingRect = pixmap.rect();
      frames << frame;
   }
}

/* Destruktor */
AnimatedPixmapItem::~AnimatedPixmapItem ()
{
}


const int AnimatedPixmapItem::frame()
{
   return currentFrame;
}

const int AnimatedPixmapItem::frameCount()
{
   return frames.size();
}

const QPixmap AnimatedPixmapItem::image(int frame)
{
   return frames.isEmpty() ? QPixmap() : frames.at(frame % frames.size()).pixmap;
}

void AnimatedPixmapItem::setVelocity(qreal xvel, qreal yvel)
{
   vx = xvel;
   vy = yvel;
}

const qreal AnimatedPixmapItem::xVelocity()
{
   return vx;
}

const qreal AnimatedPixmapItem::yVelocity()
{
   return vy;
}

void AnimatedPixmapItem::setFrame(int frame)
{
   if (!frames.isEmpty())
   {
      this->prepareGeometryChange();
      currentFrame = frame % frames.size();
   }
}

void AnimatedPixmapItem::advance(int phase)
{
   if (phase == 1)
      moveBy(vx, vy);
}

 QRectF AnimatedPixmapItem::boundingRect() const
 {
     return frames.at(currentFrame).boundingRect;
 }

QPainterPath AnimatedPixmapItem::shape() const
{
   const Frame &f = frames.at(currentFrame);
   if (f.shape.isEmpty())
   {
      QPainterPath path;
      path.addRegion(f.pixmap.createHeuristicMask());
      const_cast<Frame &>(f).shape = path;
   }
   return f.shape;
}

void AnimatedPixmapItem::paint(QPainter *painter,
                               const QStyleOptionGraphicsItem * /*option*/,
                               QWidget *                        /*widget*/)
{
   painter->drawPixmap(0, 0, frames.at(currentFrame).pixmap);
}
