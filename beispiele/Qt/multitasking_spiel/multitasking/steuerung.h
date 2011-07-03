/* steuerung.h */

#ifndef STEUERUNG_H
#define STEUERUNG_H

#include "/opt/babyDevelop/programmfenster.h"

#include "konstanten"

#include "qmessagebox.h"
#include <qtimer.h>
#include <qdatetime.h>
#include <qpushbutton.h>

#include "bild.h"
#include "spieler.h"
#include "angreifer.h"

class Steuerung : public ProgrammFenster
{
   Q_OBJECT
public:
   Steuerung (); /* Konstruktor */
  ~Steuerung (); /* Destruktor  */

int intervall;

Bild*        spielfeld;
Angreifer*   derAngreifer[4];
Spieler*     derSpieler;
QTimer*      zeitgeber;
QTime*       startzeit;
QPushButton* tasteEnde;
QPushButton* tasteNochmal;

private: //Methoden
   int pruefeKollision(int);
   int pruefeWandberuehrung();

private slots:
   void systemtakt();
   void start();
   void ende();
   void nochmal();
};

#endif
