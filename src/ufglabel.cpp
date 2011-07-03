/*--------------*/
/* ufglabel.cpp */
/*--------------*/

#include "ufglabel.h"

// Konstruktor
//-------------
UFGLabel::UFGLabel(QWidget* parent, const int nummer, QString s) : QLabel(parent, Qt::Widget), UFGbasis()
{
   objektNummer = nummer;

   objektTyp = 1;   // 1=QLabel, 2=QPushButton, 3=QLineEdit, 4=BLed
   this->setText(s);

   QColor farbe_gelb;
      farbe_gelb.setRgb(252, 255, 0); // yellow
   QPalette p_gelb;
      p_gelb.setColor(QPalette::Window, farbe_gelb);
   this->setPalette(p_gelb);

   this->setAutoFillBackground( true );

}

// Destruktor
//------------
UFGLabel::~UFGLabel()
{
}


//-----------------------------------------------
void UFGLabel::mousePressEvent( QMouseEvent* e )
{
   aktion=1; // 0=Entstehung und noch nicht geklickt
             // 1=geklickt, d.h. schieben oder Groessenaenderung
             // 2=Groessenaenderun
   QRect rect;
   rect   = QLabel::geometry();
   x0     = rect.x(); y0=rect.y();
   breite = rect.width();
   hoehe  = rect.height();
   // x0 = Abstand vom linken Rand vom Hauptprogramm
   // breite = Breite vom Knopf

   xgm = e->globalX(); ygm=e->globalY();
   // g = global = Maus von Bildschirmrand

   xm = e->x(); ym=e->y();
   // xm = Mausposition innerhalb des Widgets

   if( (xm>(breite-15)) && (ym>(hoehe-15)) )   // an der rechten, unteren Ecke gepackt also Groessenaenderung
   {
      aktion=2;
   }
   emit sendeNummer(objektNummer);   // [nummer] senden
}


//--------------------------------------------
void UFGLabel::mouseMoveEvent( QMouseEvent* e )
{
   if(aktion > 0)
   {
      if(aktion == 1)   // schieben    x() ist mit Rahmen
      {
         x0  = e->globalX() - xgm + x0;
         y0  = e->globalY() - ygm + y0;
         this->move(rasten(x0), rasten(y0));
         xgm = e->globalX();
         ygm = e->globalY();
      }
      else   // Groessenaenderung
      {
         QRect rect;
         rect = this->geometry();
         int x1 = e->x();
         int y1 = e->y();
         this->setGeometry(rasten(x0), rasten(y0), rasten(x1), rasten(y1));
//         fertigAufziehen();
      }
   }
}


//-------------------------------------------------
void UFGLabel::mouseReleaseEvent( QMouseEvent* e )
{
   aktion=0;
}

