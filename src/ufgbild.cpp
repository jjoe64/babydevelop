/*-------------*/
/* ufgbild.cpp */
/*-------------*/

#include "ufgbild.h"

#include <qpixmap.h>
#include <qlabel.h>

UFGBild::UFGBild(QWidget *parent) : QWidget(parent)
{
   bildLabel = new QLabel( this );
}


UFGBild::~UFGBild()
{
}

void UFGBild::zeigeBild(QPixmap bild)
{
   bildLabel->setGeometry( 0, 0, bild.width(), bild.height() );
   bildLabel->setPixmap( bild );
}


void UFGBild::mousePressEvent( QMouseEvent* e )
{
   emit mausKlick();
}
