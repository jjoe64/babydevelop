/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* ufgbild.cpp */

#include "ufgbild.h"

UFGBild::UFGBild(QString bilddatei, QWidget *parent) : QLabel(parent)
{
   QPixmap bild;
   bild.load ( bilddatei );
   this->setGeometry( 0, 0, bild.width(), bild.height() );
   this->setPixmap( bild );

this->setMouseTracking(true); //move auch bei nicht gedrückter maus
                                //aber nicht über anderem objekt
//this->grabMouse();

   n_press = 0;
   n_move  = 0;
   n_over  = 0;
}


UFGBild::~UFGBild()
{
}

void UFGBild::mousePressEvent( QMouseEvent* e )
{
   qWarning("bild-press %i", n_press);
   n_press++;
}

void UFGBild::mouseMoveEvent( QMouseEvent* e )
{
   qWarning("bild-move %i", n_move);
   n_move++;
}

void UFGBild::mouseOverEvent( QMouseEvent* e )
{
   qWarning("bild-over %i", n_over);
   n_over++;
}
