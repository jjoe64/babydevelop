/* gui.cpp */

#include "gui.h"

//Globale Variablen
extern QString aktuellerPfad;

/* Konstruktor */
GUI::GUI (QWidget *elternWidget) : QWidget (elternWidget)
{
   this->setGeometry(0,0,480,383);

   //Farbsteuerung ist leider etwas aufwaendig
   QColor farbe_gelb;                         // Gelb soll es sein
      farbe_gelb.setRgb(252,255,0);           // yellow
      QPalette palette_gelb;                  // Bestimmt die Behandlung z.B. Aufhellen beim Ueberfahren mit der Maus
      palette_gelb.setColor(QPalette::Window, farbe_gelb);
   this->setAutoFillBackground(true);         // Hintergrund automatisch zeichnen, wenn notwendig
   this->setPalette(palette_gelb);

   copy = new QLabel("(c) by ufg, Jorgito Alvarado and Jonas",this);
   copy->setGeometry(240, 360, 238, 20);
   copy->setPalette(Qt::green);         // Hintergrundfarbe
   copy->setAutoFillBackground(true);   // Hintergrundfarbe automatisch zeichnen, wenn notwendig
   copy->setAlignment(Qt::AlignCenter); // Zentrierte Anordnung
   copy->show();

   zeile = new QLineEdit("", this);
   zeile->setGeometry(10, 10, 230, 30);
   zeile->show();
   connect(zeile, SIGNAL( returnPressed() ), SLOT(nimmText() ) );

   tasteFinde = new QPushButton("Finde",this);
   tasteFinde->setGeometry(10, 50, 70, 30);
   tasteFinde->show();
   connect(tasteFinde, SIGNAL( clicked() ), SLOT(nimmText() ) );

   tasteInfo = new QPushButton("Info",this);
   tasteInfo->setGeometry(90, 50, 70, 30);
   tasteInfo->show();
   connect(tasteInfo, SIGNAL( clicked() ), SLOT(informieren() ) );

   tastePlay = new QPushButton("Play",this);
   tastePlay->setGeometry(170, 50, 70, 30);
   tastePlay->show();
   connect(tastePlay, SIGNAL( clicked() ), SLOT(spiele() ) );

   tasteEnde = new QPushButton("Ende",this);
   tasteEnde->setGeometry(10, 345, 70, 30);
   tasteEnde->show();
   connect(tasteEnde, SIGNAL( clicked() ), SLOT(ende() ) );

   tabelle = new QListWidget(this);
   tabelle->setGeometry(10, 95, 460, 240);
   tabelle->show();
   connect(tabelle, SIGNAL( itemDoubleClicked(QListWidgetItem*) ),SLOT(auswahlLied(QListWidgetItem*)));
}


/* Destruktor */
GUI::~GUI ()
{
}


void GUI::ladeListe()
{
   tabelle->clear();
   //Anmerkung: Mit QTextStream geht es nicht, da das Teil bei Zeilenende
   //           meint es sei das Dateiende - scheiß Qt
   QFile liste( aktuellerPfad+"/liste.txt" );
   liste.open(QIODevice::ReadOnly);
   QString zeile;
   int nZeile=0;
   while( (zeile = liste.readLine()) != NULL)
   {
qWarning("aktpfad=%s",aktuellerPfad.toLatin1().data());
      zeile.chop(1); //Zeiche \n entfernen
      pfad[nZeile] = zeile;
      QString lied = zeile.remove(0,zeile.lastIndexOf("/")+1);
      tabelle->insertItem(nZeile,lied);
      nZeile++;
   }
   liste.close();
}


void GUI::auswahlLied(QListWidgetItem* lied)
{
   //QListWidgetItem* lied wird nicht benoetigt, wird aber vom Signal geliefert
   int liedNr = tabelle->currentRow();
   emit ladeLied(pfad[liedNr]);
}


void GUI::spiele()
{
   int liedNr = tabelle->currentRow();
   emit ladeLied(pfad[liedNr]);
}


void GUI::nimmText()
{
   QString begriff = zeile->text();
   emit finde(begriff);
}


void GUI::informieren()
{
   QMessageBox::information(this,"Information","Es muss der XMMS-Player installiert sein!\n"
                                               "Geben Sie einen Teil des Suchbegriffs ein und druecken\n"
                                               "Sie [Enter] oder klicken Sie auf die [Finde]-Taste.\n"
                                               "Suchen Sie Ihr Lied aus der Liste aus und\n"
                                               "doppelklicken Sie darauf.\n"
                                               "Nun sollte das gewuenschte Lied abgespielt werden.\n"
                                               "Beenden Sie das Programm mit der [Ende]-Taste.");
}


void GUI::ende()
{
  emit sigEnde();
}
