/* spieler.cpp */

#include "spieler.h"

/* Konstruktor */
Spieler::Spieler (QWidget* elternobjekt, QString bilddatei) : Bild (elternobjekt,bilddatei)
{
}

/* Destruktor */
Spieler::~Spieler ()
{
}


//--------------------------------------------
void Spieler::mousePressEvent( QMouseEvent* e )
{
   QRect rect;
   rect=this->geometry();

   //x0 = Abstand vom linken Rand vom Hauptprogramm
   x0=rect.x(); y0=rect.y();

   //g = global = Maus von Bildschirmrand
   xgm=e->globalX(); ygm=e->globalY();

   //xm=e->x(); ym=e->y();
   //xm = Mausposition
   emit startBotschaft();
}

//--------------------------------------------
void Spieler::mouseMoveEvent( QMouseEvent* e )
{
   x0=e->globalX() - xgm + x0; y0=e->globalY() - ygm + y0;
   this->move(x0,y0);
   xgm=e->globalX(); ygm=e->globalY();
}
