/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* fenster.cpp */

#include "fenster.h"

/* Konstruktor */
Fenster::Fenster(QWidget *parent) : ProgrammFenster(parent)
{
   this->setGeometry(300,30,150,80);
   this->setWindowTitle("rechts");

   papier = new QLabel("<center>Drueck mich.</center>",this);
   // Palette des zu manipulierenden Objekts holen
   QPalette palette = papier->palette();
   // gewünschte Werte ändern
   palette.setColor(QPalette::Background, Qt::yellow);
   // Palette setzen
   papier->setPalette(palette);
   // automatisches Repaint aktivieren
   papier->setAutoFillBackground(true);
   papier->setGeometry(20, 15, 120, 50);
   papier->show();

   this->setMouseTracking(true);   //Maus-Events auch ohne Klick
}

/* Destruktor */
Fenster::~Fenster()
{
}

void Fenster::mouseMoveEvent( QMouseEvent* e )
{
   this->hide();
   emit sichtbarmachen();
}
