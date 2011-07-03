/*-----------------*/
/* einstellungen.h */
/*-----------------*/

#ifndef EINSTELLUNGEN_H
#define EINSTELLUNGEN_H

#include <QWidget>
#include <QCloseEvent>

#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qgroupbox.h>
#include <qfile.h>

#include "ufgi18n.h"

class Einstellungen : public QWidget
{
   Q_OBJECT
public:
   Einstellungen(QWidget* parent=0); // Konstruktor
  ~Einstellungen();                  // Destruktor

private slots:
   void closeEvent(QCloseEvent *event);   // nicht auf [X] reagieren

public:
   UFGi18n     *landestext;
   // Rahmen um die einzelnen Bereiche
   QGroupBox *rahmenBdp;
   QGroupBox *rahmenProjekt;
   QGroupBox *rahmenTasten;

   // Einstellungen fuer Babydevelop
   QLabel *txtFensterStartGroesse;
      QLabel *txtX0F;
      QLabel *txtY0F;
      QLabel *txtBreiteF;
      QLabel *txtHoeheF;
      QLineEdit *x0F;
      QLineEdit *y0F;
      QLineEdit *breiteF;
      QLineEdit *hoeheF;
   QLabel *txtMeldungsFensterStartGroesse;
      QLabel *txtX0MF;
      QLabel *txtY0MF;
      QLabel *txtBreiteMF;
      QLabel *txtHoeheMF;
      QLineEdit *x0MF;
      QLineEdit *y0MF;
      QLineEdit *breiteMF;
      QLineEdit *hoeheMF;
   QLabel *txtSchriftArt;
   QLineEdit *schriftArtFeld;
   QLabel *txtbdpInstallationsVerzeichnis;
   QLineEdit *bdpInstallationsVerzeichnis;
   QLabel *txtBrowserBefehl;
   QLineEdit *browserFeld;
   QLabel *txtQtHilfePfadDatei;
   QLineEdit *qtHilfePfadDateiFeld;
   QLabel *txtBetriebssystem;
   QLineEdit *betriebssystemFeld;
   QLabel *txtQtDir;
   QLineEdit *qtDir;
   QLabel *txtQtLib;
   QLineEdit *qtLib;
   QLabel *txtBdpLibs;
   QLineEdit *bdpLibs;
   QLabel *txtMocDir;
   QLineEdit *mocDir;
   QLabel *txtSyntaxHighlighting;
   QLineEdit *syntaxHighlightingFeld;
   QPushButton *schalterSH;
   QLabel *txtAutoSpeichern;
   QLineEdit *autoSpeichernFeld;
   QPushButton *schalterAS;
   QPushButton *schalterEsc;

   // Einstellungen fuer das Projekt
   QLabel    *txtCompilerFlags;
   QLineEdit *compilerFlagsFeld;
   QLabel    *txtLinkerFlags;
   QLineEdit *linkerFlagsFeld;

   QLabel    *txtEscape;
   QLineEdit *escapeFeld;

   // Tasten
   QPushButton *tasteAbbrechen;
   QPushButton *tasteSpeichern;
   QPushButton *tasteEsc;

private slots:
   void wechselnSH();   // SyntaxHighlighting
   void wechselnAS();   // autoSpeichern
   void wechselnEsc();  // Escape

public slots:
   void setNoProjekt(int);
};

#endif
