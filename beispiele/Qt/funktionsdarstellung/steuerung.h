/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* steuerung.h */

#ifndef STEUERUNG_H
#define STEUERUNG_H

#include "/opt/babyDevelop/programmfenster.h"

#include <qlabel.h>
#include <qpushbutton.h>
#include <math.h>
#include "zeichenflaeche.h"

class Steuerung : public ProgrammFenster
{
   Q_OBJECT
public:
   Steuerung (); /* Konstruktor */
  ~Steuerung (); /* Destruktor  */

private:
  QLabel*         textFlaeche;
  QPushButton*    tasteEnde;
  QPushButton*    tasteCls;
  QPushButton*    tasteZeichne;
  Zeichenflaeche* meineZeichenflaeche;

private slots:
  void ende();    //Programm beenden
  void cls();     //Zeichenflaeche und Textflaeche loeschen
  void zeichne(); //Grafik zeichnen
};

#endif
