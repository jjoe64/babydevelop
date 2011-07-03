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
#include <qtimer.h>
#include <math.h>
#include "bug.h"

class Steuerung : public ProgrammFenster
{
   Q_OBJECT
public:
   Steuerung(); /* Konstruktor */
  ~Steuerung(); /* Destruktor  */

private:
   BUG*         meineGrafikflaeche;
   QLabel*      textFlaeche;
   QPushButton* tasteEnde;
   QPushButton* tasteCls;
   QPushButton* tasteZeichne;
   QTimer*      timer;

private:
   double pos;

private slots:
  void ende();    //Programm beenden
  void cls();     //Zeichenflaeche und Textflaeche loeschen
  void zeichne(); //Grafik zeichnen
  void weiter();
};

#endif
