/* angreifer.cpp */

#include "angreifer.h"

/* Konstruktor */
Angreifer::Angreifer (QWidget* elternobjekt, QString bilddatei) : Bild (elternobjekt,bilddatei)
{
   vx = 0.0;
   vy = 0.0;
   breite = this->width();
   hoehe  = this->height();
}

/* Destruktor */
Angreifer::~Angreifer ()
{
}


void Angreifer::setzeParameter(int positionX, int positionY, double geschwindigkeitX, double geschwindigkeitY)
{
   this->move(positionX,positionY);
   posX = positionX;
   posY = positionY;
   this->vx = geschwindigkeitX;
   this->vy = geschwindigkeitY;
}


void Angreifer::bewege()
{
   if(BILDPUNKTE - this->x() - breite <= 0) //rechter Rand
      vx *= -1;

   if(BILDPUNKTE - this->y() - hoehe <= 0)  //unterer Rand
      vy *= -1;

   if(this->x() <= 0) //linker Rand
      vx *= -1;

   if(this->y() <= 0) //oberer Rand
      vy *= -1;

   posX = posX + vx;
   posY = posY + vy;
   this->move((int)posX, (int)posY);
}

QRect Angreifer::gibPosition()
{
   return this->geometry();
}
