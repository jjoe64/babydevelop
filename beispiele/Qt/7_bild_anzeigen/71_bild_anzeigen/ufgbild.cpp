/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* ufgbild.cpp */

#include "ufgbild.h"

/* Konstruktor */
UFGBild::UFGBild(QString bilddatei, QWidget* elternobjekt) : QLabel(elternobjekt)
{
   QPixmap bild;
   bild.load( bilddatei );
   this->setGeometry( 0, 0, bild.width(), bild.height() );
   this->setPixmap( bild );
}

/* Destruktor */
UFGBild::~UFGBild()
{
}
