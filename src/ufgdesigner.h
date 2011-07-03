/*---------------*/
/* ufgdesigner.h */
/*---------------*/

/*--------------------------------------------------*/
/* Der ufg-Designer ist eine Zeichenflaeche auf der */
/* GUI-Objekte plaziert werden.                     */
/* Moegliche GUI-Objekte: - QPushButton             */
/*                        - QLabel                  */
/*                        - QLineEdit               */
/*                        - BLed                    */
/*--------------------------------------------------*/

#ifndef UFGDESIGNER_H
#define UFGDESIGNER_H

#include <QWidget>
#include <QPushButton>
#include <QEvent>
#include <QCloseEvent>
#include <QTimer>
#include <QFile>
#include <QMessageBox>

#include "ufgbasis.h"   //???
#include "ufgpushbutton.h"
#include "ufglineedit.h"
#include "ufglabel.h"
#include "ufgled.h"

#include "ufgi18n.h"

const int maxObjekte = 25;

class UFGdesigner : public QWidget
{
   Q_OBJECT
public:
          UFGdesigner(QWidget* parent=0); // Konstruktor
 virtual ~UFGdesigner();                  // Destruktor

public: //da koennte man mal ein paar auf private: setzen
   UFGi18n     *landestext;

   QWidget *werkzeug;                    // Werkzeugkasten fuer Widgets
      QPushButton *tasteEsc;             // Esc-Taste
      QPushButton *tasteLabel;           // QLabel-Widget
         QLineEdit* nameLabel;
      QPushButton *tasteLineEdit;        // QLineEdit-Widget
         QLineEdit* nameLineEdit;
      QPushButton *tastePushButton;      // QPushButton-Widget
         QLineEdit* namePushButton;
      QPushButton *tasteLed;             // BLed-Widget
         QLineEdit* nameLed;

      QPushButton *tasteBeenden;
      QPushButton *tasteAbbrechen;

      QPushButton *tasteLoeschen;
         BLed        *timerled;
         QTimer      *timer;

//   QWidget** objekt;       //array dynamisch
   QWidget* objekt[maxObjekte];       // array statisch
   QString  objektName[maxObjekte];   // Objektname z.B. tasteEnde
   QString  objektText[maxObjekte];   // Objekttext z.B. Ende
   int      objektTyp[maxObjekte];    // ObjektTyp 1=QLabel, 2=QPushButton, 3=QLineEdit, 4=BLed
   QString  objektFarbe[maxObjekte];  // Objektfarbe z.B. von QLabel
   int nummer;          // Nummer des zu bearbeitenden Objekts
                        // zeigt immer auf das letzte im Array
                        // wird um 1 erhoeht, wenn neues Objekt erzeugt wird
   int wunschobjekt;    // 0=nix gewaehlt 1=QLabel
                        //                2=QPushButton
                        //                3=QLineEdit
                        //                4=BLed
   int anzahlObjekte;
   int editObjekt; //Objekt welches gerade editiert wird
   int zustand;   // nix oder move oder groesse veraendern

   QPoint pos0, pos1, pos2;

private:
   int rasten(int);

private:
protected:
   void closeEvent( QCloseEvent *e );     // wird benoetigt um Klick auf [X] abzufangen

public slots:
   void mousePressEvent( QMouseEvent* );
   void mouseReleaseEvent( QMouseEvent* );
   void mouseMoveEvent( QMouseEvent* );

   int fuellen(QString); // GUI mit den bereits vorhandenen Objekten fuellen
   QString farbe(int);

   void esc();
   void lineEdit();
   void pushButton();
   void label();
   void led();
   void loeschen();
   void takt();

   void signalauswertung(int);
   int  getAnzahlObjekte();
   int  getObjektTyp(int);
   QString getName(int);
   QString getObjektText(int);
};

#endif
