/* steuerung.cpp */

#include "steuerung.h"

/* Konstruktor */
Steuerung::Steuerung () : ProgrammFenster ()
{
   this->setWindowTitle("- BLed-Beispiel -");
   this->setGeometry(100, 200, 230, 260);

   lampe = new BLed(this);
   lampe->setGeometry(20, 20, 190, 190);
   lampe->setColor("yellow");
   lampe->off();
   lampe->show();

   tasteEin = new QPushButton("Einschalten",this);
   tasteEin->setGeometry(10, 220, 100, 30);
   tasteEin->show();
   connect(tasteEin, SIGNAL(clicked()), SLOT(ein()));

   tasteAus = new QPushButton("Ausschalten", this);
   tasteAus->setGeometry(120, 220, 100, 30);
   tasteAus->show();
   connect(tasteAus, SIGNAL(clicked()), SLOT(aus()));

   takt = new QTimer(this);
   connect(takt, SIGNAL( timeout() ), SLOT( schalten() ) );
}

/* Destruktor */
Steuerung::~Steuerung ()
{
}

void Steuerung::ein()
{
   takt->start(350);
}

void Steuerung::aus()
{
   takt->stop();
   lampe->off();
}

void Steuerung::schalten()
{
   lampe->toggle();
}
