/* steuerung.cpp */

#include "steuerung.h"

/* Konstruktor */
Steuerung::Steuerung() : ProgrammFenster()
{
   this->setGeometry(10, 10, 250, 230);

   // Hintergrund des Programmfensters gruen machen
   // Palette des zu manipulierenden Objekts holen
   QPalette paletteP = this->palette();
   // gewünschte Werte ändern
   paletteP.setColor(QPalette::Background, Qt::green);
   // Palette setzen
   this->setPalette(paletteP);
   // automatisches Repaint aktivieren
   this->setAutoFillBackground(true);

   // Ein Bild wird als Zeichenflaeche benutzt
   QPixmap zeichenflaeche("tux.png"); 

   // Zwei Linien durch das Bild malen
   // QPainter zum Linien malen
   QPainter p(&zeichenflaeche);
   // 1. Linie
   QPen pen = p.pen();
   pen.setWidth(4);
   pen.setColor(Qt::magenta);
   //pen.setStyle(Qt::SolidLine);
   pen.setStyle(Qt::DashLine);
   p.setPen(pen);
   // coole Funktionen gibt's :)
   // Das Bild hat 75x75 Pixel
   p.drawLine( QLine(zeichenflaeche.rect().topLeft(), zeichenflaeche.rect().bottomRight()) );

   // 2. Linie
   pen.setWidth(0); //0=1 aber schnell
   pen.setColor(Qt::red);
   pen.setStyle(Qt::SolidLine);
   p.setPen(pen);
   // Beachte: Es wird nur auf dem Pixmap gezeichnet
   p.drawLine(0, 0, 150, 50);
   p.end(); 

   // 
   container = new QLabel(this);
   container->setGeometry(10, 10, 180, 130);

   // Hintergrund des Containers gelb machen
   // Palette des zu manipulierenden Objekts holen
   QPalette palette = container->palette();
   // gewünschte Werte ändern
   palette.setColor(QPalette::Background, Qt::yellow);
   // Palette setzen
   container->setPalette(palette);
   // automatisches Repaint aktivieren
   container->setAutoFillBackground(true);

   // Bild anzeigen
   container->setPixmap(zeichenflaeche);
   container->move(50, 30);
   container->show();

   taste = new QPushButton("Jetzt anpassen", this);
   taste->setGeometry(10, 180, 110, 30);
   taste->show();
   connect(taste, SIGNAL( clicked() ), SLOT( anpassen() ) );
}

/* Destruktor */
Steuerung::~Steuerung()
{
}

void Steuerung::anpassen()
{
   container->adjustSize(); // container auf Bildgroesse anpassen
}
