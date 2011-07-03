/* steuerung.cpp */

#include "steuerung.h"

/* Konstruktor */
Steuerung::Steuerung() : ProgrammFenster()
{
   t = new BTabelle(8, 3, this);
   t->setzeTabellenbreite(270);
   t->setzeTabellenhoehe(110);
t->setGeometry(10, 10, 300, 300);
   t->show();

   for(int z=0; z<8; z++)
      t->setzeSpaltenbreite(z, 30);
   for(int z=0; z<3; z++)
      t->setzeReihenhoehe(z, 30);

   t->setzeText(2, 1, "H");
   t->setzeText(3, 1, "a");
   t->setzeText(4, 1, "l");
   t->setzeText(5, 1, "l");
   t->setzeText(6, 1, "o");

   QIcon i("schreihals.xpm");
   t->setzeBild(1, 1, i);

connect(t, SIGNAL(cellClicked(int, int)), SLOT( auswerten(int, int)));
}

/* Destruktor */
Steuerung::~Steuerung ()
{
}

void Steuerung::auswerten(int row, int column)
{
qWarning("hahaha");
}
