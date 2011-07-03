// Einzelne Pixel setzen
//-----------------------

/* steuerung.cpp */

#include "steuerung.h"

/* Konstruktor */
Steuerung::Steuerung() : ProgrammFenster()
{
   this->setGeometry(10,10,300,300);
   this->setStyleSheet("background-color: yellow");

   //QImage img = QImage(QString::fromStdString(e.gibBild_return));
   bug = new BUG2(this);
   bug->move(10, 10);
   bug->show();

   this->setGeometry(10, 10, bug->width()+20, bug->height()+20);

   takt = new QTimer(this);
   connect(takt, SIGNAL(timeout()), SLOT(tick()));

   srand(time(0));
   takt->start(1000);
}

/* Destruktor */
Steuerung::~Steuerung()
{
}

void Steuerung::tick()
{
   static int x=0;

   for(int z=0; z<10; z++)
   {
      maleKreuz(rand()%(240-8)+4, rand()%(320-8)+4);
   }

   if(x++>10) 
   {
      takt->stop();
      qWarning("fertig");
   }
}

void Steuerung::maleKreuz(int x, int y)
{
   bug->malflaeche.setPixel(x,   y, qRgb(255, 0, 0));
   bug->malflaeche.setPixel(x+1, y, qRgb(255, 0, 0));
   bug->malflaeche.setPixel(x-1, y, qRgb(255, 0, 0));
   bug->malflaeche.setPixel(x+2, y, qRgb(255, 0, 0));
   bug->malflaeche.setPixel(x-2, y, qRgb(255, 0, 0));
   bug->malflaeche.setPixel(x+3, y, qRgb(255, 0, 0));
   bug->malflaeche.setPixel(x-3, y, qRgb(255, 0, 0));
   bug->malflaeche.setPixel(x+4, y, qRgb(255, 0, 0));
   bug->malflaeche.setPixel(x-4, y, qRgb(255, 0, 0));

   bug->malflaeche.setPixel(x, y+1, qRgb(255, 0, 0));
   bug->malflaeche.setPixel(x, y-1, qRgb(255, 0, 0));
   bug->malflaeche.setPixel(x, y+2, qRgb(255, 0, 0));
   bug->malflaeche.setPixel(x, y-2, qRgb(255, 0, 0));
   bug->malflaeche.setPixel(x, y+3, qRgb(255, 0, 0));
   bug->malflaeche.setPixel(x, y-3, qRgb(255, 0, 0));
   bug->malflaeche.setPixel(x, y+4, qRgb(255, 0, 0));
   bug->malflaeche.setPixel(x, y-4, qRgb(255, 0, 0));

   bug->update();
}
