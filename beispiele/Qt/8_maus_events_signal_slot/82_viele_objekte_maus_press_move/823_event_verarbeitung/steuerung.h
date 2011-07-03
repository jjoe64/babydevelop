/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* Steuerung.h */

#ifndef STEUERUNG_H
#define STEUERUNG_H

#include "/opt/babyDevelop/programmfenster.h"

#include "ufgbild.h"
#include <qevent.h> //oder auch:#include <QMouseEvent> 
#include <qlabel.h>
#include <qtimer.h>
#include <qpushbutton.h>

class Steuerung : public ProgrammFenster
{
   Q_OBJECT
public:
   Steuerung(); /* Konstruktor */
  ~Steuerung(); /* Destruktor  */

private:
   int n_move; //Anzahl move-Ereignisse
   int zeit;   //CountDown-Wert
   int maus_x; //MausPosition aus steuerung-mouseMoveEvent()
   int maus_y;
   int anzahl; //Anzahl der Bilder

private:
   QLabel*      blatt;    //CountDown anzeigen
   QTimer*      zaehler;
   QPushButton* taste;
   UFGBild*     meinBild[5];

private slots:
   void losgehts();           //Zähler für CountDown
   void abwaerts();           //CountDown anzeigen und Bild anzeigen
   void verschiebe(int, int); //MausBewegung auf Bild in steuerung verarbeiten
   void mausLoesen();         //MausKlick auf Bild in steuerung verarbeiten
   void mouseMoveEvent( QMouseEvent* );
};

#endif
