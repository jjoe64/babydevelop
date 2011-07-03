/*---------------*/
/* babydevelop.h */
/*---------------*/

#ifndef _BABYDEVELOP_H_
#define _BABYDEVELOP_H_

#include <QApplication>
#include <QMainWindow>
#include <QLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QMenuBar>
#include <QStatusBar>
#include <QCloseEvent>

//fuer tabulatoren
#include <QtGui>
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QTabWidget>

#include <qtextedit.h>
#include <qplaintextedit.h>
#include <QTextCursor>
#include <qfileinfo.h>

//----------------------------------------------------------
// made from Marcel
#include <qtimer.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <stdarg.h>

#include "arbeiter.h"
#include "ufgi18n.h"
#include "eingabe_1.h"
#include "importieren.h"
#include "einstellungen.h"
#include "ufgdesigner.h"
#include "debugger.h"
#include "codeeditor.h"

const int maxKlassen=19;   // (normal reichen 19 für den Unterricht üppig) maximale Anzahl von Klassen (global)

class BabyDevelop : public QMainWindow
{
//---------------------------------------------------------------------------------------
//    .------------------------------------------------. ::QMainWindow
//    |    menuBar()                                   |
//    |------------------------------------------------|
//    |      mitte     this->setCentralWidget(mitte);  |
//    |------------------------------------------------|
//    |   statusBar()                                  |
//    '------------------------------------------------'
//---------------------------------------------------------------------------------------
   Q_OBJECT
public:
   BabyDevelop();
  ~BabyDevelop();

//--------------------------------
// Member, Variablen
//--------------------------------

// Startparameter
//--------------------------------
private:
   QString version;
   QString fd;  // fd = filedialog; wg. Startparameter auswerten nötig geworden

   int nKlassen;                     // erste eigene Klasse = Nr. 1
   QString klassenName[maxKlassen];  // ohne Zahl geht nicht
   int klassenArt[maxKlassen];       // 0=allgemeine Klasse
                                     // 1=Qt-Klasse
   QString kName;           // für Importfunktion
   int kArt;          // für Importfunktion
   int projektTyp;          // 1=C, 2=C++, 3=C++/Qt, 0 gibts nicht
   QString  lastReiterText; // um [...] der Reiter zu steuern
   int lastReiterObjektNr;  // "         "       "      "

   // fuer Einstellungen-[Abbrechen]
   //--------------------------------
   int zeilenumbruch_tmp;
   int autoSpeichern_tmp;
   int escape_tmp;
   QString compilerFlags_tmp;
   QString linkerFlags_tmp;
   QString browserBefehl_tmp;


//---Menuestrukturen--------------------------------
private:
     QMenu* menuProjekt;
        QMenu* mpNeu;
           QAction* umpnC;
           QAction* umpnCpp;
           QAction* umpnQt;
        QAction* mpOeffnen;
        QAction* mpSpeichern;
        QAction* mpSpeichernUnter;
        QAction* mpDateiSpeichern;
        QAction* mpSchliessen;
        QAction* mpBeenden;

     QMenu* menuBearbeiten;
        QAction* mbRundschlag;
        QAction* mbKompilieren;
        QAction* mbLinken;
        QAction* mbAusfuehren;
        QAction* mbAlleKompilieren;
        QAction* mbNeuerPrototyp;
        QAction* mbNeueAllgemeineKlasse;
        QAction* mbNeueGrafischeKlasse;
        QAction* mbPrototypImportieren;
        QAction* mbKlasseImportieren;
        QAction* mbPrototypLoeschen;
        QAction* mbKlasseLoeschen;
        QAction* mbEinstellungen;

     QMenu *menuInfo;
        QAction* miUeberBabyDevelop;
        QAction* miEinfuehrung;
        QAction* miProjekteigenschaften;
        QAction* miToDo;

     QMenu *menuHilfe;
        QAction* mhBabyCHilfe;
        QAction* mhBabyCppHilfe;
        QAction* mhBabyQtHilfe;
        QAction* mhQtHilfe;
        QAction* mhFAQ;
        QAction* mhMeldungsfenster;
        QAction* mhGUIDesigner;
        QAction* mhDebugger;

   //-------------------------------------
   QWidget* tabulator[maxKlassen*2+3];   //da ist das Widget für das Programmlisting drin

   //Qt4-Varianten ohne/mit BEdit -------------------------------------------------------------
   //QTextEdit*   listing[maxKlassen*2+3];     //BEdit=QTextEdit  Programmlisting
   //BEdit*       listing[maxKlassen*2+3];     //BEdit=QTextEdit  Programmlisting
   CodeEditor* listing[maxKlassen*2+3];     // BEdit=QTextEdit Programmlisting -> CodeEditor
   //------------------------------------------------------------------------------------------

   QHBoxLayout* listingBox;        //qt3=grid
   QTabWidget*  tabulatorRahmen;   //Reitertext
   int nListings;   // listing[1] fuer main.cpp
                    // gerade Nummern fuer cpp-Datei
                    // ungerade Nummern fuer h-Datei
                    // listing[2] ist BasisKlasse.cpp
                    // listing[3] ist BasisKlasse.h
                    // listing[4] ist die erste eigene Klasse.cpp
   QFont listingfont;      // Schriftart

