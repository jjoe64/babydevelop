/*-----------------*/
/* importieren.cpp */
/*-----------------*/

#include "importieren.h"

// Konstruktor
//-------------
Importieren::Importieren(QWidget *parent) : QWidget(parent)
{
   landestext=new UFGi18n();

   this->setFixedSize(315, 160);
   this->move(200, 200);
   this->setWindowTitle(landestext->getText("Klasse importieren..."));

   // fuer gelbe Hintergrundfarbe
   QColor farbe_gelb;
      farbe_gelb.setRgb(252, 255, 0); // yellow
   QPalette p_gelb;
      p_gelb.setColor(QPalette::Window, farbe_gelb);

   txtKlassenArt = new QLabel(landestext->getText("Welche KlassenArt soll importiert werden?"),this);
   txtKlassenArt->setGeometry(10,10,295,30);
   txtKlassenArt->setPalette(p_gelb);
   txtKlassenArt->setBackgroundRole( QPalette::Background );

   txtKlassenArt->show();

   txtHinweis = new QLabel(landestext->getText(" )* enthaelt SIGNAL-SLOT-Methoden"),this);
   txtHinweis->setGeometry(10,130,295,25);
   txtHinweis->setPalette(p_gelb);
   txtHinweis->setBackgroundRole( QPalette::Background );
   txtHinweis->show();

   gruppe_r = new QGroupBox(landestext->getText("KlassenArt"),this);
   gruppe_r->setGeometry(10,45,190,80);
   klasseQt = new QRadioButton(landestext->getText("Grafische Klasse )*"),gruppe_r);
   klasseQt->setGeometry(10,20,165,20);
   klasseQt->setPalette(p_gelb);
   klasseAllgemein = new QRadioButton(landestext->getText("Allgemeine Klasse"),gruppe_r);
   klasseAllgemein->setGeometry(10,50,165,20);
   klasseAllgemein->setPalette(p_gelb);
   gruppe_r->show();

   tasteAbbrechen = new QPushButton(landestext->getText("Abbrechen"),this);
   tasteAbbrechen->setGeometry(215,52,95,35);
   tasteAbbrechen->show();

   tasteOk = new QPushButton(landestext->getText("Ok"),this);
   tasteOk->setGeometry(215,92,95,35);
   tasteOk->show();
}


// Destruktor
//------------
Importieren::~Importieren()
{
}


// Methoden
//----------
int Importieren::getAntwort()
{
   if(klasseQt->isChecked()) //Qt-Klasse
   {
      return 1;
   }
   else if(klasseAllgemein->isChecked()) //allgemeine Klasse
   {
      return 0;
   }
   return -1;   // Fehler nix gewaehlt gewesen
}


void Importieren::keyPressEvent(QKeyEvent *e)
{
   switch ( e->key() )
   {                     // Hinweis: die Rueckgabecodes der einzelnen Tasten findet man in der "qnamespace.h"
      case Qt::Key_Escape:
         emit abbruch();
         break;
   }
}
