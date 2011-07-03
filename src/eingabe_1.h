/*-------------*/
/* eingabe_1.h */
/*-------------*/

#ifndef EINGABE_1_H
#define EINGABE_1_H

#include <qlabel.h>
#include <qpushbutton.h> 
#include <qlineedit.h>
#include <qstring.h>
#include <qevent.h>

#include "ufgi18n.h"

class Eingabe_1 : public QWidget
{
   Q_OBJECT
public:
   Eingabe_1(QWidget* elternObjekt=0, int projektTyp=0); // Konstruktor erweitert wegen ufg_i18n
  ~Eingabe_1();                                    // Destruktor

private:
   UFGi18n *landestext;
   QString  antwort;          // eingegebener Text
   QLabel  *txtKlassenName;

public:
   QLineEdit   *klassenName;
   QPushButton *tasteOk;
   QPushButton *tasteAbbrechen;

public slots:
   QString gibText();       // eingegebener Text
   void setzeText(QString); // Vorgabetext

private slots:
   void keyPressEvent(QKeyEvent *e);   // virtuelle Methode

signals:
   void abbruch();
};

#endif
