/*---------------*/
/* importieren.h */
/*---------------*/

#ifndef IMPORTEIREN_H
#define IMPURTIEREN_H

#include <qlabel.h>
#include <qpushbutton.h> 
#include <qgroupbox.h>
#include <qradiobutton.h>

#include <qevent.h>

#include "ufgi18n.h"

class Importieren : public QWidget
{
   Q_OBJECT
public:
   Importieren(QWidget* parent=0); // Konstruktor
  ~Importieren();                  // Destruktor

private:
   QLabel       *txtKlassenArt;
   QLabel       *txtHinweis;
   QGroupBox *gruppe_r;
   QRadioButton *klasseQt;
   QRadioButton *klasseAllgemein;

public:
   UFGi18n     *landestext;
   QPushButton *tasteOk;
   QPushButton *tasteAbbrechen;

public slots:
   int getAntwort();   // gewaehlte Option zurueckgeben

private slots:
   void keyPressEvent(QKeyEvent *e);   // virtuelle Methode

signals:
   void abbruch();
};

#endif
