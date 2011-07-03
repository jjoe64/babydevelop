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

   n_move  = 0;
}


UFGBild::~UFGBild()
{
}

void UFGBild::mouseMoveEvent( QMouseEvent* e )
{
   qWarning("bild-move %i", n_move);
   n_move++;
   emit mausbewegung(e->x()-this->width()/2, e->y()-this->height()/2);
}

void UFGBild::mousePressEvent( QMouseEvent* e )
{
   emit mausklick();
}
