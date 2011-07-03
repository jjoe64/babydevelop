/* steuerung.cpp */

#include "steuerung.h"

#include <qdebug.h>
#include <qmessagebox.h>

const float PI = 3.142;

/* Konstruktor */
Steuerung::Steuerung() : ProgrammFenster()
{
   this->setGeometry(10, 10, 310, 360);

   // Zeichenflaeche erzeugen
   welt = new QGraphicsScene();
   //                    x0,   y0, breite, hoehe
   welt->setSceneRect( -100, -100,    200,   200 );
   welt->setBackgroundBrush(Qt::blue);

   // Schaufenster erzeugen durch das die Welt/Zeichenflaeche bzw. ein Ausschnitt davon betrachtet wird
   fenster = new QGraphicsView( welt, this );
   fenster->setRenderHints( QPainter::Antialiasing );
   //                    x0, y0, breite, hoehe
   fenster->setGeometry( 10, 10,    210,   210 );
   fenster->show();

   // Spritebilder laden
   QList<QPixmap> panzerBilder;
   for(int i=0; i< 3;i++)
   {
      QPixmap p("sprites/panzer_gelb_000" + QString::number(i) + ".xpm");
      panzerBilder.append(p);
   }

   // Sprite anzeigen
   panzerSprite = new AnimatedPixmapItem(panzerBilder, welt);
   v = 4;
   winkel = 0;
   vx = v * cos(winkel);
   vy = v * sin(winkel);
   panzerSprite->setPos(-50, 0);
   panzerSprite->setVelocity(vx, vy);
qDebug() << "winkel=" << winkel << " Grad   vx=" << vx << "   vy=" << vy;

   lfdFrame = 0;

   timer = new QTimer(this);
   timer->start(77);
   connect(timer, SIGNAL( timeout() ), SLOT( weiter() ) );

   tasteEnde = new QPushButton("Ende", this);
   tasteEnde->setGeometry(10, 320, 70, 30);
   tasteEnde->show();
   connect(tasteEnde, SIGNAL( clicked() ), SLOT( beenden() ) );

}

/* Destruktor */
Steuerung::~Steuerung()
{
}


void Steuerung::weiter()
{
   lfdFrame++;
//qDebug() << "lfdFrame=" << lfdFrame;
   panzerSprite->advance(1);
   panzerSprite->setFrame(lfdFrame);

   // am Rand
   if( panzerSprite->pos().x() < -100 )                          // Rand links
      v = 0;
   if( panzerSprite->pos().x() > (100-20) )                      // Rand rechts
      v = 0;
   if( panzerSprite->pos().y() < -100)                           // Rand oben
      v = 0;
   if( panzerSprite->pos().y() > (100-10) )                      // Rand unten
      v = 0;

   // Blickrichtung berechnen
   vx = v * cos(winkel);
   vy = v * sin(winkel);
   panzerSprite->setVelocity(vx, vy);
qDebug() << "Winkel=" << winkel*180/PI << " Grad   vx=" << vx << "   vy=" << vy;
}


void Steuerung::keyReleaseEvent(QKeyEvent *e) // keyReleaseEvent haben sie wohl vergessen :( fuer Pfeiltasten
{
   e->accept();
   qDebug() << "Taste losgelassen";
   int taste = e->key();
   switch ( taste )
   {                     // Hinweis: die Rueckgabecodes der einzelnen Tasten findet man in der "qnamespace.h"
      case Qt::Key_Left:     // Pfeiltaste "links" gedueckt
         qWarning("Taste links");
         winkel = winkel - 2*3.142/16;  // durch 8 -> 45Grad
         break;
      case Qt::Key_Right:
         qWarning("Taste rechts");
         winkel = winkel + 2*3.142/16;  // durch 8 -> 45Grad
         break;
      case Qt::Key_Up:
         qWarning("Taste auf");
         v++;
         break;
      case Qt::Key_Down:
         qWarning("Taste ab");
         v--;
         break;
      case Qt::Key_X:     // Taste "x" gedueckt?
         qWarning("Taste x");
         break;
   }

   // Fahrtrichtung berechnen
   vx = v * cos(winkel);
   vy = v * sin(winkel);
   panzerSprite->setVelocity(vx, vy);

   // Blickrichtung einstellen

   // file:///usr/share/qt4/doc/html/qgraphicsitem.html#rotate
   //    Rotate an item 45 degrees around (x, y).
   //    item->setTransform(QTransform().translate(x, y).rotate(45).translate(-x, -y));
   // Rotiere um Punkt x,y mit Ursprung bei dir selber
   panzerSprite->setTransform(QTransform().translate(15,15).rotate(winkel*180/PI).translate(-15, -15));
qDebug() << "Winkel=" << winkel*180/PI << " Grad   vx=" << vx << "   vy=" << vy;
}


void Steuerung::beenden()
{
   exit(0);
}
