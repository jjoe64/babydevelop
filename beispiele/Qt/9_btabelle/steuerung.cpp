/* steuerung.cpp */

#include "steuerung.h"

/* Konstruktor */
Steuerung::Steuerung() : ProgrammFenster()
{
   tabelle = new BTabelle(8, 3, this);
   tabelle->setzeTabellenbreite(270);
   tabelle->setzeTabellenhoehe(110);
   tabelle->show();

   for(int z=0; z<8; z++)
      tabelle->setzeSpaltenbreite(z, 30);
   for(int z=0; z<3; z++)
      tabelle->setzeReihenhoehe(z, 30);

   tabelle->setzeText(2, 1, "H");
   tabelle->setzeText(3, 1, "a");
   tabelle->setzeText(4, 1, "l");
   tabelle->setzeVordergrundfarbe(Qt::magenta);
   tabelle->setzeHintergrundfarbe(Qt::blue);

   tabelle->setzeText(5, 1, "l");
   tabelle->setzeText(6, 1, "o");

   QIcon i("schreihals.xpm");
   tabelle->setzeBild(1, 1, i);

   connect(tabelle, SIGNAL( angeklicktZelle(int, int) ), SLOT( auswertenKlick(int, int) ) );
   connect(tabelle, SIGNAL( enter() ), SLOT( auswertenEnter() ) );
}

/* Destruktor */
Steuerung::~Steuerung ()
{
}

void Steuerung::auswertenKlick(int spalte, int reihe)
{
qWarning("hahaha spalte=%i reihe=%i", spalte, reihe);
}

void Steuerung::auswertenEnter()
{
qWarning("hohoho Enter");
}
