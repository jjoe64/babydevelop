/* steuerung.cpp */

#include "steuerung.h"
#include <qrect.h>

/* Konstruktor */
Steuerung::Steuerung () : ProgrammFenster ()
{
   this->setFixedSize(BILDPUNKTE, BILDPUNKTE+50);

   spielfeld = new Bild(this, "spielfeld.png");
   spielfeld->show();

   derAngreifer[0] = new Angreifer(this, "hindernis0.png");
   derAngreifer[0]->setzeParameter(70, 70, 2.1, 1.4); //x,y,vx,vy
   derAngreifer[0]->show();

   derAngreifer[1] = new Angreifer(this, "hindernis1.png");
   derAngreifer[1]->setzeParameter(270, 60, -1.4, 1.6);
   derAngreifer[1]->show();

   derAngreifer[2] = new Angreifer(this, "hindernis2.png");
   derAngreifer[2]->setzeParameter(70, 320, 1.8, -1.56);
   derAngreifer[2]->show();

   derAngreifer[3] = new Angreifer(this, "hindernis3.png");
   derAngreifer[3]->setzeParameter(300, 330, -1.4, -2.2);
   derAngreifer[3]->show();

   derSpieler = new Spieler(this, "spieler.png");
   derSpieler->move(205, 205);
   derSpieler->show();

   zeitgeber = new QTimer(this);
   connect(zeitgeber, SIGNAL(timeout()), SLOT(systemtakt()));
   connect(derSpieler, SIGNAL(startBotschaft()), SLOT(start()));

   startzeit = new QTime();
   intervall = 10;

   tasteEnde = new QPushButton("Ende",this);
   tasteEnde->setGeometry(10, BILDPUNKTE+10, 70, 30);
   tasteEnde->show();
   connect(tasteEnde,SIGNAL(clicked()),SLOT(ende()));

   tasteNochmal = new QPushButton("Nochmal",this);
   tasteNochmal->setGeometry(BILDPUNKTE-80, BILDPUNKTE+10, 70,30);
   tasteNochmal->setDisabled(true);
   tasteNochmal->show();
   connect(tasteNochmal, SIGNAL(clicked()), SLOT(nochmal()));
}

/* Destruktor */
Steuerung::~Steuerung ()
{
}


void Steuerung::systemtakt()
{
   if( startzeit->elapsed() > (11-intervall)*5000 )
   {
      intervall -= 1;
      zeitgeber->setInterval(intervall);
qWarning("Geschwindigkeit (intervall) auf %i erhoeht.",intervall);  
   }

   /* Objekte verschieben */
   for(int z=0; z<4; z++)
   {
      derAngreifer[z]->bewege();
   }

   /* Kollision ja/nein */
   for(int z=0; z<4; z++)
   {
      if(pruefeKollision(z) == 1)
      {
         zeitgeber->stop();
         QMessageBox::information(this,
                                  "- Kollision -",
                                  "verloren :-(<br>" + \
                                   QString::number((double)startzeit->elapsed()/1000) + \
                                  "&nbsp;Sekunden" );
         tasteNochmal->setDisabled(false);
      }
   }

   if(pruefeWandberuehrung())
   {
      zeitgeber->stop();
      QMessageBox::information(this,
                               "- Wandberuehrung -",
                               "verloren :-(<br>" + \
                                QString::number((double)startzeit->elapsed()/1000) + \
                               "&nbsp;Sekunden" );
      tasteNochmal->setDisabled(false);
   }
}


int Steuerung::pruefeWandberuehrung()
{
   /* Randberührung ja/nein */
   if(derSpieler->x() < 50)
      return 1;
   if( (derSpieler->x() + derSpieler->width()) > (BILDPUNKTE - 50))
      return 1;
   if(derSpieler->y() < 50)
      return 1;
   if( (derSpieler->y() + derSpieler->height()) > (BILDPUNKTE - 50))
      return 1;
   return 0;
}


int Steuerung::pruefeKollision(int objektNummer)
{
   QRect r = derAngreifer[objektNummer]->gibPosition();
   int x1, y1, x2, y2;
   r.getCoords(&x1, &y1 ,&x2, &y2);

   if( x2 < derSpieler->x() )
      return 0;   //keine Beruehrung
   if( x1 > (derSpieler->x() + derSpieler->width()) )
      return 0;   //keine Beruehrung
   if( y2 < derSpieler->y() )
      return 0;   //keine Beruehrung
   if( y1 > (derSpieler->y() + derSpieler->height()) )
      return 0;   //keine Beruehrung
   return 1;   //Beruehrung
}


void Steuerung::start()
{
   zeitgeber->start(intervall);
   startzeit->start();
   tasteNochmal->setDisabled(true);
}


void Steuerung::nochmal()
{
   tasteNochmal->setDisabled(true);
   derAngreifer[0]->setzeParameter(70, 70, 2.1, 1.4); //x,y,vx,vy
   derAngreifer[1]->setzeParameter(270, 60, -1.4, 1.6);
   derAngreifer[2]->setzeParameter(70, 320, 1.8, -1.56);
   derAngreifer[3]->setzeParameter(300, 330, -1.4, -2.2);
   derSpieler->move(205,205);

   intervall = 10;
   zeitgeber->setInterval(intervall);
   zeitgeber->stop();
}

void Steuerung::ende()
{
   exit (0);
}
