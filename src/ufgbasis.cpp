/*--------------*/
/* ufgbasis.cpp */
/*--------------*/

#include <QtDebug>
#include "ufgbasis.h"

extern QString bdpInstallVerzeichnis;

// Konstruktor
//-------------
UFGbasis::UFGbasis()
{
   aktion = 0;
}

// Destruktor
//------------
UFGbasis::~UFGbasis()
{
}

//--------------------------------------------
void UFGbasis::setNummer( int n )
{
   objektNummer = n;
}

//--------------------------------------------
int UFGbasis::getObjektTyp()
{
   return objektTyp;
}

//--------------------------------------------
void UFGbasis::setObjektName(QString n)
{
   objektName = n;
}

//--------------------------------------------
QString UFGbasis::getObjektName()
{
   return objektName;
}

//--------------------------------------------
int UFGbasis::rasten(int z)
{
   return (z+5)/10*10;
}


void UFGbasis::fertigAufziehen() //beim Erzeugen der Objekte
{
//qDebug() << "objektName = " << objektName;

   int b = ((QWidget*) this)->width();    //this->width();
qWarning("-4- breite = %i", b);
   int h = ((QWidget*) this)->height();   //this->height(); 
qWarning("-5- hoehe = %i", h);
int x0 = ((QWidget*) this)->geometry().x();
qWarning("-6- x0 = %i", x0);
int y0 = ((QWidget*) this)->geometry().y();
qWarning("-7- y0 = %i", y0);

}


