/* btabelle.cpp */

#include "btabelle.h"

#include<QTableWidgetItem>

/* Konstruktor */
BTabelle::BTabelle(int spalten, int reihen, QWidget *elternObjekt) : QWidget(elternObjekt)
{
   breite = 100; //Vorgabe
   hoehe  = 100;

   t = new QTableWidget(reihen, spalten, this);
   t->verticalHeader()->hide();
   t->horizontalHeader()->hide();

   connect(t, SIGNAL( cellClicked(int, int) ), SLOT( zelleKlick(int, int)));
}

/* Destruktor */
BTabelle::~BTabelle()
{
}

void BTabelle::setzeText(int x, int y, QString zeichen)
{
   QTableWidgetItem *newItem = new QTableWidgetItem(zeichen);
   t->setItem(y, x, newItem);
}

void BTabelle::setzeAnzahlReihen(int n)
{
   t->setRowCount(n);
}

void BTabelle::setzeAnzahlSpalten(int n)
{
   t->setColumnCount(n);
}

void BTabelle::setzeReihenhoehe(int r, int h)
{
   t->setRowHeight(r, h);
}

void BTabelle::setzeSpaltenbreite(int s, int b)
{
   t->setColumnWidth(s, b);
}

void BTabelle::setzeTabellenbreite(int b)
{
    breite = b;
    t->setGeometry(0, 0, breite, hoehe);
}

void BTabelle::setzeTabellenhoehe(int h)
{
    hoehe = h;
    t->setGeometry(0, 0, breite, hoehe);
}

void BTabelle::setzeBild(int x, int y, QIcon bild)
{
   QTableWidgetItem* i = new QTableWidgetItem(bild, 0);
   t->setItem( x, y, i );
}

void BTabelle::zelleKlick(int reihe, int spalte)
{
   emit angeklicktZelle(spalte, reihe);
}
