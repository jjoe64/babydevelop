/* btabelle.cpp */

#include "btabelle.h"

#include<QTableWidgetItem>

/* Konstruktor */
BTabelle::BTabelle(int spalten, int reihen, QWidget *elternObjekt) : QTableWidget(elternObjekt)
{
   breite = 100; //Vorgabe
   hoehe  = 100;
this->setGeometry(10, 10, 400, 200);
//   t = new QTableWidget(reihen, spalten, this);
   this->verticalHeader()->hide();
   this->horizontalHeader()->hide();
setzeAnzahlReihen(reihen);
setzeAnzahlSpalten(spalten);

}

/* Destruktor */
BTabelle::~BTabelle()
{
}

void BTabelle::setzeText(int x, int y, QString zeichen)
{
   QTableWidgetItem *newItem = new QTableWidgetItem(zeichen);
   this->setItem(y, x, newItem);
}

void BTabelle::setzeAnzahlReihen(int n)
{
   this->setRowCount(n);
}

void BTabelle::setzeAnzahlSpalten(int n)
{
   this->setColumnCount(n);
}

void BTabelle::setzeReihenhoehe(int r, int h)
{
   this->setRowHeight(r, h);
}

void BTabelle::setzeSpaltenbreite(int s, int b)
{
   this->setColumnWidth(s, b);
}

void BTabelle::setzeTabellenbreite(int b)
{
    breite = b;
    this->setGeometry(0, 0, breite, hoehe);
}

void BTabelle::setzeTabellenhoehe(int h)
{
    hoehe = h;
    this->setGeometry(0, 0, breite, hoehe);
}

void BTabelle::setzeBild(int x, int y, QIcon bild)
{
   QTableWidgetItem* i = new QTableWidgetItem(bild, 0);
   this->setItem( x, y, i );
}

//void BTabelle::cellClicked(int row, int column)
//{
//qWarning("hahaha");
//}

