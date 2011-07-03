/* tabelle.cpp */

#include "tabelle.h"

/* Konstruktor */
Tabelle::Tabelle(int rows, int columns, QWidget* parent) : QTableWidget(rows, columns, parent)
{
   this->setGeometry(0, 0, 250, 250);
}

/* Destruktor */
Tabelle::~Tabelle()
{
}

void Tabelle::mousePressEvent(QMouseEvent* e)
{
   qWarning("Tabelle::mousePressEvent");

   if(e->button() == Qt::LeftButton)
   {
      qWarning("LinksKlick");
   }

   if(e->button() == Qt::RightButton)
   {
      qWarning("RechtsKlick");
   }
}
