/* steuerung.cpp */

#include "steuerung.h"

//Globale Variablen
QString aktuellerPfad;

/* Konstruktor */
Steuerung::Steuerung () : ProgrammFenster ()
{
   this->setWindowTitle("- MP3-Player -");
   this->setFixedSize(500,403);

   aktuellerPfad = QDir::currentPath();

   dasGUI = new GUI(this);
   dasGUI->move(10,10);
   dasGUI->show();

   //Farbsteuerung ist leider etwas aufwaendig
//   QColor farbe_gelb;                         //Gelb soll es sein
//      farbe_gelb.setRgb(252,255,0);           //yellow
//      QPalette palette_gelb;                  //Bestimmt die Behandlung z.B. Aufhellen beim Ueberfahren mit der Maus
//      palette_gelb.setColor(QPalette::Window, farbe_gelb);
//this->setAutoFillBackground(true); //Hintergrund automatisch zeichnen, wenn notwendig
//   dasGUI->setPalette(palette_gelb);

   connect( dasGUI, SIGNAL( finde(QString) )    ,SLOT( uebergibText(QString) ) );
   connect( dasGUI, SIGNAL( ladeLied(QString) ) ,SLOT( spieleLied(QString) ) );
   connect( dasGUI, SIGNAL( sigEnde() )         ,SLOT( beende() ) );
}

/* Destruktor */
Steuerung::~Steuerung ()
{
   delete dieSuche;
   delete dasGUI;
   delete dasSpielen;
}


void Steuerung::uebergibText( QString begriff )
{
   dieSuche = new Suchen( begriff );
   dasGUI->ladeListe();
}


void Steuerung::spieleLied( QString lied )
{
   qWarning("lied = %s",lied.toLatin1().data());
   dasSpielen = new Spielen( lied );
}


void Steuerung::beende()
{
   QString befehl="rm -f "+aktuellerPfad+"/liste.txt";
   system(befehl.toLatin1().data());
   qWarning("Abgesetzer Befehl = %s",befehl.toLatin1().data());
   exit(0);
}
