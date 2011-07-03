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


  // newItem->setBackground(QBrush(bg));
//   newItem->setForeground(QBrush(fg));

   fg = Qt::black; // Vorgabe
   bg = Qt::white; // Vorgabe

   connect(t, SIGNAL( cellClicked(int, int) ), SLOT( zelleKlick(int, int)));
}

/* Destruktor */
BTabelle::~BTabelle()
{
}

void BTabelle::setzeText(int x, int y, QString zeichen)
{
   QTableWidgetItem *newItem = new QTableWidgetItem(zeichen);
   newItem->setBackground(QBrush(bg));
   newItem->setForeground(QBrush(fg));
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

void BTabelle::keyPressEvent(QKeyEvent* e)
{
   //qWarning("Taste::keyPressEvent(QKeyEvent* e)");
   //e->accept();  // Annehmen des KeyEvents
   switch( e->key() )
   {                       // Hinweis: die Rueckgabecodes der einzelnen Tasten findet man in der "qnamespace.h" und in file:///usr/share/qt4/doc/html/qt.html#Key-enum
      //case Qt::Key_X:    // Taste "x" gedueckt
      //   qWarning("Taste x");
      //   break;
      case Qt::Key_Return: // Taste "Enter" gedueckt
         //qWarning("Taste Enter");
         emit enter();
         break;
   }
}

void BTabelle::setzeHintergrundfarbe(QColor b)
{
   bg = b;
}

void BTabelle::setzeVordergrundfarbe(QColor f)
{
   fg = f;
}
