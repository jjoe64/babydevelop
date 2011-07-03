/*------------*/
/* ufgled.cpp */
/*------------*/

#include "ufgled.h"

extern QString bdpInstallVerzeichnis;

// Konstruktor
//-------------
UFGLed::UFGLed(QWidget *parent, const int nummer, QString s) : BLed(parent), UFGbasis()
{
   objektNummer = nummer;

   objektTyp = 4;   // 1=QLabel, 2=QPushButton, 3=QLineEdit, 4=BLed

   if(s=="Qt::red")     this->setColor(Qt::red);
   if(s=="Qt::yellow")  this->setColor(Qt::yellow);
   if(s=="Qt::green")   this->setColor(Qt::green);
   if(s=="Qt::blue")    this->setColor(Qt::blue);
   if(s=="Qt::white")   this->setColor(Qt::white);
   if(s=="Qt::black")   this->setColor(Qt::black);
   if(s=="Qt::cyan")    this->setColor(Qt::cyan);
   if(s=="Qt::magenta") this->setColor(Qt::magenta);
   if(s=="Qt::gray")    this->setColor(Qt::gray);

}


// Destruktor
//------------
UFGLed::~UFGLed()
{
}


//---------------------------------------------
void UFGLed::mousePressEvent( QMouseEvent* e )
{
   aktion=1;   // 0=Entstehung und noch nicht geklickt
               // 1=geklickt, d.h. schieben oder Groessenaenderung
               // 2=Groessenaenderun
   QRect rect;
   rect=this->geometry();
   x0=rect.x(); y0=rect.y(); breite=rect.width(); hoehe=rect.height();
   // x0 = Abstand vom linken Rand vom Hauptprogramm
   // breite = Breite vom Knopf

   xgm=e->globalX(); ygm=e->globalY();
   // g = global = Maus von Bildschirmrand

   xm=e->x(); ym=e->y();
   // xm = Mausposition

   if( (xm>(breite-15)) && (ym>(hoehe-15)) )   // an der rechten, unteren Ecke gepackt also Groessenaenderung
   {
      aktion=2;
   }
   emit sendeNummer(objektNummer);   // [nummer] senden
}


//--------------------------------------------
void UFGLed::mouseMoveEvent( QMouseEvent* e )
{
   if(aktion>0)
   {
      if(aktion==1)   // schieben    x() ist mit Rahmen
      {
         x0=e->globalX() - xgm + x0; y0=e->globalY() - ygm + y0;
         this->move(rasten(x0),rasten(y0));
         xgm=e->globalX(); ygm=e->globalY();
      }
      else   // Groessenaenderung
      {
         QRect rect;
         rect=this->geometry();
         int x1=e->x();
         int y1=e->y();
         this->setGeometry(rasten(x0), rasten(y0), rasten(x1), rasten(y1));   // Breite und Hoehe sollen gleich sein
//         fertigAufziehen();
      }
   }
}


//-----------------------------------------------
void UFGLed::mouseReleaseEvent( QMouseEvent* e )
{
   aktion=0;
}

