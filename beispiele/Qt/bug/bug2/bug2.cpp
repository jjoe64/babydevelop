// Einzelne Pixel setzen
//-----------------------

/* bug2.cpp */

#include "bug2.h"

/* Konstruktor */
BUG2::BUG2(QWidget* elternObjekt) : QLabel(elternObjekt)
{
   this->setGeometry(10, 10, 200, 200);
   this->show();

   malflaeche = QImage("tux.png");
   this->setGeometry(0, 0, malflaeche.width(), malflaeche.height());

   update(); // erwirkt das Zeichnen/Umschalten (Doppel-Pufferung)
}

void BUG2::update()
{
  this->setPixmap(QPixmap::fromImage(malflaeche));
}

/* Destruktor */
BUG2::~BUG2()
{
}
