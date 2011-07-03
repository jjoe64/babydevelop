/* bild.cpp */

#include "bild.h"

/* Konstruktor */
Bild::Bild (QWidget* elternobjekt, QString bilddatei) : QLabel (elternobjekt)
{
   QPixmap bild;
   bild.load ( bilddatei );
   this->setGeometry( 0, 0, bild.width(), bild.height() );
   this->setPixmap( bild );
}

/* Destruktor */
Bild::~Bild ()
{
}