   // fuer Listing markieren
   QTextCharFormat format_original; // aktuelles Format, fuer markierte Fehlerzeile zuruecknehmen
   int fehler_start_pos;            // Startposition des Markierten Textes
   int fehler_ende_pos;             // Endeposition des Markierten Textes
   int fehleranzeige;               // 0=aus, 1=ein
   int fehler_reiter;
   // fuer Zeilennummer markieren
   int znr_fehler_start_pos;            // Startposition des Markierten Textes
   int znr_fehler_ende_pos;             // Endeposition des Markierten Textes
   int znr_fehler_reiter;

   //------------------------------------------------
   QWidget     *mitte;
   QHBoxLayout *layoutMitte;

//remember: Eine Klasse die escape-Sequenzen anzeigen kann nehmen
//   QTextEdit     *meldungsFenster; // Fuer Kompiler-/Linker-Meldungen
   QPlainTextEdit     *meldungsFenster; // Fuer Kompiler-/Linker-Meldungen
   Eingabe_1     *eingabeZeile;    // einzeilige Eingabe mit [Ok] und [Abbrechen]
   Importieren   *importFenster;
   Einstellungen *einstellungenFenster;

   UFGi18n       *landestext;
   UFGdesigner   *designer;
   Debugger      *debugger;
   int statusDebugger;          // 0=aus, 1=aktiv

   QString projektName;
   QString projektVerzeichnis;

   // Fuer Fehlerbehandlung
   int rueckgabeWert;

   QTimer *timer_ausgabe;
   CArbeiter *arbeiter;


//-------------------------------------------------
// Methoden
//-------------------------------------------------

private slots:              // Projekt-Menu
   void neuesProjektCErstellen();       // wird von neuesProjektC aufgerufen
   void neuesProjektCPPErstellen();     // wird von neuesProjektCPP aufgerufen
   void neuesProjektQtErstellen();      // usw.

public slots:
      void oeffnen(QString);
         void oeffnenJetzt();
private slots:
         void oeffnen();
      void speichern();
      void speichernUnter();
         void speichereListings();
         void speichereScripte();
      void speichernDatei();
      void schliessen();
      void beenden();
         void loescheDateien();
   void rundschlag();       // Bearbeiten-Menue
      void kompilieren();
      void linken();
      void ausfuehren();
      void kompilieren_alle();
      void neuPrototyp();
         void neuPrototypOk();
         void neuPrototypAbbrechen();
      void neueKlasse();
         void neueKlasseOk();
         void neueKlasseAbbrechen();
      void neueQtKlasse();
         void neueQtKlasseOk();
         void neueQtKlasseAbbrechen();
      void prototypImportieren();
      void klasseImportieren();
         void importKlasseOk();
         void importKlasseAbbrechen();
         void importKlassennameOk();
         void importKlassennameAbbrechen();
      void loeschenPrototyp();
      void loeschenKlasse();
      void einstellungen();
         void einstellungenSpeichern();
         void einstellungenAbbrechen();
   void ueberBabyDevelop();   // Info-Menue
      void einfuehrung();
      void projekteigenschaften();
      void todo();
   void babyCHilfe();         // Hilfe-Menue
      void babyCppHilfe();
      void babyQtHilfe();
      void qtHilfe();
      void babyFAQ();
      void darstellung();           // alle Fenster neu aufbauen
      void meldungsfensterEinAus(); // Meldungsfenster Sichtbarkeit umschalten
      void startDesigner();
         void designerAbbrechen();
         int  designerBeenden();
         void loescheDesigner();
      void startDebugger();
         void debuggerBeenden();
			void zeileMarkieren(QString,QString);


   //-------------------------------------------------------------------------------
   void ausgabeTimeout();
   // Anzeigen der ZeilenNummer der aktiven Zeile
   void zeileAnzeigen(void);     // fuer Maus-Klick
   void meldung_doppelklick();   // fuer Sprung zum Fehler
   //-------------------------------------------------------------------------------

   void reiterHervorheben(int);
   void loescheEingabeZeile();
   void loescheImportFenster();

private: // Methoden
   int  forken(int);                  // Forken
   void ladeRCFile();                 // RC-Dateien laden
   void ladeUserRCFile();             // User-RC-Dateien laden
   void schreibeRCFile(QString);      // RC-Dateien schreiben
   int  ladeTexte();                  // laenderspezifische Texte laden
   int  script(QString);              // Scripte schreiben
   int  Makefile();
   void bildeStruktur(QString);       // Tabulator-Strukturen bilden
   void deleteAll();                  // Strukturen loeschen, zuruecksetzen bei Neu und Oeffnen
   int  pruefeNameVorhanden(QString); // ueberpruefen ob Name schon vorhanden ist
   void closeEvent(QCloseEvent *e);   // wird benoetigt um Klick auf [X] abzufangen
   void schreibeMeldungsfenster(QString);
   int  pruefeProjektName(QString);
   int  pruefeVerzeichnisName(QString);
};

#endif

