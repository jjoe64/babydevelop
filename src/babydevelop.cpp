/*-----------------*/
/* babydevelop.cpp */
/*-----------------*/

#include "babydevelop.h"

QString laenderkuerzel;
QString bdpInstallVerzeichnis;
QString schriftArt;
QString linkerFlags;
QString compilerFlags;
QString browserBefehl;
QString qtHilfePfadDatei;
QString QtLib;
QString Libs;
QString QtDir;
QString MocDir;

int x0mf, y0mf, xmf, ymf;
int x0bd, y0bd, xbd, ybd;

int escape;
int autoSpeichern;
int zeilenumbruch;

#include <QMessageBox>
#include <QRegExp>
#include <QSpacerItem>

BabyDevelop::BabyDevelop() : QMainWindow()
{
   //Startparameter für Linux/Windows
   version = "10.4.0-alfa-s-";
#if defined(LINUX)
   version += "Linux";
   bdpInstallVerzeichnis="/opt";
#elif defined(WIN32)
   version += "Win32";
   bdpInstallVerzeichnis = "C:/opt";
#endif

   nListings      = 1; // 0 als Startwert geht nicht (qt3)
   nKlassen       = 0;
   projektTyp     = 0; // Startwert=0=nix: ab bdp-6 0=kein Projekt geladen
   escape         = 0; // Startwert=Keine Escape-Sequenzen
   statusDebugger = 0; //

   //Konfigurationen laden
   this->ladeRCFile();
   this->ladeUserRCFile();

   //Pointer auf Arbeiterklasse
   this->arbeiter = new CArbeiter();

   //sprachspezifische Texte einstellen
   landestext=new UFGi18n();

   //erzeuge Meldungsfenster
   meldungsFenster=new QPlainTextEdit("", this);
   connect(this->meldungsFenster, SIGNAL(selectionChanged()), this, SLOT(meldung_doppelklick()));

   //hauptfenster
   this->setWindowIcon(QIcon(bdpInstallVerzeichnis+"/babyDevelop/babydevelop-icon.png"));
   this->setWindowTitle("BabyDevelop " + version + " - (c)ufg anD thE freE worlD");
   this->setGeometry(x0bd, y0bd, xbd, ybd);

   //...
   compilerFlags = "";
   linkerFlags   = "";


   //-------------------
   // Menuestrukturen
   //-------------------

   //--------------------------------------------------
   // Menue Projekt
   //--------------------------------------------------
   menuProjekt = new QMenu();
//???   menuProjekt->setAttribute(Qt::iconVisibleInMenu);
      // Untermenue Projekt-Neu
      //------------------------
      mpNeu = new QMenu();
         umpnC = new QAction(QIcon(bdpInstallVerzeichnis+"/babyDevelop/bilder/c.xpm"), "C...", this);
         umpnC->setIconVisibleInMenu(true);
         umpnC->setStatusTip(landestext->getText("Ein Konsole-C-Projekt erstellen."));
         connect(umpnC, SIGNAL(triggered()), this, SLOT(neuesProjektCErstellen()));

         umpnCpp = new QAction(QIcon(bdpInstallVerzeichnis+"/babyDevelop/bilder/c++.xpm"), "C++...", this);
         umpnCpp->setIconVisibleInMenu(true);
         umpnCpp->setStatusTip(landestext->getText("Ein Konsole-C++-Projekt erstellen."));
         connect(umpnCpp, SIGNAL(triggered()), this, SLOT(neuesProjektCPPErstellen()));

         umpnQt = new QAction(QIcon(bdpInstallVerzeichnis+"/babyDevelop/bilder/neu_qt.xpm"), "Qt...", this);
         umpnQt->setIconVisibleInMenu(true);
         umpnQt->setStatusTip(landestext->getText("Ein grafisches Qt-Projekt erstellen."));
         connect(umpnQt, SIGNAL(triggered()), this, SLOT(neuesProjektQtErstellen()));

      mpNeu = menuProjekt->addMenu(QIcon(bdpInstallVerzeichnis+"/babyDevelop/bilder/projekt_neu_mini.xpm"), "&"+landestext->getText("Neu..."));
      mpNeu->setIcon(QIcon(bdpInstallVerzeichnis+"/babyDevelop/bilder/projekt_neu_mini.xpm"));
      mpNeu->addAction(umpnC);
      mpNeu->addAction(umpnCpp);
      mpNeu->addAction(umpnQt);


      // Untermenue Oeffnen
      //--------------------
      mpOeffnen = new QAction(QIcon(bdpInstallVerzeichnis+"/babyDevelop/bilder/projekt_oeffnen_mini.xpm"), "&"+landestext->getText("Oeffnen..."), this);
      mpOeffnen->setShortcut(QString("Ctrl+O"));
      mpOeffnen->setIconVisibleInMenu(true);
      mpOeffnen->setStatusTip(landestext->getText("Ein vorhandenes Projekt oeffnen."));
      connect(mpOeffnen, SIGNAL(triggered()), this, SLOT(oeffnen()));

      // Untermenue Speichern
      //----------------------
      mpSpeichern = new QAction(QIcon(bdpInstallVerzeichnis+"/babyDevelop/bilder/projekt_speichern_mini.xpm"), "&"+landestext->getText("Speichern"), this);
      mpSpeichern->setShortcut(QString("Ctrl+P"));
      mpSpeichern->setIconVisibleInMenu(true);
      mpSpeichern->setStatusTip(landestext->getText("Alle Projektdateien speichern."));
      connect(mpSpeichern, SIGNAL(triggered()), this, SLOT(speichern()));

      // Untermenue Speichern unter
      //----------------------------
      mpSpeichernUnter = new QAction(QIcon(bdpInstallVerzeichnis+"/babyDevelop/bilder/projekt_speichern_unter_mini.xpm"), landestext->getText("Speichern unter..."), this);
      mpSpeichernUnter->setIconVisibleInMenu(true);
      mpSpeichernUnter->setStatusTip(landestext->getText("Das Projekt in einem anderen Verzeichnis speichern."));
      connect(mpSpeichernUnter, SIGNAL(triggered()), this, SLOT(speichernUnter()));

      // Untermenue Datei speichern
      //----------------------------
      mpDateiSpeichern = new QAction(QIcon(bdpInstallVerzeichnis+"/babyDevelop/bilder/projekt_datei_speichern_mini.xpm"), "&"+landestext->getText("Datei speichern"), this);
      mpDateiSpeichern->setShortcut(QString("Ctrl+S"));
      mpDateiSpeichern->setIconVisibleInMenu(true);
      mpDateiSpeichern->setStatusTip(landestext->getText("Die aktive Datei speichern."));
      connect(mpSpeichern, SIGNAL(triggered()), this, SLOT(speichernDatei()));

      // Untermenue schliessen
      //-----------------------
      mpSchliessen = new QAction(QIcon(bdpInstallVerzeichnis+"/babyDevelop/bilder/projekt_schliessen_mini.xpm"), landestext->getText("Schliessen"), this);
      mpSchliessen->setStatusTip(landestext->getText("Das Projekt schliessen."));
      mpSchliessen->setIconVisibleInMenu(true);
      connect(mpSchliessen, SIGNAL(triggered()), this, SLOT(schliessen()));

      // Untermenue beenden
      //--------------------
      mpBeenden = new QAction(QIcon(bdpInstallVerzeichnis+"/babyDevelop/bilder/projekt_beenden_mini.xpm"), "&"+landestext->getText("Beenden"), this);
      mpBeenden->setShortcut(QString("Ctrl+Q"));
      mpBeenden->setIconVisibleInMenu(true);
      mpBeenden->setStatusTip(landestext->getText("Das liebe BabyDevelop beenden :-("));
      connect(mpBeenden, SIGNAL(triggered()), this, SLOT(beenden()));


   // Projekt-Untermenues einfuegen
   //-------------------------------------------------------
   menuProjekt = this->menuBar()->addMenu("&"+landestext->getText("Projekt"));
   menuProjekt->addMenu(mpNeu);
      menuProjekt->addSeparator();
   menuProjekt->addAction(mpOeffnen);
      menuProjekt->addSeparator();
   menuProjekt->addAction(mpSpeichern);
   menuProjekt->addAction(mpSpeichernUnter);
   menuProjekt->addAction(mpDateiSpeichern);
      menuProjekt->addSeparator();
   menuProjekt->addAction(mpSchliessen);
   menuProjekt->addAction(mpBeenden);


   //-----------------------------------------------------
   // Menue Bearbeiten
   //-----------------------------------------------------
   menuBearbeiten = new QMenu();
      // Untermenu Rundschlag
      //----------------------
      mbRundschlag = new QAction(QIcon(bdpInstallVerzeichnis+"/babyDevelop/bilder/rundschlag_mini.xpm"), "&"+landestext->getText("Rundschlag"), this);
      mbRundschlag->setShortcut(QString("Ctrl+U"));
      mbRundschlag->setIconVisibleInMenu(true);
      mbRundschlag->setStatusTip(landestext->getText("Das komplettes Projekt kompilieren und linken."));
      connect(mbRundschlag, SIGNAL(triggered()), this, SLOT(rundschlag()));

      // Untermenu Kompilieren
      //-----------------------
      mbKompilieren = new QAction(QIcon(bdpInstallVerzeichnis+"/babyDevelop/bilder/kompilieren_mini.xpm"), "&"+landestext->getText("Kompilieren"), this);
      mbKompilieren->setShortcut(QString("Ctrl+K"));
      mbKompilieren->setIconVisibleInMenu(true);
      mbKompilieren->setStatusTip(landestext->getText("Nur die aktive Datei kompilieren."));
      connect(mbKompilieren, SIGNAL(triggered()), this, SLOT(kompilieren()));

      // Untermenu Linken
      //------------------
      mbLinken = new QAction(QIcon(bdpInstallVerzeichnis+"/babyDevelop/bilder/linken_mini.xpm"), "&"+landestext->getText("Linken"), this);
      mbLinken->setShortcut(QString("Ctrl+L"));
      mbLinken->setIconVisibleInMenu(true);
      mbLinken->setStatusTip(landestext->getText("Die Objektdateien zusammenlinken."));
      connect(mbLinken, SIGNAL(triggered()), this, SLOT(linken()));

      // Untermenu Ausfuehren
      //----------------------
      mbAusfuehren = new QAction(QIcon(bdpInstallVerzeichnis+"/babyDevelop/bilder/ausfuehren_mini.xpm"), "&"+landestext->getText("Ausfuehren"), this);
      mbAusfuehren->setShortcut(QString("Ctrl+R"));
      mbAusfuehren->setIconVisibleInMenu(true);
      mbAusfuehren->setStatusTip(landestext->getText("Das Projekt ausfuehren."));
      connect(mbAusfuehren, SIGNAL(triggered()), this, SLOT(ausfuehren()));

      // Untermenu Alle Kompilieren
      //----------------------------
      mbAlleKompilieren = new QAction(QIcon(bdpInstallVerzeichnis+"/babyDevelop/bilder/kompilieren_alle_mini.xpm"), landestext->getText("Alle kompilieren"), this);
      mbAlleKompilieren->setIconVisibleInMenu(true);
      mbAlleKompilieren->setStatusTip(landestext->getText("Alle Dateien kompilieren."));
      connect(mbAlleKompilieren, SIGNAL(triggered()), this, SLOT(kompilieren_alle()));

      // Untermenu Neuer Prototyp
      //--------------------------
      mbNeuerPrototyp = new QAction(QIcon(bdpInstallVerzeichnis+"/babyDevelop/bilder/neu_prototyp_mini.xpm"), landestext->getText("Neuer Prototyp..."), this);
      mbNeuerPrototyp->setIconVisibleInMenu(true);
      mbNeuerPrototyp->setStatusTip(landestext->getText("Einen neuen Prototyp anlegen."));
      connect(mbNeuerPrototyp, SIGNAL(triggered()), this, SLOT(neuPrototyp()));

      // Untermenu Neue allgemeine Klasse
      //----------------------------------
      mbNeueAllgemeineKlasse = new QAction(QIcon(bdpInstallVerzeichnis+"/babyDevelop/bilder/neu_klasse_allgemein_mini.xpm"), landestext->getText("Neue allgemeine Klasse..."), this);
      mbNeueAllgemeineKlasse->setIconVisibleInMenu(true);
      mbNeueAllgemeineKlasse->setStatusTip(landestext->getText("Eine neue allgemeine Klasse anlegen."));
      connect(mbNeueAllgemeineKlasse, SIGNAL(triggered()), this, SLOT(neueKlasse()));

      // Untermenu Neue grafische Klasse
      //---------------------------------
      mbNeueGrafischeKlasse = new QAction(QIcon(bdpInstallVerzeichnis+"/babyDevelop/bilder/neu_klasse_grafisch_mini.xpm"), landestext->getText("Neue grafische Klasse..."), this);
      mbNeueGrafischeKlasse->setIconVisibleInMenu(true);
      mbNeueGrafischeKlasse->setStatusTip(landestext->getText("Eine neue grafische Klasse anlegen."));
      connect(mbNeueGrafischeKlasse, SIGNAL(triggered()), this, SLOT(neueQtKlasse()));

      // Untermenu Prototyp importieren
      //--------------------------------
      mbPrototypImportieren = new QAction(QIcon(bdpInstallVerzeichnis+"/babyDevelop/bilder/prototyp_importieren_mini.xpm"), landestext->getText("Prototyp importieren..."), this);
      mbPrototypImportieren->setIconVisibleInMenu(true);
      mbPrototypImportieren->setStatusTip(landestext->getText("Einen Prototyp importieren..."));
      connect(mbPrototypImportieren, SIGNAL(triggered()), this, SLOT(prototypImportieren()));

      // Untermenu Klasse Importieren
      //------------------------------
      mbKlasseImportieren = new QAction(QIcon(bdpInstallVerzeichnis+"/babyDevelop/bilder/klasse_importieren_mini.xpm"), landestext->getText("Klasse importieren..."), this);
      mbKlasseImportieren->setIconVisibleInMenu(true);
      mbKlasseImportieren->setStatusTip(landestext->getText("Eine Klasse importieren."));
      connect(mbKlasseImportieren, SIGNAL(triggered()), this, SLOT(klasseImportieren()));

      // Untermenu Prototyp Loeschen
      //-----------------------------
      mbPrototypLoeschen = new QAction(QIcon(bdpInstallVerzeichnis+"/babyDevelop/bilder/prototyp_loeschen_mini.xpm"), landestext->getText("Prototyp loeschen"), this);
      mbPrototypLoeschen->setIconVisibleInMenu(true);
      mbPrototypLoeschen->setStatusTip(landestext->getText("Eine Prototyp-Datei loeschen."));
      connect(mbPrototypLoeschen, SIGNAL(triggered()), this, SLOT(loeschenPrototyp()));

      // Untermenu Klasse loeschen
      //---------------------------
      mbKlasseLoeschen = new QAction(QIcon(bdpInstallVerzeichnis+"/babyDevelop/bilder/klasse_loeschen_mini.xpm"), landestext->getText("Klasse loeschen"), this);
      mbKlasseLoeschen->setIconVisibleInMenu(true);
      mbKlasseLoeschen->setStatusTip(landestext->getText("Eine Klassen-Datei loeschen."));
      connect(mbKlasseLoeschen, SIGNAL(triggered()), this, SLOT(loeschenKlasse()));

      // Untermenu Einstellungen
      //-------------------------
      mbEinstellungen = new QAction(QIcon(bdpInstallVerzeichnis+"/babyDevelop/bilder/einstellungen_mini.xpm"), "&"+landestext->getText("Einstellungen..."), this);
      mbEinstellungen->setIconVisibleInMenu(true);
      mbEinstellungen->setStatusTip(landestext->getText("Einstellungen fuer BabyDevelop und das Projekt."));
      connect(mbEinstellungen, SIGNAL(triggered()), this, SLOT(einstellungen()));


   // Bearbeiten-Menues einfuegen
   //-----------------------------
   menuBearbeiten = this->menuBar()->addMenu("&"+landestext->getText("Bearbeiten"));
      menuBearbeiten->addAction(mbRundschlag);
      menuBearbeiten->addSeparator();
      menuBearbeiten->addAction(mbKompilieren);
      menuBearbeiten->addAction(mbLinken);
      menuBearbeiten->addAction(mbAusfuehren);
      menuBearbeiten->addAction(mbAlleKompilieren);
      menuBearbeiten->addSeparator();
      menuBearbeiten->addAction(mbNeuerPrototyp);
      menuBearbeiten->addAction(mbNeueAllgemeineKlasse);
      menuBearbeiten->addAction(mbNeueGrafischeKlasse);
      menuBearbeiten->addAction(mbPrototypImportieren);
      menuBearbeiten->addAction(mbKlasseImportieren);
      menuBearbeiten->addSeparator();
      menuBearbeiten->addAction(mbPrototypLoeschen);
      menuBearbeiten->addAction(mbKlasseLoeschen);
      menuBearbeiten->addSeparator();
      menuBearbeiten->addAction(mbEinstellungen);


   //---------------------------------------------------------
   // Menue Info
   //---------------------------------------------------------
   menuInfo = new QMenu();

      // Untermenu Ueber BabyDevelop
      //-----------------------------
      miUeberBabyDevelop = new QAction(QIcon(bdpInstallVerzeichnis+"/babyDevelop/bilder/ueber_mini.xpm"), landestext->getText("Ueber BabyDevelop"), this);
      miUeberBabyDevelop->setIconVisibleInMenu(true);
      miUeberBabyDevelop->setStatusTip(landestext->getText("Ich zeige Ihnen wer ich bin."));
      connect(miUeberBabyDevelop, SIGNAL(triggered()), this, SLOT(ueberBabyDevelop()));

      // Untermenu Einfuehrung
      //-----------------------
      miEinfuehrung = new QAction(QIcon(bdpInstallVerzeichnis+"/babyDevelop/bilder/einfuehrung_mini.xpm"), landestext->getText("Einfuehrung"), this);
      miEinfuehrung->setIconVisibleInMenu(true);
      miEinfuehrung->setStatusTip(landestext->getText("Zeigt eine kleine Einfuehrung in BabyDevelop."));
      connect(miEinfuehrung, SIGNAL(triggered()), this, SLOT(einfuehrung()));

      // Untermenu Projekteigenschaften
      //--------------------------------
      miProjekteigenschaften = new QAction(QIcon(bdpInstallVerzeichnis+"/babyDevelop/bilder/projekteigenschaften_mini.xpm"), landestext->getText("Projekteigenschaften"), this);
      miProjekteigenschaften->setIconVisibleInMenu(true);
      miProjekteigenschaften->setStatusTip(landestext->getText("Zeigt die Eigenschaften des geoeffneten Projekts."));
      connect(miProjekteigenschaften, SIGNAL(triggered()), this, SLOT(projekteigenschaften()));

      // Untermenu ToDo
      //----------------
      miToDo = new QAction(QIcon(bdpInstallVerzeichnis+"/babyDevelop/bilder/todo_mini.xpm"), "ToDo", this);
      miToDo->setIconVisibleInMenu(true);
      miToDo->setStatusTip(landestext->getText("Es gibt viel zu tun - lassen wirs liegen :-)"));
      connect(miToDo, SIGNAL(triggered()), this, SLOT(todo()));

   // Info-Menues einfuegen
   menuInfo = this->menuBar()->addMenu("&Info");
      menuInfo->addAction(miUeberBabyDevelop);
      menuInfo->addAction(miEinfuehrung);
      menuInfo->addAction(miProjekteigenschaften);
      menuInfo->addSeparator();
      menuInfo->addAction(miToDo);


   //---------------------------------------------------------
   // Menue Hilfe
   //---------------------------------------------------------
   menuHilfe = new QMenu();

      // Untermenu Baby-C-Hilfe
      //------------------------
      mhBabyCHilfe = new QAction(QIcon(bdpInstallVerzeichnis+"/babyDevelop/bilder/c.xpm"), landestext->getText("Baby-C-Hilfe"), this);
      mhBabyCHilfe->setIconVisibleInMenu(true);
      mhBabyCHilfe->setStatusTip(landestext->getText("BabyDevelop-Hilfen fuer C."));
      connect(mhBabyCHilfe, SIGNAL(triggered()), this, SLOT(babyCHilfe()));

      // Untermenu Baby-C++-Hilfe
      //--------------------------
      mhBabyCppHilfe = new QAction(QIcon(bdpInstallVerzeichnis+"/babyDevelop/bilder/c++.xpm"), landestext->getText("Baby-C++-Hilfe"), this);
      mhBabyCppHilfe->setIconVisibleInMenu(true);
      mhBabyCppHilfe->setStatusTip(landestext->getText("BabyDevelop-Hilfen fuer C++."));
      connect(mhBabyCppHilfe, SIGNAL(triggered()), this, SLOT(babyCppHilfe()));

      // Untermenu Baby-Qt-Hilfe
      //-------------------------
      mhBabyQtHilfe = new QAction(QIcon(bdpInstallVerzeichnis+"/babyDevelop/bilder/bdp_hilfe_mini.xpm"), landestext->getText("Baby-Qt-Hilfe"), this);
      mhBabyQtHilfe->setIconVisibleInMenu(true);
      mhBabyQtHilfe->setStatusTip(landestext->getText("BabyDevelop-Hilfen fuer Qt-Widgets."));
      connect(mhBabyQtHilfe, SIGNAL(triggered()), this, SLOT(babyQtHilfe()));

      // Untermenu Qt-Hilfe
      //--------------------
      mhQtHilfe = new QAction(QIcon(bdpInstallVerzeichnis+"/babyDevelop/bilder/qt_hilfe_mini.xpm"), landestext->getText("Qt-Hilfe"), this);
      mhQtHilfe->setIconVisibleInMenu(true);
      mhQtHilfe->setStatusTip("Qt-Reference Documentation.");
      connect(mhQtHilfe, SIGNAL(triggered()), this, SLOT(qtHilfe()));

      // Untermenu FAQ
      //---------------
      mhFAQ = new QAction(QIcon(bdpInstallVerzeichnis+"/babyDevelop/bilder/faq_mini.xpm"), "FAQ", this);
      mhFAQ->setIconVisibleInMenu(true);
      mhFAQ->setStatusTip(landestext->getText("Referenzdokumentation, Hilfen und Beispiele zu besonderen Widgets."));
      connect(mhFAQ, SIGNAL(triggered()), this, SLOT(babyFAQ()));

      // Untermenu Meldungsfenster
      //---------------------------
      mhMeldungsfenster = new QAction(QIcon(bdpInstallVerzeichnis+"/babyDevelop/bilder/meldungsfenster_mini.xpm"), landestext->getText("Meldungsfenster"), this);
      mhMeldungsfenster->setIconVisibleInMenu(true);
      mhMeldungsfenster->setStatusTip(landestext->getText("Meldungsfenster ein-/ausschalten."));
      connect(mhMeldungsfenster, SIGNAL(triggered()), this, SLOT(meldungsfensterEinAus()));

      // Untermenu GUI-designer
      //------------------------
      mhGUIDesigner = new QAction(QIcon(bdpInstallVerzeichnis+"/babyDevelop/bilder/designer_mini.xpm"), "GUI-Designer", this);
      mhGUIDesigner->setIconVisibleInMenu(true);
      mhGUIDesigner->setStatusTip(landestext->getText("GUI-Designer starten."));
      connect(mhGUIDesigner, SIGNAL(triggered()), this, SLOT(startDesigner()));

      // Untermenu Debugger
      //--------------------
      mhDebugger = new QAction(QIcon(bdpInstallVerzeichnis+"/babyDevelop/bilder/debugger_mini.xpm"), "Debugger", this);
      mhDebugger->setIconVisibleInMenu(true);
      mhDebugger->setStatusTip(landestext->getText("Debugger starten."));
      connect(mhDebugger, SIGNAL(triggered()), this, SLOT(startDebugger()));


   // Hilfe-Menues einfuegen
   //------------------------
   menuHilfe = this->menuBar()->addMenu(landestext->getText("Hilfe"));
      menuHilfe->addAction(mhBabyCHilfe);
      menuHilfe->addAction(mhBabyCppHilfe);
      menuHilfe->addAction(mhBabyQtHilfe);
      menuHilfe->addAction(mhQtHilfe);
      menuHilfe->addAction(mhFAQ);
      menuHilfe->addSeparator();
      menuHilfe->addAction(mhMeldungsfenster);
      menuHilfe->addSeparator();
      menuHilfe->addAction(mhGUIDesigner);
      menuHilfe->addAction(mhDebugger);


   //Menues deaktivieren
   //--------------------
   mpSpeichern           ->setEnabled( false );
   mpSpeichernUnter      ->setEnabled( false );
   mpDateiSpeichern      ->setEnabled( false );
   mpSchliessen          ->setEnabled( false );
   mbRundschlag          ->setEnabled( false );
   mbKompilieren         ->setEnabled( false );
   mbLinken              ->setEnabled( false );
   mbAusfuehren          ->setEnabled( false );
   mbAlleKompilieren     ->setEnabled( false );
   mbNeuerPrototyp       ->setEnabled( false );
   mbNeueAllgemeineKlasse->setEnabled( false );
   mbNeueGrafischeKlasse ->setEnabled( false );
   mbPrototypImportieren ->setEnabled( false );
   mbKlasseImportieren   ->setEnabled( false );
   mbPrototypLoeschen    ->setEnabled( false );
   mbKlasseLoeschen      ->setEnabled( false );
   mhGUIDesigner         ->setEnabled( false );
   mhDebugger            ->setEnabled( false );


   //----------------------
   // Tabulatorbereich
   //----------------------
   tabulatorRahmen = new QTabWidget();

	// Tabulatorenbereich zuweisen
   //-----------------------------
	mitte = new QSplitter(Qt::Vertical);            // drei-teiliges Fenster -> mitte -> siehe babydevelop.h
	this->setCentralWidget(mitte);
   mitte->addWidget(tabulatorRahmen);
   mitte->addWidget(meldungsFenster);
   mitte->setStretchFactor(0, 2);
   mitte->setStretchFactor(1, 1);

   // Startbildanzeige erzeugen
   //---------------------------
   bildeStruktur("-/-");

   listing[nListings]->setFont( listingfont );
   listing[nListings]->setPlainText(landestext->getText("Kein Projekt geladen."));
   listing[nListings]->setPlainText("\n");

   listing[nListings]->setPlainText(listing[nListings]->toPlainText()+"\n\n\n"+
"            ____        _           ____                 _"+"\n"+
"           | __ )  __ _| |__  _   _|  _ \\  _____   _____| | ___  _ __"+"\n"+
"           |  _ \\ / _` | |_ \\| | | | | | |/ _ \\ \\ / / _ \\ |/ _ \\|  _ \\"+"\n"+
"           | |_) | (_| | |_) | |_| | |_| |  __/\\ V /  __/ | (_) | |_) |"+"\n"+
"           |____/ \\__,_|_.__/ \\__, |____/ \\___| \\_/ \\___|_|\\___/| .__/"+"\n"+
"                              |___/                             |_|"+version);


   // Statusleiste fuettern
   //-----------------------
	this->statusBar()->showMessage(landestext->getText("Willkommen zu BabyDevelop :-)"));
//ufg//this->resize(800,600);
	this->show();

   // Timer erzeugen welcher alle 10ms versucht Ausgaben vom Arbeiter zu lesen
   //--------------------------------------------------------------------------
   this->timer_ausgabe = new QTimer(this);
   this->timer_ausgabe->start(10);
   connect(this->timer_ausgabe, SIGNAL(timeout()), this, SLOT(ausgabeTimeout()));


   //---------------------------------------------
   //nur bei testversion--------------------------
//this->oeffnen("/tmp/testpro/steuerung.bdp");
//this->oeffnen("C:/testprojekt/test.bdp.bdp");
   //nur bei testversion--------------------------
   //---------------------------------------------
}


BabyDevelop::~BabyDevelop()
{
   // Anmerkung:
   // Funktioniert nicht, wenn man auf das [X] drueckt.
   // Siehe Methode beenden()
   delete meldungsFenster;
}


/* -------------------------------------------------------------------------- */
/* ------------------------------------------------------------- Methoden --- */
/* -------------------------------------------------------------------------- */


/* -------------------------------------------------------------------------- */
/* --------------------------------------------- Projekt - neuesProjekt-C --- */
/* -------------------------------------------------------------------------- */
void BabyDevelop::neuesProjektCErstellen()
{
   QString fd = QFileDialog::getSaveFileName(this, landestext->getText("Neues Projekt..."),QDir::homePath(),"Projektdatei (*.bdp)");
   if(fd=="")   // Abgebrochen
      return;

   projektVerzeichnis=fd.left(fd.lastIndexOf("/",-1));   // ohne rechten slash
   projektName=fd.mid(projektVerzeichnis.length()+1,-1); // ohne fuehrenden slash
   projektName=projektName.remove(" ");

   //Test auf unerlaubtes Zeichen im ProjektNamen
   //---------------------------------------------
   if(this->pruefeProjektName(projektName))
   {
      QString text = landestext->getText("...unerlaubtes Zeichen im ProjektNamen!\n\n(Erlaubte Zeichen: a...z, 0...9, _, -)");
      text = text + "\n(" + projektName + ")";
      QMessageBox::information(this,landestext->getText("Ich spreche..."),text);
      return;
   }
   //Test auf unerlaubtes Zeichen im VerzeichnisNamen
   //-------------------------------------------------
   if(this->pruefeVerzeichnisName(projektVerzeichnis))
   {
      QString text = landestext->getText("...unerlaubtes Zeichen im VerzeichnisNamen!\n\n(Erlaubte Zeichen: a...z, 0...9, _, -)");
      text = text + "\n(" + projektVerzeichnis + ")";
      QMessageBox::information(this,landestext->getText("Ich spreche..."),text);
      return;
   }

   // Schon ein Projekt geladen ->alle Member, Variablen, Objekte loeschen
   //----------------------------------------------------------------------
   if(projektTyp>0)
      deleteAll();
   projektVerzeichnis=fd.left(fd.lastIndexOf("/",-1));   //ohne rechten slash
   projektName=fd.mid(projektVerzeichnis.length()+1,-1);         //ohne fuehrenden slash
   projektName=projektName.remove(" ");


   projektTyp=1;   // 1=C, 2=C++, 3=C++/Qt, 4=GP2X/SDL-C 5=GP2X/SDL-C++, 0=kein Projekt geladen
   escape=1;

   // Test auf erster Buchstabe Grossbuchstabe
   //------------------------------------------
   if(projektName.left(1)!=projektName.left(1).toUpper())
   {
      QMessageBox::warning( this ,landestext->getText("- UML-Warnung -"), landestext->getText("Die Projektdatei soll mit einem Grossbuchstaben beginnen.<br>(Korrigiere selbstaendig)") );
   }

   // erster Buchstabe Grossbuchstabe
   //---------------------------------
   if(projektName.length()>1)
   {
      projektName=projektName.left(1).toUpper()+projektName.mid(1);
   }
   else
   {
      projektName=projektName.toUpper();
   }

   QString dateiName=fd;   //mit Pfad
   if(dateiName.right(4)!=".bdp")
      dateiName+=".bdp";

   //--- Projektdateien in Tabs erzeugen - main.c ---//
   //------------------------------------------------//
   // listing[1] wird schon beim Systemstart erzeugt
   listing[nListings]->setFont( listingfont );

   listing[nListings]->setPlainText(QString("/* main.c */\n\n") +
                               QString("#include <stdio.h>\n\n") +
                               QString("int main ()\n") +
                               QString("{\n") +
                               QString("   printf (\"I like BabyDevelop!\\n\");\n") +
                               QString("   //sleep(3);\n") +
                               QString("   return 0;\n") +
                               QString("}\n"));
   tabulatorRahmen->setTabText( 0, QString("[main.c]") );
   tabulatorRahmen->show();


   // Datei speichern - main.c
   //--------------------------
   QFile file_m( projektVerzeichnis+"/main.c" );
   if ( file_m.open( QIODevice::WriteOnly | QIODevice::Text) )
   {
      QTextStream strom( &file_m );
      strom << listing[1]->toPlainText();
      file_m.close();
   }

   // Babydevelop-Projektdatei speichern/schreiben
   //----------------------------------------------
   rueckgabeWert=script("projektdatei");

   // Scripte zum kompilieren, linken, ausfuehren erzeugen
   //------------------------------------------------------
   this->ladeRCFile();  // neutralisieren aller Parameter
/*   Libs="";             // da C-Projekt
*/

   // Makefile erzeugen
   //-------------------
   this->Makefile();

   // Projektverzeichnis+Name in Titelleiste anzeigen
   //-------------------------------------------------
   //   this->setCaption("BabyDevelop - "+projektVerzeichnis+"/"+projektName+" - (c)ufg);
	this->setWindowTitle("BabyDevelop - " + projektVerzeichnis + "/" + projektName);

   // Menuestatus
   //-------------
   mpSpeichern->setEnabled( true );
   mpSpeichernUnter->setEnabled( true );
   mpDateiSpeichern->setEnabled( true );
   mpSchliessen->setEnabled( true );
   mbRundschlag->setEnabled( true );
   mbKompilieren->setEnabled( true );
   mbLinken->setEnabled( true );
   mbAusfuehren->setEnabled( true );
   mbAlleKompilieren->setEnabled( true );
   mbNeuerPrototyp->setEnabled( true );
   mbNeueAllgemeineKlasse->setEnabled( false );
   mbNeueGrafischeKlasse->setEnabled( false );
   mbPrototypImportieren->setEnabled( true );
   mbKlasseImportieren->setEnabled( false );
   mbPrototypLoeschen->setEnabled( true );
   mbKlasseLoeschen->setEnabled( false );
   mhGUIDesigner->setEnabled( false );
   mhDebugger->setEnabled( true );


   // aktivieren von Signal currentChanged erst nach dem Laden/oeffnen
   //------------------------------------------------------------------
   connect(tabulatorRahmen, SIGNAL(currentChanged(int)), SLOT(reiterHervorheben(int)));
   lastReiterText="";
   schreibeRCFile("projekt");
}


/* -------------------------------------------------------------------------- */
/* ------------------------------------------- Projekt - neuesProjekt-C++ --- */
/* -------------------------------------------------------------------------- */
void BabyDevelop::neuesProjektCPPErstellen()
{
   // Verzeichnis und ProjektName eingeben
   //--------------------------------------
   QString fd=QFileDialog::getSaveFileName(this,landestext->getText("Neues C++-Projekt anlegen..."),QDir::homePath(),landestext->getText("Projektdatei")+" (*.bdp)");
   if(fd.isEmpty())   /* Abgebrochen */
      return;

   projektVerzeichnis=fd.left(fd.lastIndexOf('/',-1));   //ohne rechten slash
   projektName=fd.mid(fd.lastIndexOf('/',-1)+1);         //ohne fuehrenden slash
   projektName=projektName.remove(" ");

   // Test auf unerlaubtes Zeichen im ProjektNamen
   //----------------------------------------------
   if(this->pruefeProjektName(projektName))
   {
      QString text = landestext->getText("...unerlaubtes Zeichen im ProjektNamen!\n\n(Erlaubte Zeichen: a...z, 0...9, _, -)");
      text = text + "\n(" + projektName + ")";
      QMessageBox::information(this,landestext->getText("Ich spreche..."),text);
      return;
   }

   // Test auf unerlaubtes Zeichen im VerzeichnisNamen
   //--------------------------------------------------
   if(this->pruefeVerzeichnisName(projektVerzeichnis))
   {
      QString text = landestext->getText("...unerlaubtes Zeichen im VerzeichnisNamen!\n\n(Erlaubte Zeichen: a...z, 0...9, _, -)");
      text = text + "\n(" + projektVerzeichnis + ")";
      QMessageBox::information(this,landestext->getText("Ich spreche..."),text);
      return;
   }

   // Schon ein Projekt geladen ->alle Member, Variablen, Objekte loeschen
   //----------------------------------------------------------------------
   if(projektTyp>0)
      deleteAll();
   projektVerzeichnis=fd.left(fd.lastIndexOf('/',-1));   //ohne rechten slash
   projektName=fd.mid(fd.lastIndexOf('/',-1)+1);         //ohne fuehrenden slash
   projektName=projektName.remove(" ");

   projektTyp=2;   //1=C, 2=C++, 3=C++/Qt, 0=kein Projekt geladen
   escape=1;

   // Test auf erster Buchstabe Grossbuchstabe
   //------------------------------------------
   if(projektName.left(1)!=projektName.left(1).toUpper())
   {
      QMessageBox::warning( this ,landestext->getText("- UML-Warnung -"), landestext->getText("Die Projektdatei soll mit einem Grossbuchstaben beginnen.<br>(Korrigiere selbstaendig)") );
   }

   // erster Buchstabe Grossbuchstabe
   //---------------------------------
   if(projektName.length()>1)
   {
      projektName=projektName.left(1).toUpper()+projektName.mid(1);
   }
   else
   {
      projektName=projektName.toUpper();
   }

   QString dateiName=fd;   //mit Pfad
   if(dateiName.right(4)!=".bdp")
      dateiName+=".bdp";

   listing[nListings]->setFont( listingfont );

   //--- Projektdateien in Tabs erzeugen - 1. main.cpp ---//
   //-----------------------------------------------------//
   // listing[1] wird schon beim Systemstart erzeugt
   listing[nListings]->setPlainText(QString("/* main.cpp */\n\n") +
                               QString("#include <stdio.h>\n") +
                               QString("#include <stdlib.h>\n") +
                               QString("#include <iostream>\n") +
                               QString("using namespace std;\n\n") +
                               QString("int main ()\n") +
                               QString("{\n") +
                               QString("   cout << \"I like BabyDevelop, too!\" << endl;\n") +
                               QString("   //sleep(3);\n") +
                               QString("   return 0;\n") +
                               QString("}\n"));
   tabulatorRahmen->setTabText( 0, QString("[main.cpp]") );
   tabulatorRahmen->show();

   // Datei speichern - main.cpp
   //----------------------------
   QFile file_m( projektVerzeichnis+"/main.cpp" );
   if ( file_m.open( QIODevice::WriteOnly ) )
   {
      QTextStream stream( &file_m );
      stream << listing[1]->toPlainText();
      file_m.close();
   }

   // Babydevelop-Projektdatei speichern/schreiben
   rueckgabeWert=script("projektdatei");

   // Scripte zum kompilieren, linken, ausfuehren erzeugen
   //------------------------------------------------------
   this->ladeRCFile();   // neutralisieren aller Parameter
/*   Libs="";              // da C++-Projekt
*/

   // Makefile erzeugen
   //-------------------
   this->Makefile();

   // Projektverzeichnis+Name in Titelleiste anzeigen
   //-------------------------------------------------
   this->setWindowTitle("BabyDevelop - "+projektVerzeichnis+"/"+projektName);

   // Menuestatus
   //-------------
   mpSpeichern->setEnabled( true );
   mpSpeichernUnter->setEnabled( true );
   mpDateiSpeichern->setEnabled( true );
   mpSchliessen->setEnabled( true );
   mbRundschlag->setEnabled( true );
   mbKompilieren->setEnabled( true );
   mbLinken->setEnabled( true );
   mbAusfuehren->setEnabled( true );
   mbAlleKompilieren->setEnabled( true );
   mbNeuerPrototyp->setEnabled( false );
   mbNeueAllgemeineKlasse->setEnabled( true );
   mbNeueGrafischeKlasse->setEnabled( false );
   mbPrototypImportieren->setEnabled( false );
   mbKlasseImportieren->setEnabled( true );
   mbPrototypLoeschen->setEnabled( false );
   mbKlasseLoeschen->setEnabled( true );
   mhGUIDesigner->setEnabled( false );
   mhDebugger->setEnabled( true );


   // aktivieren von Signal currentChanged erst nach dem Laden/oeffnen
   //------------------------------------------------------------------
   connect(tabulatorRahmen, SIGNAL(currentChanged(int)), SLOT(reiterHervorheben(int)));
   lastReiterText="";
   schreibeRCFile("projekt");
}


/* -------------------------------------------------------------------------- */
/* -------------------------------------------- Projekt - neuesProjekt-Qt --- */
/* -------------------------------------------------------------------------- */
void BabyDevelop::neuesProjektQtErstellen()
{
   // Verzeichnis und ProjektName eingeben
   //--------------------------------------
   QString fd=QFileDialog::getSaveFileName(this,landestext->getText("Neues Qt/CPP-Projekt anlegen..."),QDir::homePath(),landestext->getText("Projektdatei")+" (*.bdp)");
   if(fd.isEmpty())   // Abgebrochen
      return;

   projektVerzeichnis=fd.left(fd.lastIndexOf('/', - 1));   //ohne rechten slash
   projektName=fd.mid(fd.lastIndexOf('/',-1) + 1);         //ohne fuehrenden slash
   projektName=projektName.remove(" ");

   // Test auf unerlaubtes Zeichen im ProjektNamen
   //----------------------------------------------
   if(this->pruefeProjektName(projektName))
   {
      QString text = landestext->getText("...unerlaubtes Zeichen im ProjektNamen!\n\n(Erlaubte Zeichen: a...z, 0...9, _, -)");
      text = text + "\n(" + projektName + ")";
      QMessageBox::information(this,landestext->getText("Ich spreche..."),text);
      return;
   }

   // Test auf unerlaubtes Zeichen im VerzeichnisNamen
   //--------------------------------------------------
   if(this->pruefeVerzeichnisName(projektVerzeichnis))
   {
      QString text = landestext->getText("...unerlaubtes Zeichen im VerzeichnisNamen!\n\n(Erlaubte Zeichen: a...z, 0...9, _, -)");
      text = text + " (" + projektName + ")";
      QMessageBox::information(this,landestext->getText("Ich spreche..."),text);
      return;
   }

   // Schon ein Projekt geladen ->alle Member, Variablen, Objekte loeschen
   //----------------------------------------------------------------------
   if(projektTyp > 1)
      deleteAll();
   projektVerzeichnis=fd.left(fd.lastIndexOf('/', -1));   //ohne rechten slash
   projektName=fd.mid(fd.lastIndexOf('/', -1)+1);         //ohne fuehrenden slash
   projektName=projektName.remove(" ");

   projektTyp = 3;   //1=C, 2=C++, 3=C++/Qt, 0=kein Projekt geladen
   schreibeRCFile("projekt");

   // Test auf erster Buchstabe Grossbuchstabe
   //------------------------------------------
   if(projektName.left(1) != projektName.left(1).toUpper())
   {
      QMessageBox::warning( this, landestext->getText("- UML-Warnung -"), landestext->getText("Die Projektdatei soll mit einem Grossbuchstaben beginnen, da daraus die Basisklasse entsteht.<br>(Korrigiere selbstaendig)") );
   }

   // erster Buchstabe Grossbuchstabe
   //---------------------------------
   if(projektName.length() > 1)
   {
      projektName = projektName.left(1).toUpper() + projektName.mid(1);
   }
   else
   {
      projektName = projektName.toUpper();
   }

   // SuSE 10.0-KDE-Problem abfangen d.h. .bdp wegschneiden
   //-------------------------------------------------------
   if( (projektName.length()>4) && (projektName.right(4)==".bdp") )
      projektName=projektName.left(projektName.length()-4);

   QString dateiName=fd;   //mit Pfad
   if(dateiName.right(4)!=".bdp")
      dateiName+=".bdp";

   listing[nListings]->setFont( listingfont );
//   listing[nListings]->setPlainText(listing[nListings]->toPlainText()+"\n\n\n"+

   //--- Projektdateien in Tabs erzeugen - 1. main.cpp ---//
   //-----------------------------------------------------//
   // listing[1] wird schon beim Systemstart erzeugt
   listing[nListings]->setPlainText(QString("/* main.cpp */\n\n") +
                               QString("#include <qapplication.h>\n\n") +
                               QString("#include \"" + projektName.toLower() + ".h\"\n\n") +
                               QString("int main(int argc, char **argv)\n") +
                               QString("{\n") +
                               QString("   QApplication meinProgramm(argc, argv);\n") +
                               QString("   " + projektName + " " + projektName.toLower() + ";\n") +
                               QString("   " + projektName.toLower() + ".show();\n") +
                               QString("   int rueckgabe = meinProgramm.exec();\n") +
                               QString("   return rueckgabe;\n") +
                               QString("}\n") );

   tabulatorRahmen->setTabText( 0, QString("[main.cpp]") );

   //--- Projektdateien in Tabs erzeugen - 2. basisklasse.cpp ---//
   nListings++;
   bildeStruktur(projektName.toLower() + ".cpp");

   listing[nListings]->setFont( listingfont );

   listing[nListings]->setPlainText(QString("/* " + projektName.toLower() + ".cpp */\n\n") +
                               QString("#include \"" + projektName.toLower() + ".h\"\n\n") +
                               QString("/* Konstruktor */\n") +
                               QString(projektName + "::" + projektName + "() : ProgrammFenster()\n") +
                               QString("{\n") +
                               QString("}\n\n") +
                               QString("/* Destruktor */\n") +
                               QString(projektName + "::~" + projektName + " ()\n") +
                               QString("{\n") +
                               QString("}\n"));

   //--- Projektdateien in Tabs erzeugen - 3. basisklasse.h ---//
   nListings++;
   bildeStruktur(projektName.toLower()+".h");

   listing[nListings]->setFont( listingfont );

   listing[nListings]->setPlainText(QString("/* " + projektName.toLower() + ".h */\n\n") +
                               QString("#ifndef "+projektName.toUpper()+"_H\n") +
                               QString("#define "+projektName.toUpper()+"_H\n\n") +
#if defined(LINUX)
                               QString("#include \"/opt/babyDevelop/programmfenster.h\"\n\n") +
#elif defined(WIN32)
                               QString("#include \"C:\\opt\\babyDevelop\\programmfenster.h\"\n\n") +
#endif
                               QString("class " + projektName + " : public ProgrammFenster\n") +
                               QString("{\n") +
                               QString("   Q_OBJECT\n") +
                               QString("public:\n") +
                               QString("   " + projektName + "(); //Konstruktor\n") +
                               QString("  ~" + projektName + "(); //Destruktor\n") +
                               QString("};\n\n") +
                               QString("#endif\n"));

   tabulatorRahmen->show();

   // alle Dateien speichern - 1. main.cpp
   //--------------------------------------
   QFile file_m( projektVerzeichnis+"/main.cpp" );
   if ( file_m.open( QIODevice::WriteOnly ) )
   {
      QTextStream stream( &file_m );
      stream << listing[1]->toPlainText();
      file_m.close();
   }

   // alle Dateien speichern - 2. basisklasse.cpp
   //---------------------------------------------
   QFile file_cpp( projektVerzeichnis+"/"+projektName.toLower()+".cpp" );
   if ( file_cpp.open( QIODevice::WriteOnly ) )
   {
      QTextStream stream( &file_cpp );
      stream << listing[2]->toPlainText();
      file_cpp.close();
   }

   // alle Dateien speichern - 3. basisklasse.h
   //-------------------------------------------
   QFile file_h( projektVerzeichnis+"/"+projektName.toLower()+".h" );
   if ( file_h.open( QIODevice::WriteOnly ) )
   {
      QTextStream stream( &file_h );
      stream << listing[3]->toPlainText();
      file_h.close();
   }

   // Babydevelop-Projektdatei speichern/schreiben
   //----------------------------------------------
   rueckgabeWert=script("projektdatei");

   // Scripte zum kompilieren, linken, ausfuehren erzeugen
   //------------------------------------------------------
   this->ladeRCFile();   //neutralisieren aller Parameter

/*   rueckgabeWert=script("main");
*/

   // Makefile erzeugen
   //-------------------
   this->Makefile();

   // Projektverzeichnis+Name in Titelleiste anzeigen
   //-------------------------------------------------
   this->setWindowTitle("BabyDevelop - "+projektVerzeichnis+"/"+projektName);

   // Menuestatus
   //-------------
   mpSpeichern->setEnabled( true );
   mpSpeichernUnter->setEnabled( true );
   mpDateiSpeichern->setEnabled( true );
   mpSchliessen->setEnabled( true );
   mbRundschlag->setEnabled( true );
   mbKompilieren->setEnabled( true );
   mbLinken->setEnabled( true );
   mbAusfuehren->setEnabled( true );
   mbAlleKompilieren->setEnabled( true );
   mbNeuerPrototyp->setEnabled( false );
   mbNeueAllgemeineKlasse->setEnabled( true );
   mbNeueGrafischeKlasse->setEnabled( true );
   mbPrototypImportieren->setEnabled( false );
   mbKlasseImportieren->setEnabled( true );
   mbPrototypLoeschen->setEnabled( false );
   mbKlasseLoeschen->setEnabled( true );
   mhGUIDesigner->setEnabled( true );
   mhDebugger->setEnabled( true );


   // aktivieren von Signal currentChanged erst nach dem Laden/oeffnen
   //------------------------------------------------------------------
   connect(tabulatorRahmen,SIGNAL(currentChanged(int)),SLOT(reiterHervorheben(int)));
   lastReiterText="";
}


/* -------------------------------------------------------------------------- */
/* ---------------------------------------------------- Projekt - oeffnen --- */
/* ---------------------------------------------------     Ueberladen     --- */
/* -------------------------------------------------------------------------- */
void BabyDevelop::oeffnen(QString datei)
{
   if("file:///" == datei.left(8))
   {
      datei = datei.mid(7);
   }
   fd = datei;

   oeffnenJetzt();
}

void BabyDevelop::oeffnen()
{
   fd = QFileDialog::getOpenFileName(this,landestext->getText("Projekt waehlen..."),QDir::homePath(),landestext->getText("Projektdatei")+" (*.bdp)");

   if(fd.isEmpty())
   {
      return; // Abgebrochen
   }

   oeffnenJetzt();
}

void BabyDevelop::oeffnenJetzt()
{
   QString pV=fd.left(fd.lastIndexOf("/",-1));   //ProjektVerzeichnis ohne rechten slash
   QString pN=fd.mid(fd.lastIndexOf("/",-1)+1);  //ProjektName ohne fuehrenden slash

   // Test auf unerlaubtes Zeichen im ProjektNamen
   //----------------------------------------------
   if(this->pruefeProjektName(pN))
   {
      QMessageBox::information(this,"Ich spreche...","...unerlaubtes Zeichen im ProjektNamen!\n\n(Erlaubt sind: a...z, 0...9, _, -)");
      return;
   }

   // Test auf unerlaubtes Zeichen im VerzeichnisNamen
   //--------------------------------------------------
   if(this->pruefeVerzeichnisName(pV))
   {
      QMessageBox::information(this,"Ich spreche...","...unerlaubtes Zeichen im VerzeichnisNamen!\n\n(Erlaubt sind: a...z, 0...9, _, -)");
      return;
   }

   // Meldungsfenster loeschen
   //--------------------------
   meldungsFenster->setPlainText("");

   // Menues zuruecksetzen
   //----------------------
   mbNeuerPrototyp->setEnabled( false );
   mbNeueAllgemeineKlasse->setEnabled( false );
   mbNeueGrafischeKlasse->setEnabled( false );
   mbPrototypImportieren->setEnabled( false );
   mbKlasseImportieren->setEnabled( false );
   mbPrototypLoeschen->setEnabled( false );
   mbKlasseLoeschen->setEnabled( false );
   mhGUIDesigner->setEnabled( false );

   // Schon ein Projekt geladen ->alle Member, Variablen, Objekte loeschen
   //----------------------------------------------------------------------
   if(projektTyp>1)
   {
      this->deleteAll();
   }

   projektVerzeichnis=fd.left(fd.lastIndexOf('/',-1));   // ohne rechten slash
   projektName=fd.mid(fd.lastIndexOf('/',-1)+1);         // ohne fuehrenden slash

   this->ladeRCFile();   // babydevelop.rc laden (Parameter neutralisieren)

   QFile file(fd);   // Projektdatei einlesen
   if(!file.open(QIODevice::ReadOnly))
   {
      meldungsFenster->setPlainText( meldungsFenster->toPlainText() + "\n" + landestext->getText("Projektdatei einlesen gescheitert.") );
      return;
   }
   QTextStream stream(&file);

   // Datei einlesen
   //----------------
   QString zeile;
   zeile = stream.readLine();   // BabyDevelop-Projektdatei             (1.Zeile)
   zeile = stream.readLine();   // ProjektName=...                      (2.Zeile)
      projektName=zeile.mid(zeile.indexOf("=",0)+1);
      this->setWindowTitle("- BabyDevelop - "+projektName);

   zeile = stream.readLine();   // ProjektTyp                           (3.Zeile)
                                // Anmerkung bei bdp-Version < 3 kommt hier nKlassen -> wird nicht mehr unterstuetzt!
   if(!zeile.contains("ProjektTyp="))
   {
      meldungsFenster->setPlainText(landestext->getText("Struktur der Projektdatei fehlerhaft."));
      return;
   }
   projektTyp=zeile.mid(zeile.indexOf("=",0)+1).toInt();   //0=gibts nicht, 1=C, 2=C++, 3=C++/Qt, 4=GP2X/SDL/C, 5=GP2X/SDL/C++
   if(projektTyp!=3)
   {
      Libs="";   // da kein Qt-Projekt; das sind die Libs der oberen haelfte im einstelluns-fenster
   }

   // Parametergruppe "Klassen"
   //---------------------------
   zeile = stream.readLine();   // nKlassen=...
   nKlassen=zeile.mid(zeile.indexOf("=", 0) +1).toInt();

   // Klassennamen einlesen
   //-----------------------
   int z = 0;
   while(z < nKlassen)   // Klassennamen einlesen
   {                     // erste eigene Klasse = Nr. 1
      z++;
      zeile          = stream.readLine();   // KlassenName[1...]
      klassenName[z] = zeile.mid(zeile.indexOf("=",0) +1);
      zeile          = stream.readLine();   // KlassenArt[0=allgem.Klasse, 1=QtKlasse]
      klassenArt[z]  = zeile.mid(zeile.indexOf("=",0) +1).toInt();
   }

   file.close();
   // delete fd;  <--bewirkt Speicherzugriffsfehler!!!

   // Quellcodedateien laden
   //------------------------
   //--- Quellcodedateien laden - 1. main.c/cpp ---//
   //----------------------------------------------//
   QString endung;
   if(projektTyp == 1)
   {
      endung="c";
   }
   else
   {
      endung="cpp";
   }
   QFile file2(projektVerzeichnis+"/main."+endung);
   if(!file2.open(QIODevice::ReadOnly))
   {
      meldungsFenster->setPlainText( landestext->getText("Kann Datei ") );
      meldungsFenster->setPlainText( meldungsFenster->toPlainText() + "main." + endung + " " );
      meldungsFenster->setPlainText( meldungsFenster->toPlainText() + landestext->getText("nicht oeffnen.") );
      return;
   }
   QTextStream stream2(&file2);

   // main.c/cpp-Datei einlesen
   //---------------------------
   listing[nListings]->setFont( listingfont );

   listing[nListings]->setPlainText(stream2.readAll());
   file2.close();

   tabulatorRahmen->setTabText( nListings-1, QString("[main."+endung+"]") );

   // Meldungen
   //-----------
   meldungsFenster->setPlainText( landestext->getText("Projekt") + ": " + projektName + "\n");
   meldungsFenster->setPlainText(meldungsFenster->toPlainText() + landestext->getText("ProjektTyp") + ": ");
   switch(projektTyp)
   {
      case 1:meldungsFenster->setPlainText(meldungsFenster->toPlainText()+"C");break;
      case 2:meldungsFenster->setPlainText(meldungsFenster->toPlainText()+"C++");break;
      case 3:meldungsFenster->setPlainText(meldungsFenster->toPlainText()+"Qt/C++");break;
   }
   meldungsFenster->setPlainText(meldungsFenster->toPlainText() + "\n" + landestext->getText("Verzeichnis") + ": " + projektVerzeichnis );
   meldungsFenster->setPlainText(meldungsFenster->toPlainText() + "\n" + "main." + endung + " " + landestext->getText("geladen"));

   if(projektTyp==3)
   {
      // Qt-Typ -> BasisKlasse muss eingelesen werden
      //--- Quellcodedateien laden - 2. basisklasse.cpp ---//
      //---------------------------------------------------//
      nListings++;
      bildeStruktur(projektName.toLower()+".cpp");

      QFile file3(projektVerzeichnis+"/"+projektName.toLower()+".cpp");

      if(!file3.open(QIODevice::ReadOnly))
      {
         meldungsFenster->setPlainText( meldungsFenster->toPlainText() + "\n" + landestext->getText("Kann Datei") );
         meldungsFenster->setPlainText( meldungsFenster->toPlainText() + projektName.toLower() + ".cpp ");
         meldungsFenster->setPlainText( meldungsFenster->toPlainText() + landestext->getText("nicht oeffnen.") );
         return;
      }

      // basisklasse.cpp-Datei (bzw. projektname.cpp) auslesen
      //-------------------------------------------------------
      QTextStream stream_cpp(&file3);
      listing[nListings]->setFont( listingfont );
      listing[nListings]->setPlainText(stream_cpp.readAll());
      file3.close();

      //--- Quellcodedateien laden - 3. basisklasse.h ---//
      //-------------------------------------------------//
      nListings++;
      bildeStruktur(projektName.toLower() + ".h");

      QFile file4(projektVerzeichnis + "/" + projektName.toLower() + ".h");
      if(!file4.open(QIODevice::ReadOnly))
      {
         meldungsFenster->setPlainText( meldungsFenster->toPlainText() + "\n" + landestext->getText("Kann Datei") );
         meldungsFenster->setPlainText( meldungsFenster->toPlainText() + projektName.toLower() + ".h" );
         meldungsFenster->setPlainText( meldungsFenster->toPlainText() + landestext->getText("nicht oeffnen.") );
         return;
      }

      // basisklasse.h-Datei (bzw. projektname.h) auslesen
      //---------------------------------------------------
      QTextStream stream_h(&file4);

      listing[nListings]->setFont( listingfont );

      listing[nListings]->setPlainText(stream_h.readAll());
      file4.close();

      // Meldung
      //---------
      meldungsFenster->setPlainText(meldungsFenster->toPlainText() + "\n" + landestext->getText("Basisklasse geladen") + "\n");
   }

   /* ----------------------------------------------------------------------- */
   /* ----------------------------------------------- eigene Klassen einlesen */
   /* ----------------------------------------------------------------------- */
   z=0;
   while(z<nKlassen)
   {
      // Klassendateien laden
      // erste eigene Klasse = klassenName[1]
      z++;
      QFile file_cpp(projektVerzeichnis+"/"+klassenName[z].toLower()+"."+endung);
      if(!file_cpp.open(QIODevice::ReadOnly))
      {
         meldungsFenster->setPlainText( meldungsFenster->toPlainText() + "\n" + landestext->getText("Kann Datei") );
         meldungsFenster->setPlainText( meldungsFenster->toPlainText() + " " + klassenName[z].toLower() + "." + endung );
         meldungsFenster->setPlainText( meldungsFenster->toPlainText() + " " + landestext->getText("nicht oeffnen.") );
         return;
      }

      // c-/cpp-Datei
      //--------------
      nListings++;
      bildeStruktur(klassenName[z].toLower()+"."+endung);

      QTextStream stream_cpp(&file_cpp);

      // c-/cpp-Datei auslesen
      //-----------------------
      listing[nListings]->setFont( listingfont );

      listing[nListings]->setPlainText(stream_cpp.readAll());
      file_cpp.close();

      // Header-Datei
      //--------------
      nListings++;
      bildeStruktur(klassenName[z].toLower()+".h");

      QFile file_h(projektVerzeichnis+"/"+klassenName[z].toLower()+".h");
      if(!file_h.open(QIODevice::ReadOnly))
      {
         meldungsFenster->setPlainText( meldungsFenster->toPlainText() + "\n" + landestext->getText("Kann Datei") );
         meldungsFenster->setPlainText( meldungsFenster->toPlainText() + " " + klassenName[z].toLower() + ".h");
         meldungsFenster->setPlainText( meldungsFenster->toPlainText() + " " + landestext->getText("nicht oeffnen.") );
         return;
      }
      QTextStream stream_h(&file_h);

      // h-Datei einlesen
      //------------------
      listing[nListings]->setFont( listingfont );

      listing[nListings]->setPlainText(stream_h.readAll());
      file_h.close();

      // Meldung
      //---------
      meldungsFenster->setPlainText(meldungsFenster->toPlainText() + "\n" + landestext->getText("Klasse ")+klassenName[z]+"\n"+landestext->getText("geladen"));
   }

   //--- Projektparameter laden
   //---------------------------
   if(QFile::exists(projektVerzeichnis+"/bdpProjekt.rc"))
   {
      // Datei vorhanden
      //-----------------
      QFile filep(projektVerzeichnis+"/bdpProjekt.rc");
      if(!filep.open(QIODevice::ReadOnly))
      {
         meldungsFenster->setPlainText( meldungsFenster->toPlainText() + "\n" + landestext->getText("Kann Datei bdpProjekt.rc nicht oeffnen."));
         return;
      }
      QTextStream streamp(&filep);

      // bdpProjek.rc-Datei einlesen
      //-----------------------------
      QString line;
      line = streamp.readLine();   // BabyDevelopProjektRC-File
      line = streamp.readLine();   // n.c.
      line = streamp.readLine();   // CompilerFlags=/usr/include/SDL -D_REENTRANT (z.B.)
      compilerFlags=line.mid(line.lastIndexOf("=",-1));
      if(compilerFlags=="=")
      {   // nix definiert
         compilerFlags="";
      }
      else
      {
         compilerFlags=compilerFlags.mid(1);
      }
      line = streamp.readLine();   // LinkerFlags=/usr/lib -lSDL -lpthread (z.B.)
      linkerFlags=line.mid(line.lastIndexOf("=",-1));
      if(linkerFlags=="=")
      {   //nix definiert
         linkerFlags="";
      }
      else
      {
         linkerFlags=linkerFlags.mid(1);
      }
      line = streamp.readLine();   // war GP2XCompilerFlags=/usr/local/gp2xdev/include/SDL -D_REENTRANT (z.B.)
      line = streamp.readLine();   // war GP2XLinkerFlags=/usr/local/gp2xdev/lib -Wl,-rpath,/usr/local/gp2xdev/lib -lSDL -lpthread (z.B.)
      line = streamp.readLine();   // n.c.
      line = streamp.readLine();   // escapeSequenzen=1 ist Standard fuer C und C++
      if(line.contains("1",Qt::CaseInsensitive))
      {
         escape=1;
      }
      else
      {
         escape=0;
      }
      line = streamp.readLine();   // n.c.
      line = streamp.readLine();   // n.c.
      file2.close();

      // Meldung
      //---------
      meldungsFenster->setPlainText(meldungsFenster->toPlainText() + "\n" + landestext->getText("CompilerFlags und LinkerFlags geladen.") );
   }
   else
   {
      // keine Projektparameter definiert
      //----------------------------------
      meldungsFenster->setPlainText( meldungsFenster->toPlainText() + "\n" + landestext->getText("Information: Keine Projektparameter definiert.") );
      autoSpeichern    = 1;
      compilerFlags    = "";
      linkerFlags      = "";
   }

   /* ---------------------------------------.------------------------------- */
   /*                                        | Scripte jedesmal neu schreiben */
   /*                                        '------------------------------- */
   speichereScripte();
   tabulatorRahmen->show();

   // Projektverzeichnis+Name in Titelleiste anzeigen
   //-------------------------------------------------
   this->setWindowTitle(projektVerzeichnis+"/"+projektName+" - BabyDevelop " + version);

   // Menuestatus
   //-------------
   mpSpeichern->setEnabled( true );
   mpSpeichernUnter->setEnabled( true );
   mpDateiSpeichern->setEnabled( true );
   mpSchliessen->setEnabled( true );

   mbRundschlag->setEnabled( true );
   mbKompilieren->setEnabled( true );
   mbLinken->setEnabled( true );
   mbAusfuehren->setEnabled( true );
   mbAlleKompilieren->setEnabled( true );
   mhDebugger->setEnabled( true );

   if(projektTyp==1)   // =C
   {
      mbNeuerPrototyp->setEnabled(true );
      mbPrototypImportieren->setEnabled( true );
      mbPrototypLoeschen->setEnabled( true );
   }
   else if(projektTyp==2)   // =C++
   {
      mbNeueAllgemeineKlasse->setEnabled( true );
      mbKlasseImportieren->setEnabled( true );
   }
   else   // projektTyp=3=C++/Qt
   {
      mbNeueAllgemeineKlasse->setEnabled( true );
      mbNeueGrafischeKlasse->setEnabled( true );
      mbKlasseImportieren->setEnabled( true );
      mhGUIDesigner->setEnabled( true );
   }

   if(nKlassen>0)
   {
      if( (projektTyp==1)||(projektTyp==4) )
      {
         mbPrototypLoeschen->setEnabled( true );
      }
      else
      {
         mbKlasseLoeschen->setEnabled( true );
      }
   }

   // aktivieren von Signal currentChanged erst nach dem Laden/oeffnen
   //------------------------------------------------------------------
   connect(tabulatorRahmen, SIGNAL(currentChanged(int)), SLOT(reiterHervorheben(int)));
   lastReiterText="";
}


/* -------------------------------------------------------------------------- */
/* -------------------------------------------------- Projekt - speichern --- */
/* -------------------------------------------------------------------------- */
void BabyDevelop::speichern()
{
   speichereListings();
}


/* -------------------------------------------------------------------------- */
/* -------------------------------------------- Projekt - speichern unter --- */
/* -------------------------------------------------------------------------- */
void BabyDevelop::speichernUnter()
{
   // Verzeichnis und ProjektName eingeben
   //--------------------------------------
   QString fd=QFileDialog::getExistingDirectory(this,landestext->getText("Verzeichnis waehlen..."),QDir::homePath(),QFileDialog::ShowDirsOnly);
   if(fd.isEmpty()) // Abgebrochen
   {
      return;
   }
   projektVerzeichnis=fd;  // ohne rechten slash

   speichereListings();
   speichereScripte();
   rueckgabeWert=script("projektdatei");

   // Projektverzeichnis+Name in Titelleiste anzeigen
   //-------------------------------------------------
   this->setWindowTitle("BabyDevelop - "+projektVerzeichnis+"/"+projektName);
}


/* -------------------------------------------------------------------------- */
/* --------------------------------------------- Projekt - Datei speichern -- */
/* -------------------------------------------------------------------------- */
void BabyDevelop::speichernDatei()
{
   // Nur aktive Datei speichern
   //----------------------------
   QString zielDatei = tabulatorRahmen->tabText(tabulatorRahmen->currentIndex());
   zielDatei = zielDatei.remove("[");
   zielDatei = zielDatei.remove("]");

   int aktive = tabulatorRahmen->currentIndex() + 1;
   QFile file( projektVerzeichnis + "/" + zielDatei );
   if ( file.open( QIODevice::WriteOnly ) )
   {
      QTextStream stream( &file );
      stream << listing[aktive]->toPlainText();
      file.close();
   }
   else
   {
      meldungsFenster->setPlainText( landestext->getText("Kann Datei") );
      meldungsFenster->setPlainText( meldungsFenster->toPlainText() + " " + zielDatei );
      meldungsFenster->setPlainText( meldungsFenster->toPlainText() + " " + landestext->getText("nicht oeffnen.") );
   }
}


/* -------------------------------------------------------------------------- */
/* ------------------------------------------------- Projekt - schliessen --- */
/* -------------------------------------------------------------------------- */
void BabyDevelop::schliessen()
{
   // alle Member, Variablen, Objekte loeschen
   //------------------------------------------
   deleteAll();

   // Menuestatus
   //-------------
   mpSpeichern->setEnabled( false );
   mpSpeichernUnter->setEnabled( false );
   mpDateiSpeichern->setEnabled( false );
   mpSchliessen->setEnabled( false );
   mbRundschlag->setEnabled( false );
   mbKompilieren->setEnabled( false );
   mbLinken->setEnabled( false );
   mbAusfuehren->setEnabled( false );
   mbAlleKompilieren->setEnabled( false );
   mbNeueAllgemeineKlasse->setEnabled( false );
   mbNeueGrafischeKlasse->setEnabled( false );
   mbKlasseImportieren->setEnabled( false );
   mbKlasseLoeschen->setEnabled( false );
   mhGUIDesigner->setEnabled( false );
   mhDebugger->setEnabled( false );

   // deaktivieren von Signal currentChanged beim Projekt schiessen
   //---------------------------------------------------------------
   disconnect(tabulatorRahmen, SIGNAL(currentChanged(QWidget*)));
   lastReiterText="";
}


/* -------------------------------------------------------------------------- */
/* ---------------------------------------------------- Projekt - beenden --- */
/* -------------------------------------------------------------------------- */
void BabyDevelop::beenden(void)
{
   this->loescheDateien();
	qApp->quit();
}


/* -------------------------------------------------------------------------- */
/* ---------------------- *.sh-, *.moc-, *.moc.cpp-, *.o-Dateien loeschen --- */
/* -------------------------------------------------------------------------- */
void BabyDevelop::loescheDateien()
{
	this->meldungsFenster->clear();
   if(projektVerzeichnis != "")
      this->arbeiter->start(ARBEITER_LOESCHEN, this->projektVerzeichnis, "");
}


/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------- Menues-Bearbeiten */
/* -------------------------------------------------------------------------- */


/* -------------------------------------------------------------------------- */
/* ---------------------------------------------- Bearbeiten - rundschlag --- */
/* -------------------------------------------------------------------------- */
void BabyDevelop::rundschlag()
{
	if(autoSpeichern == 1)
		speichereListings();

	this->meldungsFenster->clear();
	this->schreibeMeldungsfenster(">>> Rundschlag <<<\n");

	this->arbeiter->start(ARBEITER_RUNDSCHLAG, this->projektVerzeichnis, "");
}


/* -------------------------------------------------------------------------- */
/* --------------------------------------------- Bearbeiten - kompilieren --- */
/* -------------------------------------------------------------------------- */
void BabyDevelop::kompilieren()
{
	if(autoSpeichern == 1)
		speichernDatei();

	// [foobar.c] -> foobar.o
	QString modul = tabulatorRahmen->tabText(tabulatorRahmen->currentIndex());
	modul = modul.left(modul.lastIndexOf(".", -1));
   modul = modul.mid(1);   // -> foobar

   //modul bleibt unveraendert  //ufg
   //modul += ".o";             //Marcel

	this->meldungsFenster->clear();

   bool ist_moc_klasse = false;
   if(projektTyp==3) //Qt-Projekt
   {
      if(modul==projektName.toLower()) //Basisklasse braucht moc
      {
         ist_moc_klasse = true;
      }
      else if(nKlassen>0) //es gibt eigene Klassen
      {
         for(int z=0; z<nKlassen; z++) //ob die aktive Klasse den moc braucht ermitteln
         {                             //es ist auch moeglich, dass garkeine Klasse den moc braucht
            if(klassenName[z+1].toLower()==modul)
            {
               if(klassenArt[z+1]==1) //Qt-Klasse die den moc braucht
               {
                  ist_moc_klasse = true;
                  break; //sobald die Klasse gefunden wurde
               }
            }
         }
      }
   }
   if(ist_moc_klasse)
   {
      // MOC-Klasse
      // moc-Kompilieren + normal kompilieren
      // zuvor jedoch dateiname.moc.o loeschen weil make nicht immer merkt wenn sich etwas veraendert hat
      QFile file;
      file.remove(projektVerzeichnis + "/" + modul + ".moc.o");

      this->schreibeMeldungsfenster(">>> moc-Kompilieren (" + modul + ".moc.o) <<<\n");
      // MUSS in einem Schritt passieren, da multi-threading
      this->arbeiter->start(ARBEITER_MOC, this->projektVerzeichnis, modul + ".o " + modul + ".moc.o");
   }
   else
   {
      // definitiv keine MOC-Klasse
      // nur kompilieren
      // zuvor jedoch dateiname.o loeschen weil der make nicht immer merkt wenn sich etwas veraendert hat
      QFile file;
      file.remove(projektVerzeichnis + "/" + modul + ".o");
      this->schreibeMeldungsfenster(">>> Kompilieren (" + modul + ".o) <<<\n");
      this->arbeiter->start(ARBEITER_KOMPILIEREN, this->projektVerzeichnis, modul + ".o");
   }
}


/* -------------------------------------------------------------------------- */
/* ---------------------------------------- Bearbeiten - kompilieren_alle --- */
/* -------------------------------------------------------------------------- */
void BabyDevelop::kompilieren_alle()
{
	if(autoSpeichern == 1) {
		speichereListings();
	}

	this->meldungsFenster->clear();
	this->schreibeMeldungsfenster(">>> Alle Kompilieren <<<\n");

	this->arbeiter->start(ARBEITER_ALLE_KOMPILIEREN, this->projektVerzeichnis, "");
}


/* -------------------------------------------------------------------------- */
/* -------------------------------------------------- Bearbeiten - linken --- */
/* -------------------------------------------------------------------------- */
void BabyDevelop::linken()
{
	this->meldungsFenster->clear();
	this->schreibeMeldungsfenster(">>> Linken <<<\n");

	this->arbeiter->start(ARBEITER_LINKEN, this->projektVerzeichnis, "");
}


/* -------------------------------------------------------------------------- */
/* ------------------------------------------ Bearbeiten - run/ausfuehren --- */
/* -------------------------------------------------------------------------- */
void BabyDevelop::ausfuehren()
{
	this->meldungsFenster->clear();
	this->schreibeMeldungsfenster(">>> Ausfuehren <<<\n");

	this->arbeiter->start(ARBEITER_AUSFUEHREN, this->projektVerzeichnis, "");
}


/* -------------------------------------------------------------------------- */
/* ------------------------------------------ Bearbeiten - neuer Prototyp --- */
/* -------------------------------------------------------------------------- */
void BabyDevelop::neuPrototyp()
{
   eingabeZeile = new Eingabe_1(NULL,projektTyp);
   eingabeZeile->show();
   this->setDisabled(true);
   connect(eingabeZeile->klassenName, SIGNAL(returnPressed()), SLOT(neuPrototypOk()));
   connect(eingabeZeile->tasteOk, SIGNAL(clicked()), SLOT(neuPrototypOk()));
   connect(eingabeZeile->tasteAbbrechen, SIGNAL(clicked()), SLOT(neuPrototypAbbrechen()));
   connect(eingabeZeile, SIGNAL(abbruch()), SLOT(neuPrototypAbbrechen()));
}


/* ------------------------------.------------------------------------------- */
/*                               | neuPrototyp - Anteil [Abbrechen] gedrueckt */
/*                               '------------------------------------------- */
void BabyDevelop::neuPrototypAbbrechen()
{
   // eingabeZeile loeschen
   eingabeZeile->hide();
   QTimer::singleShot(200, this, SLOT(loescheEingabeZeile()));

   this->setEnabled(true);
}


/* ---------------------------------------.---------------------------------- */
/*                                        | neuPrototyp-Anteil [Ok] gedrueckt */
/*                                        '---------------------------------- */
void BabyDevelop::neuPrototypOk()
{
   QString kName=eingabeZeile->gibText();
   kName=kName.remove(" ");

   eingabeZeile->setEnabled(false);

   int status=pruefeNameVorhanden(kName);
   if(status==-1)
   {
      QMessageBox::critical( this ,landestext->getText("- Fehler -"), kName + landestext->getText(" schon vorhanden.<br>Waehlen Sie einen anderen Namen.") );

      // eingabeZeile loeschen
      eingabeZeile->hide();
      QTimer::singleShot(200, this, SLOT(loescheEingabeZeile()));

      this->setEnabled(true);
      return;
   }

   // eingabeZeile loeschen
   eingabeZeile->hide();
   QTimer::singleShot(200, this, SLOT(loescheEingabeZeile()));

   nKlassen++;
   klassenName[nKlassen]=kName;
   this->setEnabled(true);

   // Test auf erster Buchstabe Grossbuchstabe
   //------------------------------------------
   if(klassenName[nKlassen].left(1)!=klassenName[nKlassen].left(1).toLower())
   {
      QMessageBox::warning( this ,landestext->getText("- UML-Warnung -"), "Methoden/Funktionen sollen mit einem Kleinbuchstaben beginnen<br>korrigiere selbstaendig." );
   }

   // erster Buchstabe Kleinbuchstabe machen
   //----------------------------------------
   klassenName[nKlassen].left(1) = klassenName[nKlassen].left(1).toLower();


   //--- .c-Datei ---//
   //----------------//
   nListings++;
   bildeStruktur(klassenName[nKlassen]+".c");

   listing[nListings]->setPlainText(QString("/* ") + klassenName[nKlassen] + QString(".c */\n\n") +
                               QString("#include \"") + klassenName[nKlassen] + QString(".h\"\n\n") +
                               QString("void ") + klassenName[nKlassen] + QString(" ()\n") +
                               QString("{\n") +
                               QString("}\n"));

   // c-Datei speichern
   //-------------------
   QFile file_cpp( projektVerzeichnis + "/" + klassenName[nKlassen].toLower() + ".c" );
   if ( file_cpp.open( QIODevice::WriteOnly ) )
   {
      QTextStream stream( &file_cpp );
      stream << listing[nListings]->toPlainText();
      file_cpp.close();
   }


   //--- .h-Datei ---//
   //----------------//
   nListings++;
   bildeStruktur(klassenName[nKlassen]+".h");

   listing[nListings]->setPlainText(QString("/* ") + klassenName[nKlassen] + QString(".h */\n\n") +
                               QString("#ifndef "+klassenName[nKlassen].toUpper() + "_H\n") +
                               QString("#define "+klassenName[nKlassen].toUpper() + "_H\n\n") +
                               QString("#include <stdio.h>\n\n") +
                               QString("void " + klassenName[nKlassen] + "();\n\n") +
                               QString("#endif\n"));

   // h-Datei speichern
   //-------------------
   QFile file_h( projektVerzeichnis+"/" + klassenName[nKlassen]+".h" );
   if ( file_h.open( QIODevice::WriteOnly ) )
   {
      QTextStream stream( &file_h );
      stream << listing[nListings]->toPlainText();
      file_h.close();
   }

   klassenArt[nKlassen] = 0;   // 0=allgemeine Klasse

   rueckgabeWert=script("projektdatei");

   // Makefile anpassen
   //-------------------
   this->Makefile();

   // Menuestatus
   //-------------
   mbPrototypLoeschen->setEnabled( true );
}


/* -------------------------------------------------------------------------- */
/* ---------------------------------- Bearbeiten - neue allgemeine Klasse --- */
/* -------------------------------------------------------------------------- */
void BabyDevelop::neueKlasse()
{
   eingabeZeile = new Eingabe_1(NULL, projektTyp);
   eingabeZeile->show();
   this->setDisabled(true);
   connect(eingabeZeile->klassenName, SIGNAL(returnPressed()), SLOT(neueKlasseOk()));
   connect(eingabeZeile->tasteOk, SIGNAL(clicked()), SLOT(neueKlasseOk()));
   connect(eingabeZeile->tasteAbbrechen, SIGNAL(clicked()), SLOT(neueKlasseAbbrechen()));
   connect(eingabeZeile, SIGNAL(abbruch()), SLOT(neueKlasseAbbrechen()));
}


/* -------------------.------------------------------------------------------ */
/*                    | neue allgemeine Klasse - Anteil [Abbrechen] gedrueckt */
/*                    '------------------------------------------------------ */
void BabyDevelop::neueKlasseAbbrechen()
{
   // eingabeZeile loeschen
   eingabeZeile->hide();
   QTimer::singleShot(200, this, SLOT(loescheEingabeZeile()));

   this->setEnabled(true);
}


/* ----------------------------------------.--------------------------------- */
/*                             | neue allgemeine Klasse-Anteil [Ok] gedrueckt */
/*                             | allgemeine C++-Klasse                        */
/*                             '--------------------------------------------- */
void BabyDevelop::neueKlasseOk()
{
   QString kName=eingabeZeile->gibText();
   kName=kName.remove(" ");
   eingabeZeile->setEnabled(false);

   if(kName=="")
   {
      QMessageBox::critical( this ,landestext->getText("- Fehler -"), "Sie haben keinen Namen eingegeben.<br>Geben Sie einen Namen ein." );

      // eingabeZeile loeschen
      eingabeZeile->hide();
      QTimer::singleShot(200, this, SLOT(loescheEingabeZeile()));

      this->setEnabled(true);
      return;
   }

   int status=pruefeNameVorhanden(kName);
   if(status==-1)
   {
      QMessageBox::critical( this ,landestext->getText("- Fehler -"), kName + landestext->getText(" schon vorhanden.<br>Waehlen Sie einen anderen Namen.") );

      // eingabeZeile loeschen
      eingabeZeile->hide();
      QTimer::singleShot(200, this, SLOT(loescheEingabeZeile()));

      this->setEnabled(true);
      return;
   }

   // eingabeZeile loeschen erst am Ende der Funktion

   nKlassen++;
   klassenName[nKlassen]=kName;
   this->setEnabled(true);

   // Test auf erster Buchstabe Grossbuchstabe
   //------------------------------------------
   if(klassenName[nKlassen].left(1)!=klassenName[nKlassen].left(1).toUpper())
   {
      QMessageBox::warning( this ,landestext->getText("- UML-Warnung -"), landestext->getText("Eine Klasse soll mit einem Grossbuchstaben beginnen.<br>(Korrigiere selbstaendig)") );
   }

   // erster Buchstabe Grossbuchstabe machen
   //----------------------------------------
   if(klassenName[nKlassen].length()>1)
   {
      klassenName[nKlassen] = klassenName[nKlassen].left(1).toUpper()+klassenName[nKlassen].mid(1);
   }
   else
   {
      klassenName[nKlassen] = klassenName[nKlassen].toUpper();
   }

   //--- ...cpp-Datei ---//
   //--------------------//
   nListings++;
   bildeStruktur(klassenName[nKlassen].toLower()+".cpp");

   listing[nListings]->setPlainText(QString("/* ") + klassenName[nKlassen].toLower() + QString(".cpp */\n\n") +
                               QString("#include \"") + klassenName[nKlassen].toLower() + QString(".h\"\n\n") +
                               QString("/* Konstruktor */\n") +
                               klassenName[nKlassen] + QString("::") + klassenName[nKlassen] + QString("()\n") +
                               QString("{\n") +
                               QString("}\n\n") +
                               QString("/* Destruktor */\n") +
                               klassenName[nKlassen] + QString("::~") + klassenName[nKlassen] + QString("()\n") +
                               QString("{\n") +
                               QString("}\n"));

   // cpp-Datei speichern
   //---------------------
   QFile file_cpp( projektVerzeichnis+"/"+klassenName[nKlassen].toLower()+".cpp" );
   if ( file_cpp.open( QIODevice::WriteOnly ) )
   {
      QTextStream stream( &file_cpp );
      stream << listing[nListings]->toPlainText();
      file_cpp.close();
   }

   //--- ...h-Datei ---//
   //------------------//
   nListings++;
   bildeStruktur(klassenName[nKlassen].toLower()+".h");

   listing[nListings]->setPlainText(QString("/* ") + klassenName[nKlassen].toLower() + QString(".h */\n\n") +
                               QString("#ifndef "+klassenName[nKlassen].toUpper() + "_H\n") +
                               QString("#define "+klassenName[nKlassen].toUpper() + "_H\n\n") +
                               QString("#include <stdio.h>\n") +
                               QString("#include <stdlib.h>\n") +
                               QString("#include <iostream>\n") +
                               QString("using namespace std;\n\n") +
                               QString("class " + klassenName[nKlassen] + "\n") +
                               QString("{\n") +
                               QString("public:\n") +
                               QString("   ") + klassenName[nKlassen] + QString("();  /* Konstruktor */\n") +
                               QString("  ~") + klassenName[nKlassen] + QString("();  /* Destruktor  */\n") +
                               QString("};\n\n") +
                               QString("#endif\n"));

   // h-Datei speichern
   //-------------------
   QFile file_h( projektVerzeichnis+"/"+klassenName[nKlassen].toLower()+".h" );
   if ( file_h.open( QIODevice::WriteOnly ) )
   {
      QTextStream stream( &file_h );
      stream << listing[nListings]->toPlainText();
      file_h.close();
   }

   klassenArt[nKlassen] = 0;   // 0=allgemeine Klasse

   rueckgabeWert=script("projektdatei");

   // eingabeZeile loeschen
   eingabeZeile->hide();
   QTimer::singleShot(200, this, SLOT(loescheEingabeZeile()));

   // Makefile anpassen
   //-------------------
   this->Makefile();

   // Menuestatus
   //-------------
   mbKlasseLoeschen->setEnabled( true );

}


/* -------------------------------------------------------------------------- */
/* ------------------------------------------ Bearbeiten - neue Qt-Klasse --- */
/* -------------------------------------------------------------------------- */
void BabyDevelop::neueQtKlasse()
{
   eingabeZeile = new Eingabe_1(NULL,projektTyp);
   eingabeZeile->show();
   this->setDisabled(true);
   connect(eingabeZeile->klassenName, SIGNAL(returnPressed()), SLOT(neueQtKlasseOk()));
   connect(eingabeZeile->tasteOk, SIGNAL(clicked()), SLOT(neueQtKlasseOk()));
   connect(eingabeZeile->tasteAbbrechen, SIGNAL(clicked()), SLOT(neueQtKlasseAbbrechen()));
   connect(eingabeZeile, SIGNAL(abbruch()), SLOT(neueQtKlasseAbbrechen()));
}


/* -----------------------------.-------------------------------------------- */
/*                              | neueQtKlasse - Anteil [Abbrechen] gedrueckt */
/*                              '-------------------------------------------- */
void BabyDevelop::neueQtKlasseAbbrechen()
{
   // eingabeZeile loeschen
   eingabeZeile->hide();
   QTimer::singleShot(200, this, SLOT(loescheEingabeZeile()));
   
   this->setEnabled(true);
}


/* ------------------------------------.------------------------------------- */
/*                                     | neueQtKlasse - Anteil [Ok] gedrueckt */
/*                                     '------------------------------------- */
void BabyDevelop::neueQtKlasseOk()
{
   QString kName=eingabeZeile->gibText();
   kName=kName.remove(" ");
   eingabeZeile->setEnabled(false);

   if(kName=="")
   {
      QMessageBox::critical( this ,landestext->getText("- Fehler -"), "Sie haben keinen Namen eingegeben.<br>Geben Sie einen Namen ein." );

      // eingabeZeile loeschen
      eingabeZeile->hide();
      QTimer::singleShot(200, this, SLOT(loescheEingabeZeile()));

      this->setEnabled(true);
      return;
   }

   int status=pruefeNameVorhanden(kName);
   if(status==-1)
   {
      QMessageBox::critical( this ,landestext->getText("- Fehler -"), kName + " schon vorhanden.<br>Waehlen Sie einen anderen Namen." );

      // eingabeZeile loeschen
      eingabeZeile->hide();
      QTimer::singleShot(200, this, SLOT(loescheEingabeZeile()));

      this->setEnabled(true);
      return;
   }

   // eingabeZeile loeschen
   eingabeZeile->hide();
   QTimer::singleShot(200, this, SLOT(loescheEingabeZeile()));

   nKlassen++;
   klassenName[nKlassen]=kName;
   this->setEnabled(true);

   // Test auf erster Buchstabe Grossbuchstabe
   //------------------------------------------
   if(klassenName[nKlassen].left(1)!=klassenName[nKlassen].left(1).toUpper())
   {
      QMessageBox::warning( this ,landestext->getText("- UML-Warnung -"), landestext->getText("Eine Klasse soll mit einem Grossbuchstaben beginnen.<br>(Korrigiere selbstaendig)") );
   }

   // erster Buchstabe Grossbuchstabe
   //---------------------------------
   if(klassenName[nKlassen].length()>1)
   {
      klassenName[nKlassen]=klassenName[nKlassen].left(1).toUpper()+klassenName[nKlassen].mid(1);
   }
   else
   {
      klassenName[nKlassen]=klassenName[nKlassen].toUpper();
   }

   //--- ...cpp ---//
   //--------------//
   nListings++;
   bildeStruktur(klassenName[nKlassen].toLower()+".cpp");

   listing[nListings]->setPlainText(QString("/* ") + klassenName[nKlassen].toLower() + QString(".cpp */\n\n") +
                               QString("#include \"") + klassenName[nKlassen].toLower() + QString(".h\"\n\n") +
                               QString("/* Konstruktor */\n") +
                               klassenName[nKlassen] + QString("::") + klassenName[nKlassen] + QString("() : ProgrammFenster()\n") +
                               QString("{\n") +
                               QString("}\n\n") +
                               QString("/* Destruktor */\n") +
                               klassenName[nKlassen] + QString("::~") + klassenName[nKlassen] + QString("()\n") +
                               QString("{\n") +
                               QString("}\n"));

   // cpp-Datei speichern
   //---------------------
   QFile file_cpp( projektVerzeichnis+"/"+klassenName[nKlassen].toLower()+".cpp" );
   if ( file_cpp.open( QIODevice::WriteOnly ) )
   {
      QTextStream stream( &file_cpp );
      stream << listing[nListings]->toPlainText();
      file_cpp.close();
   }

   //--- ...h ---//
   //------------//
   nListings++;
   bildeStruktur(klassenName[nKlassen].toLower()+".h");

   listing[nListings]->setPlainText(QString("/* ") + klassenName[nKlassen].toLower() + QString(".h */\n\n") + \
                               QString("#ifndef " + klassenName[nKlassen].toUpper() + "_H\n") +
                               QString("#define " + klassenName[nKlassen].toUpper() + "_H\n\n") +
                               QString("#include \"" + bdpInstallVerzeichnis + "/babyDevelop/programmfenster.h\"\n\n") +
                               QString("class ") + klassenName[nKlassen] + QString(" : public ProgrammFenster\n") +
                               QString("{\n") +
                               QString("   Q_OBJECT\n") +
                               QString("public:\n") +
                               QString("   ") + klassenName[nKlassen] + QString("();   /* Konstruktor */\n") +
                               QString("  ~") + klassenName[nKlassen] + QString("();   /* Destruktor  */\n") +
                               QString("};\n\n") +
                               QString("#endif\n"));

   // h-Datei speichern
   //-------------------
   QFile file_h( projektVerzeichnis + "/" + klassenName[nKlassen].toLower() + ".h" );
   if ( file_h.open( QIODevice::WriteOnly ) )
   {
      QTextStream stream( &file_h );
      stream << listing[nListings]->toPlainText();
      file_h.close();
   }

   klassenArt[nKlassen] = 1;

   rueckgabeWert=script("projektdatei");

   // Makefile anpassen
   //-------------------
   this->Makefile();

   // Menuestatus
   //-------------
   mbKlasseLoeschen->setEnabled( true );
}


/* -------------------------------------------------------------------------- */
/* ------------------------------------ Bearbeiten - Prototyp importieren --- */
/* -------------------------------------------------------------------------- */
void BabyDevelop::prototypImportieren()
{
   // Verzeichnis und Klassenname waehlen
   //-------------------------------------
   QString fd = QFileDialog::getOpenFileName(this,landestext->getText("Prototypdeklaration oeffnen..."),QDir::homePath(),landestext->getText("PrototypDeklaration")+" (*.h)");
   if(fd.isEmpty()) // Abgebrochen
   {
      return;
   }

   QString kName=fd.mid(fd.lastIndexOf('/',-1)+1);   // ohne fuehrenden slash, mit Endung
   kName=kName.left(kName.lastIndexOf('.',-1));      // nur noch der KlassenName alleine

   int status=pruefeNameVorhanden(kName);
   if(status==-1)
   {
      QMessageBox::critical( this ,landestext->getText("- Fehler -"), kName + " schon vorhanden.<br>Waehlen Sie einen anderen Namen." );
      return;
   }

   QString dateiNameH=fd;   // mit Pfad
   if(dateiNameH.right(2)!=".h")
      dateiNameH+=".h";

   QString dateiNameCPP=dateiNameH.left(dateiNameH.length()-1)+"c";
   if( QFile::exists(dateiNameH.left(dateiNameH.length()-1)+"c") != true )
   {  // keine c-Datei gefunden
      QMessageBox::information( this ,landestext->getText("- Fehler -"), landestext->getText("Keine c-Datei gefunden.") );
      return;
   }

   // c- + h-Datei oeffnen
   //----------------------
   nKlassen++;
   QFile file_cpp(dateiNameCPP);
   if(!file_cpp.open(QIODevice::ReadOnly))
   {
      meldungsFenster->setPlainText( landestext->getText("Kann Datei") );
      meldungsFenster->setPlainText( meldungsFenster->toPlainText() + " " + dateiNameCPP );
      meldungsFenster->setPlainText( meldungsFenster->toPlainText() + " " + landestext->getText("nicht oeffnen.") );
      return;
   }
   klassenName[nKlassen]=kName;
   klassenArt[nKlassen]=0;   // allgemeine "Klasse"

   // c-Datei
   //---------
   nListings++;
   bildeStruktur(klassenName[nKlassen].toLower()+".c");

   QTextStream stream_cpp(&file_cpp);
   // cpp-Datei einlesen
   //--------------------
   listing[nListings]->setPlainText(stream_cpp.readAll());
   file_cpp.close();

   // c-Datei speichern p=Prototyp c=C-Datei
   //----------------------------------------
   QFile file_pc( projektVerzeichnis+"/"+klassenName[nKlassen].toLower()+".c" );
   if ( file_pc.open( QIODevice::WriteOnly ) )
   {
      QTextStream stream( &file_pc );
      stream << listing[nListings]->toPlainText();
      file_pc.close();
   }

   // h-Datei
   //---------
   nListings++;
   bildeStruktur(klassenName[nKlassen].toLower()+".h");

   QFile file_h(dateiNameH);
   if(!file_h.open(QIODevice::ReadOnly))
   {
      meldungsFenster->setPlainText( landestext->getText("Kann Datei") );
      meldungsFenster->setPlainText( meldungsFenster->toPlainText() + " " + dateiNameH );
      meldungsFenster->setPlainText( meldungsFenster->toPlainText() + " " + landestext->getText("nicht oeffnen.") );
      return;
   }
   QTextStream stream_h(&file_h);
   // h-Datei einlesen
   //------------------
   listing[nListings]->setPlainText(stream_h.readAll());
   file_h.close();

   // h-Datei speichern p=Prototyp h=h-Datei
   //----------------------------------------
   QFile file_ph( projektVerzeichnis+"/"+klassenName[nKlassen].toLower()+".h" );
   if ( file_ph.open( QIODevice::WriteOnly ) )
   {
      QTextStream stream( &file_ph );
      stream << listing[nListings]->toPlainText();
      file_ph.close();
   }

   // Kompilierscripte schreiben
   //----------------------------
   rueckgabeWert=script("projektdatei");

   // Makefile anpassen
   //-------------------
   this->Makefile();

   // Menuestatus
   //-------------
   mbPrototypLoeschen->setEnabled( true );
}


/* -------------------------------------------------------------------------- */
/* -------------------------------------- Bearbeiten - Klasse importieren --- */
/* -------------------------------------------------------------------------- */
void BabyDevelop::klasseImportieren()
{
   this->setEnabled(false);
   if(projektTyp==3)   // Qt-Projekt
   {
      importFenster = new Importieren(NULL);
      connect(importFenster->tasteOk, SIGNAL(clicked()), SLOT(importKlasseOk()));
      connect(importFenster->tasteAbbrechen, SIGNAL(clicked()), SLOT(importKlasseAbbrechen()));
      connect(importFenster, SIGNAL(abbruch()), SLOT(importKlasseAbbrechen()));
      importFenster->show();
   }
   else   // C++-Projekt
   {
      importKlasseOk();
   }
}


/* -----------------------.-------------------------------------------------- */
/*                        | Klasse importieren - Anteil [Abbrechen] gedrueckt */
/*                        '-------------------------------------------------- */
void BabyDevelop::importKlasseAbbrechen()
{
   // importFenster loeschen
   importFenster->hide();
   QTimer::singleShot(200, this, SLOT(loescheImportFenster()));
   this->setEnabled(true);
}


void BabyDevelop::loescheImportFenster()
{
   delete importFenster;
}


/* ------------------------------.------------------------------------------- */
/*                               | Klasse importieren - Anteil [Ok] gedrueckt */
/*                               '------------------------------------------- */
void BabyDevelop::importKlasseOk()
{
   if(projektTyp==3)   // Qt-Projekt
   {
      importFenster->setEnabled(false);
      kArt = importFenster->getAntwort();

      if(kArt<0)
      {
         QMessageBox::information( this, landestext->getText("Sie muessen die KlasserArt waehlen!"), landestext->getText("KlassenDeklaration") );
         importFenster->setEnabled(true);
         return;
      }
      // importFenster verstecken, spaeter loeschen mit
      // QTimer::singleShot(200, this, SLOT(loescheImportFenster()));
      importFenster->hide();
   }
   else   // C++-Projekt
   {
      kArt = 0;   // allgemeine Klasse
   }

   // Verzeichnis und Klassenname waehlen
   // der Klassenname wird aus dem Dateinamen ermittelt
   //---------------------------------------------------
   fd = QFileDialog::getOpenFileName(this, landestext->getText("Klassendeklaration oeffnen..."), QDir::homePath(), landestext->getText("KlassenDeklaration")+" (*.h)");
   if(fd.isEmpty())  // Abgebrochen
   {
      this->setEnabled(true);
      if(projektTyp==3)   // Qt-Projekt
      {
         QTimer::singleShot(200, this, SLOT(loescheImportFenster()));
      }
      return;
   }

   kName = fd.mid(fd.lastIndexOf('/',-1)+1);       // ohne fuehrenden slash, mit Endung
   kName = kName.left(kName.lastIndexOf('.',-1));  // nur noch der KlassenName alleine
   QString erster = kName.left(1).toUpper();       // erster Buchstabe Grossbuchstabe
   if(kName=="bug")      kName="BUG";      // kleine Gefaelligkeit
   if(kName=="bled")     kName="BLed";     // kleine Gefaelligkeit
   if(kName=="btabelle") kName="BTabelle"; // kleine Gefaelligkeit
   QString rest;
   if(kName.length()>1)
      rest = kName.mid(1);
   kName = erster+rest;

   // individuelle Gross-/Kleinschreibung ermoeglichen
   //--------------------------------------------------
   eingabeZeile = new Eingabe_1(0, 0);
   eingabeZeile->setzeText(kName);
   eingabeZeile->show();

   connect(eingabeZeile->tasteAbbrechen, SIGNAL(clicked()), SLOT(importKlassennameAbbrechen()));
   connect(eingabeZeile->tasteOk, SIGNAL(clicked()), SLOT(importKlassennameOk()));
   connect(eingabeZeile, SIGNAL(abbruch()), SLOT(importKlassennameAbbrechen()));
}


/* ------------------------.------------------------------------------------- */
/*                         | importKlassenname - Anteil [Abbrechen] gedrueckt */
/*                         '------------------------------------------------- */
void BabyDevelop::importKlassennameAbbrechen()
{
   // eingabeZeile loeschen
   eingabeZeile->hide();
   QTimer::singleShot(200, this, SLOT(loescheEingabeZeile()));

   if(projektTyp==3)   // Qt-Projekt
   {
      QTimer::singleShot(200, this, SLOT(loescheImportFenster()));
   }

   this->setEnabled(true);
}


void BabyDevelop::loescheEingabeZeile()
{
   delete eingabeZeile;
}


/* -------------------------------.------------------------------------------ */
/*                                | importKlassenname - Anteil [Ok] gedrueckt */
/*                                '------------------------------------------ */
void BabyDevelop::importKlassennameOk()
{
   kName = eingabeZeile->gibText();
   kArt = importFenster->getAntwort();

   // eingabeZeile loeschen
   eingabeZeile->hide();
   QTimer::singleShot(200, this, SLOT(loescheEingabeZeile()));

   // leeres Feld
   //-------------
   if(kName.length()<1)
   {
      QMessageBox::warning( this, landestext->getText("- Fehler -"), landestext->getText("Sie haben keinen Namen eingegeben.<br>Geben Sie einen Namen ein.") );
      this->setEnabled(true);
      if(projektTyp==3)   // Qt-Projekt
         QTimer::singleShot(200, this, SLOT(loescheImportFenster()));
      return;
   }

   // Test auf erster Buchstabe Grossbuchstabe
   //------------------------------------------
   if(kName.left(1)!=kName.left(1).toUpper())
   {
      QMessageBox::warning( this, landestext->getText("- UML-Warnung -"), landestext->getText("Eine Klasse soll mit einem Grossbuchstaben beginnen.<br>(Korrigiere selbstaendig)") );
   }

   // erster Buchstabe Grossbuchstabe
   //---------------------------------
   if(kName.length()>1)
   {
      kName = kName.left(1).toUpper()+kName.mid(1);
   }
   else
   {
      kName = kName.toUpper();
   }

   int status = pruefeNameVorhanden(kName);
   if(status==-1)
   {
      QMessageBox::critical(this, landestext->getText("- Fehler -"), kName + " schon vorhanden.<br>Waehlen Sie einen anderen Namen." );
      this->setEnabled(true);
      if(projektTyp==3)   // Qt-Projekt
         QTimer::singleShot(200, this, SLOT(loescheImportFenster()));
      return;
   }

   QString dateiNameH=fd;   // mit Pfad
   if(dateiNameH.right(2)!=".h")
      dateiNameH+=".h";

   QString dateiNameCPP=dateiNameH.left(dateiNameH.length()-1)+"cpp";

   if( QFile::exists(dateiNameH.left(dateiNameH.length()-1)+"cpp") != true )
   {  // keine cpp-Datei gefunden
      QMessageBox::critical( this, landestext->getText("- Fehler -"), landestext->getText("Keine cpp-Datei gefunden.") );
      this->setEnabled(true);
      if(projektTyp==3)   // Qt-Projekt
         QTimer::singleShot(200, this, SLOT(loescheImportFenster()));
      return;
   }

   // cpp + h oeffnen
   //-----------------
   nKlassen++;
   QFile file_cpp(dateiNameCPP);
   if(!file_cpp.open(QIODevice::ReadOnly))
   {
      this->setEnabled(true);
      meldungsFenster->setPlainText( landestext->getText("Kann Datei") );
      meldungsFenster->setPlainText( meldungsFenster->toPlainText() + " " + dateiNameCPP );
      meldungsFenster->setPlainText( meldungsFenster->toPlainText() + " " + landestext->getText("nicht oeffnen.") );
      if(projektTyp==3)   // Qt-Projekt
         QTimer::singleShot(200, this, SLOT(loescheImportFenster()));
      return;
   }
   klassenName[nKlassen] = kName;
   klassenArt[nKlassen]  = kArt;

   // cpp-Datei
   //-----------
   nListings++;
   bildeStruktur(klassenName[nKlassen].toLower()+".cpp");

   QTextStream stream_cpp(&file_cpp);

   // cpp-Datei einlesen
   //--------------------
   listing[nListings]->setPlainText(stream_cpp.readAll());
   file_cpp.close();

   // c-Datei speichern p=Prototyp c=C-Datei s=speichern
   //----------------------------------------------------
   QFile file_cpp_s( projektVerzeichnis+"/"+klassenName[nKlassen].toLower()+".cpp" );
   if ( file_cpp_s.open( QIODevice::WriteOnly ) )
   {
      QTextStream stream( &file_cpp_s );
      stream << listing[nListings]->toPlainText();
      file_cpp_s.close();
   }

   // h-Datei
   //---------
   nListings++;
   bildeStruktur(klassenName[nKlassen].toLower()+".h");

   QFile file_h(dateiNameH);
   if(!file_h.open(QIODevice::ReadOnly))
   {
      this->setEnabled(true);
      meldungsFenster->setPlainText( landestext->getText("Kann Datei") );
      meldungsFenster->setPlainText( meldungsFenster->toPlainText() + " " + dateiNameH.toLatin1().data() );
      meldungsFenster->setPlainText( meldungsFenster->toPlainText() + " " + landestext->getText("nicht oeffnen.") );
      if(projektTyp==3)   // Qt-Projekt
         QTimer::singleShot(200, this, SLOT(loescheImportFenster()));
      return;
   }
   QTextStream stream_h(&file_h);

   // h-Datei einlesen
   //------------------
   listing[nListings]->setPlainText(stream_h.readAll());
   file_h.close();

   // h-Datei speichern p=Prototyp h=h-Datei s=speichern
   //----------------------------------------------------
   QFile file_h_s( projektVerzeichnis+"/"+klassenName[nKlassen].toLower()+".h" );
   if ( file_h_s.open( QIODevice::WriteOnly ) )
   {
      QTextStream stream( &file_h_s );
      stream << listing[nListings]->toPlainText();
      file_h_s.close();
   }

   rueckgabeWert=script("projektdatei");

   // Makefile anpassen
   //-------------------
   this->Makefile();

   // Menuestatus
   //-------------
   mbKlasseLoeschen->setEnabled( true );

   if(projektTyp==3)   // Qt-Projekt
      QTimer::singleShot(200, this, SLOT(loescheImportFenster()));
   this->setEnabled(true);
}


/* -------------------------------------------------------------------------- */
/* --------------------------------------- Bearbeiten - Prototyp loeschen --- */
/* -------------------------------------------------------------------------- */
void BabyDevelop::loeschenPrototyp()
{
   QString zielDatei=tabulatorRahmen->tabText(tabulatorRahmen->currentIndex());
   zielDatei=zielDatei.left(zielDatei.lastIndexOf(".",-1));
   zielDatei=zielDatei.remove("[");   // Zeichen [ entfernen

   int aktive=tabulatorRahmen->currentIndex()+1;
   int zielreiter=aktive;   // um den Reitertext beim naechsten Klick richtig setzten zu koennen

   aktive=aktive-(aktive%2);   /* zeigt auf c-Datei der aktiven Klasse      */
                               /* h-Datei der Klasse hat einen Index hoeher */
                               /* main.cpp = 0                              */
                               /* basisklasse = 2                           */
                               /* erste eigen klasse = 4                    */

   if(aktive==0)   // main.cpp
   {
      QMessageBox::critical(this,landestext->getText("- Unsinnige Operation -"),landestext->getText("Die Datei main.cpp zu loeschen macht keinen Sinn!"));
      return;
   }

   // das ist falsch:   aktive+=3;   //zeigt jetzt auf das gewaehlte Listing
   // ab hier ist aktive >= 4, 6, 8, 10, ...

   // wirklich loeschen
   //-------------------
   if(QMessageBox::critical(this,landestext->getText("- Achtung: Loesche aktiven Prototyp -"),landestext->getText("Soll der Prototyp")+" "+zielDatei+" "+landestext->getText("geloescht werden?"),landestext->getText("Ja"),landestext->getText("Nein"),QString::null,0,1)==1)
   {
      return;
   }

   // h-, c-, usw.-Dateien loeschen
   //-------------------------------
   QFile file;
   file.remove(projektVerzeichnis+"/"+zielDatei+".c");
   file.remove(projektVerzeichnis+"/"+zielDatei+".h");
   file.remove(projektVerzeichnis+"/"+zielDatei+".o");
   file.remove(projektVerzeichnis+"/"+zielDatei+".sh");

   // Daten umschaufeln
   //-------------------
   int z=aktive;     // zeigt auf ersten (linken) Reiter der zu loeschenden Klasse
                     // also auf *.cpp-Datei

   if(z<nListings-2) // Fokus steht nicht auf letztem oder vorletztem Reiter
   {
      for(z=aktive; z<nListings-2; z=z+2)
      {
         listing[z]->setPlainText(listing[z+2]->toPlainText());
         tabulatorRahmen->setTabText(z,tabulatorRahmen->tabText(z+2));
         listing[z+1]->setPlainText(listing[z+3]->toPlainText());
         tabulatorRahmen->setTabText(z+1,tabulatorRahmen->tabText(z+3));
         klassenName[(z-2)/2+1] = klassenName[(z-2)/2+2];
         klassenArt[(z-2)/2+1] = klassenArt[(z-2)/2+2];
      }
   }

   lastReiterText=tabulatorRahmen->tabText(zielreiter);

   // die beiden hintersten loeschen
   //--------------------------------
   delete listing[z+1];
   delete tabulator[z+1];
   delete listing[z];
   delete tabulator[z];

   nKlassen -=1;
   nListings-=2;

   rueckgabeWert=script("projektdatei");   /* Projektdatei neu schreiben */

   // Makefile anpassen
   //-------------------
   this->Makefile();

   // Menuestatus
   //-------------
   if(nKlassen<1)
   {
      mbPrototypLoeschen->setEnabled( false );
   }
}


/* -------------------------------------------------------------------------- */
/* ----------------------------------------- Bearbeiten - Klasse loeschen --- */
/* -------------------------------------------------------------------------- */
void BabyDevelop::loeschenKlasse()
{
   QString zielDatei = tabulatorRahmen->tabText(tabulatorRahmen->currentIndex());
   zielDatei = zielDatei.left(zielDatei.lastIndexOf(".",-1));
   zielDatei = zielDatei.remove("[");   // Zeichen [ entfernen

   int aktive = tabulatorRahmen->currentIndex()+1;
   int zielreiter = aktive-1;    // um den Reitertext beim naechsten Klick richtig setzten zu koennen

   aktive = aktive-(aktive%2);   // zeigt auf cpp-Datei der Klasse
                               // h-Datei der Klasse hat einen Index hoeher
                               // main.cpp ergibt 0
                               // basisklasse ergibt 2
                               // erste  eigen Klasse ergibt 4
                               // zweite eigen Klasse ergibt 6

   if(aktive==0)   // main.cpp
   {
      QMessageBox::critical(this,landestext->getText("- Unsinnige Operation -"),landestext->getText("Die Datei main.cpp zu loeschen macht keinen Sinn!"));
      return;
   }
   if( (aktive==2)&&(projektTyp==3) )   //C++/Qt-Basisklasse
   {
      QMessageBox::critical(this,landestext->getText("- Unsinnige Operation -"),landestext->getText("Die Basisklasse zu loeschen macht keinen Sinn!"));
      return;
   }

   // das ist falsch:   aktive+=3;   //zeigt jetzt auf das gewaehlte Listing
   // ab hier ist aktive >= 4, 6, 8, 10, ...

   // wirklich loeschen
   //-------------------
   if(QMessageBox::critical(this,landestext->getText("- Achtung: Loesche aktive Klasse -"),landestext->getText("Soll die Klasse")+" "+zielDatei+" "+landestext->getText("geloescht werden?"),landestext->getText("Ja"),landestext->getText("Nein"),QString::null,0,1)==1)
   {
      return;
   }

   // h-, cpp-, usw.-Dateien loeschen
   //---------------------------------
   QFile file;
   file.remove(projektVerzeichnis+"/"+zielDatei+".cpp");

   if(klassenArt[aktive/2]==3)   // Qt-Klasse
   {
      file.remove(projektVerzeichnis+"/"+zielDatei+".moc.cpp");
      file.remove(projektVerzeichnis+"/"+zielDatei+".moc.o");
   }
   file.remove(projektVerzeichnis+"/"+zielDatei+".h");
   file.remove(projektVerzeichnis+"/"+zielDatei+".o");
   file.remove(projektVerzeichnis+"/"+zielDatei+".sh");

   // Daten umschaufeln
   //-------------------
   int z=aktive;     // zeigt auf ersten (linken) Reiter der zu loeschenden Klasse
                     // also auf *.cpp-Datei

   if(z<nListings-2) // Fokus steht nicht auf letztem oder vorletztem Reiter
   {
      for(z=aktive; z<nListings-2; z=z+2)
      {
         listing[z]->setPlainText(listing[z+2]->toPlainText());               // Programmlisting von cpp
         tabulatorRahmen->setTabText(z-1,tabulatorRahmen->tabText(z+1)); // Reitertext von cpp
         listing[z+1]->setPlainText(listing[z+3]->toPlainText());             // Programmlisting von h
         tabulatorRahmen->setTabText(z,tabulatorRahmen->tabText(z+2));   // Reitertext von h

         if(projektTyp==2)   // C++-
         {
            klassenName[(z-2)/2+1]=klassenName[(z-2)/2+2];
            klassenArt[(z-2)/2+1]=klassenArt[(z-2)/2+2];
         }
         else   // Qt-Projekt
         {
            klassenName[(z-2)/2]=klassenName[(z-2)/2+1];
            klassenArt[(z-2)/2]=klassenArt[(z-2)/2+1];
         }
      }
   }

   lastReiterText=tabulatorRahmen->tabText(zielreiter);

   // die beiden hintersten loeschen
   //--------------------------------
   delete listing[z+1];
   delete tabulator[z+1];
   delete listing[z];
   delete tabulator[z];

   nKlassen -=1;
   nListings-=2;

   rueckgabeWert=script("projektdatei");   // Projektdatei neu schreiben
  
   // Makefile anpassen
   //-------------------
   this->Makefile();

   // Menuestatus
   //-------------
   if(nKlassen<1)
   {
      mbKlasseLoeschen->setEnabled( false );
   }
}


/* -------------------------------------------------------------------------- */
/* ------------------------------------------- Bearbeiten - Einstellungen --- */
/* -------------------------------------------------------------------------- */
void BabyDevelop::einstellungen()
{
   // VariablenZustand sichern
   //--------------------------
   autoSpeichern_tmp     = autoSpeichern;      // ->user
   escape_tmp            = escape;             // ->user
   compilerFlags_tmp     = compilerFlags;      // ->projekt
   linkerFlags_tmp       = linkerFlags;        // ->projekt
   browserBefehl_tmp     = browserBefehl;      // ->user

   // Fenster erzeugen
   //------------------
   einstellungenFenster = new Einstellungen(NULL);
   connect(einstellungenFenster->tasteAbbrechen, SIGNAL(clicked()), SLOT(einstellungenAbbrechen()));
   connect(einstellungenFenster->tasteSpeichern, SIGNAL(clicked()), SLOT(einstellungenSpeichern()));

   if(projektTyp>0)
      einstellungenFenster->setNoProjekt(0);
   else
      einstellungenFenster->setNoProjekt(1);

   this->setEnabled(false);
   einstellungenFenster->show();
}


/* ----------------------------.--------------------------------------------- */
/*                             | Einstellungen - Anteil [Abbrechen] gedrueckt */
/*                             '--------------------------------------------- */
void BabyDevelop::einstellungenAbbrechen()
{
   this->setEnabled(true);
   delete einstellungenFenster;

   // VariablenZustand zuruecksichern
   //---------------------------------
   autoSpeichern = autoSpeichern_tmp;
   escape        = escape_tmp;
   compilerFlags = compilerFlags_tmp;
   linkerFlags   = linkerFlags_tmp;
   browserBefehl = browserBefehl_tmp;
}


/* ----------------------------.--------------------------------------------- */
/*                             | Einstellungen - Anteil [Speichern] gedrueckt */
/*                             '--------------------------------------------- */
void BabyDevelop::einstellungenSpeichern()
{
   einstellungenFenster->setEnabled(false);
   // drei getrennte .rc-Dateien
   //    1. /opt/babydevelop/babydevelop.rc
   //    2. im HomeVerzeichnis des Users .babydevelop_user.rc
   //    3. im ProjektVerzeichnis bdpProjekt.rc

   if( projektTyp>0 )   // dann ist ein Projekt geladen
   {
      compilerFlags = einstellungenFenster->compilerFlagsFeld->text();
      linkerFlags   = einstellungenFenster->linkerFlagsFeld->text();
      schreibeRCFile("projekt");
      speichereScripte();
   }

   browserBefehl=einstellungenFenster->browserFeld->text();
   schreibeRCFile("user");
   this->darstellung();

   delete einstellungenFenster;
   this->setEnabled(true);
}


/* -------------------------------------------------------------------------- */
/* ----------------------------------------------------------- Menue-Info --- */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* ---------------------------------------------- Info - UeberBabyDevelop --- */
/* -------------------------------------------------------------------------- */
void BabyDevelop::ueberBabyDevelop()
{
   QMessageBox::information( this ,"- BabyDevelop " + version + " - Info -", "Idee + (c) Ulrich F. Gehring (ufg)<br> \
      Special thx 2<br>          \
      - Jan Gehring<br>          \
      - Marcel Block<br>         \
      - Jonas Gehring<br>        \
      - Fernando Gallego Outon<br><br>Version: "+version+"<br><br> \
      http://babydevelop.sourceforge.net" );
}


/* -------------------------------------------------------------------------- */
/* ------------------------------------------ Info - Einfuehrung anzeigen --- */
/* -------------------------------------------------------------------------- */
void BabyDevelop::einfuehrung()
{
   QString tmp = browserBefehl + " " + bdpInstallVerzeichnis+(QString)"/babyDevelop/einfuehrung/einfuehrung.html &";
   system(tmp.toLatin1().data());
}


/* -------------------------------------------------------------------------- */
/* --------------------------------- Info - Projekteigenschaften anzeigen --- */
/* -------------------------------------------------------------------------- */
void BabyDevelop::projekteigenschaften()
{
   if(projektName!="")
   {
      meldungsFenster->setPlainText( (landestext->getText("Eigenschaften des geladenen Projekts") + "\n") );
      QString t = landestext->getText("ProjektName: ");
      t = t + projektName.toLatin1().data();
      meldungsFenster->setPlainText( meldungsFenster->toPlainText() + t + "\n");

      t = landestext->getText("ProjektVerzeichnis: ");
      t = t + projektVerzeichnis;
      meldungsFenster->setPlainText( meldungsFenster->toPlainText() + t + "\n");

      switch (projektTyp)
      {
         case 1: meldungsFenster->setPlainText( meldungsFenster->toPlainText() + "ProjektTyp: C\n"); break;
         case 2: meldungsFenster->setPlainText( meldungsFenster->toPlainText() + "ProjektTyp: C++\n"); break;
         case 3: meldungsFenster->setPlainText( meldungsFenster->toPlainText() + "ProjektTyp: Qt/C++\n"); break;
      }
      t = landestext->getText("Anzahl der Klassen = ");
      t = t + QString::number(nKlassen);
      meldungsFenster->setPlainText( meldungsFenster->toPlainText() + t + "\n");
      if(nKlassen>0)
         meldungsFenster->setPlainText( meldungsFenster->toPlainText() + landestext->getText("Auflistung der Klassen") + "\n");
      for(int z=0; z<nKlassen; z++)
      {
         if(klassenArt[z+1]==0)
         {
            t = klassenName[z+1];
            t = t + "   (" + landestext->getText("allgemeine Klasse") +")\n";
            meldungsFenster->setPlainText( meldungsFenster->toPlainText() + t );
         }
         else
         {
            t = klassenName[z+1];
            t = t + "   (" + landestext->getText("grafische Klasse") +")\n";
            meldungsFenster->setPlainText( meldungsFenster->toPlainText() + t );
         }
      }
   }
   else
   {
      meldungsFenster->setPlainText( landestext->getText("Kein Projekt geladen.") + "\n");
   }

}


/* -------------------------------------------------------------------------- */
/* ------------------------------------------- Info - ToDo-Liste anzeigen --- */
/* -------------------------------------------------------------------------- */
void BabyDevelop::todo()
{
   QString tmp = browserBefehl + " " + bdpInstallVerzeichnis+(QString)"/babyDevelop/StandDerDinge.txt &";
   system(tmp.toLatin1().data());
}


/* -------------------------------------------------------------------------- */
/* ----------------------------------------- Hilfe - BabyDevelop C-Hilfe --- */
/* -------------------------------------------------------------------------- */
void BabyDevelop::babyCHilfe()
{
   QString tmp = browserBefehl + " " + bdpInstallVerzeichnis+(QString)"/babyDevelop/einfuehrung/c/index_c.html &";
   system(tmp.toLatin1().data());
}


/* -------------------------------------------------------------------------- */
/* ----------------------------------------- Hilfe - BabyDevelop C++-Hilfe --- */
/* -------------------------------------------------------------------------- */
void BabyDevelop::babyCppHilfe()
{
   QString tmp = browserBefehl + " " + bdpInstallVerzeichnis + (QString)"/babyDevelop/einfuehrung/cpp/index_cpp.html &";
   system(tmp.toLatin1().data());
}


/* -------------------------------------------------------------------------- */
/* ----------------------------------------- Hilfe - BabyDevelop Qt-Hilfe --- */
/* -------------------------------------------------------------------------- */
void BabyDevelop::babyQtHilfe()
{
   QString tmp = browserBefehl + " " + bdpInstallVerzeichnis + (QString)"/babyDevelop/babyDevelopQtHilfe/babyDevelopQtHilfe.html &";
   system(tmp.toLatin1().data());
}


/* -------------------------------------------------------------------------- */
/* ----------------------------------------------------- Hilfe - Qt-Hilfe --- */
/* -------------------------------------------------------------------------- */
void BabyDevelop::qtHilfe()
{
   QString tmp = browserBefehl + " " + qtHilfePfadDatei + (QString)" &";
   system(tmp.toLatin1().data());
}


/* -------------------------------------------------------------------------- */
/* ---------------------------------------------- Hilfe - BabyDevelop FAQ --- */
/* -------------------------------------------------------------------------- */
void BabyDevelop::babyFAQ()
{
   QString tmp = browserBefehl + " " + bdpInstallVerzeichnis + (QString)"/babyDevelop/babyDevelopFAQ/faq.html &";
   system(tmp.toLatin1().data());
}


/* -------------------------------------------------------------------------- */
/* ------------------------------------------------- Hilfe - UFG-Designer --- */
/* -------------------------------------------------------------------------- */
void BabyDevelop::startDesigner()
{
   if(autoSpeichern == 1)
      speichereListings();
   int aktive = tabulatorRahmen->currentIndex() + 1;
   aktive = aktive-(aktive%2);   // zeigt auf cpp-Datei der Klasse
                               // h-Datei der Klasse hat einen Index hoeher
                               // main.cpp = 0
                               // basisklasse = 2
                               // erste eigen klasse = 4
   if(aktive==0)   // main.cpp
   {
      QMessageBox::critical(this, landestext->getText("- Unsinnige Operation -"), landestext->getText("In der main.cpp ein GUI zu implementieren macht keinen Sinn."));
      return;
   }

   designer = new UFGdesigner(NULL);

   // Objekte in Designer eintragen
   //-------------------------------
   QString zielDatei=tabulatorRahmen->tabText(tabulatorRahmen->currentIndex());
   zielDatei=zielDatei.remove("[");
   zielDatei=zielDatei.remove("]");
   zielDatei=zielDatei.left(zielDatei.lastIndexOf(".", -1));

   int status = designer->fuellen(projektVerzeichnis + "/" + zielDatei);
   if(status < 0) // Ein Fehler ist aufgetreten - Designer kann nicht gestartet werden
   {
      QString t = landestext->getText("Kann Designer nicht starten :-(") + "\n";
      t = t + landestext->getText("Die Struktur wurde veraendert!");
      t = t + "\n" + "(Fehler " + QString::number(status) + ")";
      QMessageBox::critical(this, landestext->getText("- Fehler -"), t);
      this->setEnabled(true);
      delete designer;
      return;
   }
   connect(designer->tasteBeenden, SIGNAL(clicked()), SLOT(designerBeenden()));
   connect(designer->tasteAbbrechen, SIGNAL(clicked()), SLOT(designerAbbrechen()));
   this->setEnabled(false);
   designer->show();
}


/* ---------------------------------.---------------------------------------- */
/*                                  | Designer - Anteil [Abbrechen] gedrueckt */
/*                                  '---------------------------------------- */
void BabyDevelop::designerAbbrechen()
{
   this->setEnabled(true);
   delete designer;
}


void BabyDevelop::loescheDesigner()
{
   delete designer;
}


/* -----------------------------------.-------------------------------------- */
/*                                    | Designer - Anteil [Beenden] gedrueckt */
/*                                    |                   und damit speichern */
/*                                    '-------------------------------------- */
int BabyDevelop::designerBeenden()
{
   // Objekte in h.- und .cpp-Datei eintragen
   //-----------------------------------------
   int anzahl=designer->getAnzahlObjekte();

   if(anzahl>0)         // Objekte wurden erzeugt
   {
      QString puffer;   // Puffer zum Umschaufeln

      QString zielDatei=tabulatorRahmen->tabText(tabulatorRahmen->currentIndex());
      zielDatei=zielDatei.remove("[");
      zielDatei=zielDatei.remove("]");
      zielDatei=zielDatei.left(zielDatei.lastIndexOf(".", -1));

      // .h einlesen bis /babyDevelop/programmfenster.h"
      //-------------------------------------------------
      QFile file_i(projektVerzeichnis + "/" + zielDatei + ".h");   // einlesen
      if(!file_i.open(QIODevice::ReadOnly))
      {
         meldungsFenster->setPlainText( landestext->getText("Kann Datei") );
         meldungsFenster->setPlainText( meldungsFenster->toPlainText() + " " + zielDatei + ".h" );
         meldungsFenster->setPlainText( meldungsFenster->toPlainText() + " " + landestext->getText("nicht oeffnen.") );
         return -1;
      }
      QTextStream stream_i(&file_i);

      // .h in /tmp puffern
      //--------------------
      //QFile file_o("/tmp/tmp.bdp");
      QFile file_o(projektVerzeichnis + "/" + zielDatei + ".temp");
      if(!file_o.open(QIODevice::WriteOnly))
      {
         meldungsFenster->setPlainText( landestext->getText("Kann Datei '"+projektVerzeichnis+"/"+zielDatei+".temp' nicht anlegen.") );
         return -1;
      }
      QTextStream stream_o(&file_o);

      // und los gehts
      //// /babyDevelop/programmfenster.h" suchen
      // programmfenster.h" suchen
      //---------------------------
      do
      {
         puffer = stream_i.readLine();
         stream_o << puffer << "\n";
      }while( ( puffer.lastIndexOf("#include \"", -1) < 0 )||( puffer.lastIndexOf("programmfenster.h\"", -1) < 0 ) );
//      }while( ( puffer.lastIndexOf("#include \"", -1)<0 )||( puffer.lastIndexOf("/babyDevelop/programmfenster.h\"",-1)<0 ) );

    // schon mal was geschrieben, dann Text: /* <UFGdesigner> */
    puffer = stream_i.readLine();   // Inhalt nicht vergessen
    int UFGdesignerIndikator = puffer.lastIndexOf("/* <UFGdesigner> */",-1);   // Designer-Eintrag oder Programmcode
    if(UFGdesignerIndikator!=-1)   // restliche #include_s einlesen bis /* </UFGdesigner> */
    {
          QString puffer2 = "";
          while(puffer2 != "/* </UFGdesigner> */")
          {
                puffer2 = stream_i.readLine();   // alte Eintraege interessieren nicht, da
                                                 // aktuelle designer-Objekte geschrieben werden
          }
    }
    stream_o << "/* <UFGdesigner> */" << "\n";

      /*----------------------*/
      /* #include_s schreiben */
      /*----------------------*/
      bool qlabelIndikator       = 0;
      bool qpushbuttonIndikator  = 0;
      bool qlineeditIndikator    = 0;
      bool bledIndikator         = 0;
      for(int z=1;z<=anzahl;z++)
      {
         int t = designer->getObjektTyp(z);
         switch(t)
         {
            case 1: if(qlabelIndikator == 0)                       // QLabel
                    {
                       stream_o << "#include <qlabel.h>" << "\n";
                       qlabelIndikator=1;
                    }
                    break;
            case 2: if(qpushbuttonIndikator == 0)                  // QPushButton
                    {
                       stream_o << "#include <qpushbutton.h>" << "\n";
                       qpushbuttonIndikator=1;
                    }
                    break;
            case 3: if(qlineeditIndikator == 0)                    // QLineEdit
                    {
                       stream_o << "#include <qlineedit.h>" << "\n";
                       qlineeditIndikator=1;
                    }
                    break;
            case 4: if(bledIndikator == 0)                         // BLed
                    {
                       stream_o << "#include \"bled.h\"" << "\n";
                       bledIndikator=1;
                    }
                    break;
         }
      }
      stream_o << "/* </UFGdesigner> */" << "\n";
      if(UFGdesignerIndikator == -1)
         stream_o << puffer << "\n";

    // .h weiter einlesen bis Destruktor
    // alles umschaufeln inkl. Konstruktor
    //-------------------------------------
      do
      {
         puffer = stream_i.readLine();
         stream_o << puffer << "\n";
      }while( puffer.toLower().lastIndexOf("~"+zielDatei,-1)<0 );

    // alte Eintraege interessieren nicht
    //------------------------------------
    if(UFGdesignerIndikator != -1)
      {
          QString puffer2 = "";
          while(puffer2 != "/* </UFGdesigner> */")
          {
                puffer2 = stream_i.readLine();   // alte Eintraege interessieren nicht,da
                                                 // aktuelle designer-Objekte geschrieben werden
          }
      }

      // Designer-Deklarationen dazu (ObjektKlasse*) z.B. QLabel *txt;
      //---------------------------------------------------------------
      stream_o << "/* <UFGdesigner> */" << "\n";
      for(int z=1;z<=anzahl;z++)
      {
         int t = designer->getObjektTyp(z);
         switch(t)
         {
            case 1: stream_o << "   QLabel* ";      break;
            case 2: stream_o << "   QPushButton* "; break;
            case 3: stream_o << "   QLineEdit* ";   break;
            case 4: stream_o << "   BLed* ";        break;
         }

      // Objektname dazu
      //-----------------
      stream_o << designer->getName(z) << ";\n";
      }
      stream_o << "/* </UFGdesigner> */" << "\n";

      // Rest von .h einlesen
      //----------------------
      do
      {
         puffer = stream_i.readLine();
         stream_o << puffer << "\n";
      }while(!stream_i.atEnd());
      file_i.close();
      file_o.close();

      //------------------------------------------------
      // aktiven Reiter ermitteln
      int aktive=tabulatorRahmen->currentIndex()+1;
      aktive=aktive-(aktive%2);   // zeigt auf cpp-Datei der Klasse
                                  // h-Datei der Klasse hat einen Index hoeher
                                  // main.cpp = 0
                                  // basisklasse = 2
                                  // erste eigen klasse = 4

      // .h umkopieren dazu erst in aktivem Reiter+1 laden
      //---------------------------------------------------
      //QFile file("/tmp/tmp.bdp");
      QFile file(projektVerzeichnis+"/"+zielDatei+".temp");
      if(!file.open(QIODevice::ReadOnly))
      {
         meldungsFenster->setPlainText( landestext->getText("Kann Datei '"+projektVerzeichnis+"/"+zielDatei+".temp' nicht oeffnen.") );
         return -1;
      }
      QTextStream stream(&file);

      // Datei einlesen d.h. Reiter neu fuellen
      //----------------------------------------
      listing[aktive+1]->setPlainText(stream.readAll());
      file.close();

      // .h-Datei speichern
      //--------------------
      QFile file_h( projektVerzeichnis+"/"+zielDatei+".h" );
      if ( file_h.open( QIODevice::WriteOnly ) )
      {
         QTextStream stream( &file_h );
         stream << listing[aktive+1]->toPlainText();
         file_h.close();
      }

      //-------------------------------------------------------
      // .cpp einlesen bis Konstruktor {
      //-------------------------------------------------------
      QFile file_ic(projektVerzeichnis+"/"+zielDatei+".cpp");   // einlesen
      if(!file_ic.open(QIODevice::ReadOnly))
      {
         meldungsFenster->setPlainText( landestext->getText("Kann Datei") );
         meldungsFenster->setPlainText( meldungsFenster->toPlainText() + " " + zielDatei + ".cpp" );
         meldungsFenster->setPlainText( meldungsFenster->toPlainText() + " " + landestext->getText("nicht oeffnen.") );
         return -1;
      }
      QTextStream stream_ic(&file_ic);

      // .cpp in /tmp puffern
      //----------------------
      //QFile file_oc("/tmp/tmp.bdp");
      QFile file_oc(projektVerzeichnis+"/"+zielDatei+".temp");
      if(!file_oc.open(QIODevice::WriteOnly))
      {
         meldungsFenster->setPlainText( landestext->getText("Kann Datei '"+projektVerzeichnis+"/"+zielDatei+".temp' nicht anlegen.") );
         return -1;
      }
      QTextStream stream_oc(&file_oc);

    // und los gehts
    // { suchen
    //---------------
      do
      {
         puffer = stream_ic.readLine();
         stream_oc << puffer << "\n";
      }while( puffer.lastIndexOf("{",-1)<0 );

    // schon mal was geschrieben, dann Text: /* <UFGdesigner> */
    //-----------------------------------------------------------
    puffer = stream_ic.readLine();   // Inhalt nicht vergessen, nur wenn Programmcode
    UFGdesignerIndikator = puffer.lastIndexOf("/* <UFGdesigner> */",-1);
    if(UFGdesignerIndikator!=-1)   // restliche Definitionen einlesen bis /* </UFGdesigner> */
      {
          QString puffer2 = "";
          while(puffer2 != "/* </UFGdesigner> */")
          {
                puffer2 = stream_ic.readLine();   // alte Eintraege interessieren nicht,da
                                                  // aktuelle designer-Objekte geschrieben werden
          }
      }

    stream_oc << "/* <UFGdesigner> */" << "\n";

      // zunaechst die Fenstergroesse
      //------------------------------
      stream_oc << "   this->setGeometry(";
                       stream_oc << designer->x() << "," << designer->y() << ",";
                       stream_oc << designer->width() << "," << designer->height() << ");" << "\n";

      // (neue) Objeknamen schreiben
      for(int z=1;z<=anzahl;z++)
      {
         stream_oc  << "\n";
         stream_oc << "   " << designer->getName(z) << " = new ";
         int t = designer->getObjektTyp(z);
         switch(t)
         {
            case 1: stream_oc << "QLabel(\"" << designer->getObjektText(z) << "\", this);" << "\n";
                    if(designer->farbe(z) != "keine")
                    {
                       stream_oc << "   " << designer->getName(z) << "->setPalette(" << designer->farbe(z) << ");" << "\n";
                       stream_oc << "   " << designer->getName(z) << "->setAutoFillBackground(true);\n";
                    }
                    break;
            case 2: stream_oc << "QPushButton(\"" << designer->getObjektText(z) << "\", this);" << "\n";
                    break;
            case 3: stream_oc << "QLineEdit(\"" << designer->getObjektText(z) << "\", this);" << "\n";
                    break;
            case 4: stream_oc << "BLed(this);" << "\n";
                    // Farbe der BLed z.B.: led->setColor(Qt::yellow);
                    stream_oc << "   " << designer->getName(z) << "->setColor(";
                    stream_oc << designer->getObjektText(z) << ");" << "\n"; // BLed hat als ObjektText die Farbe

/*
            case 4: stream_oc << "BLed(Q" << designer->getObjektText(z);
                       if(designer->getObjektText(z)=="t::re")     stream_oc << "d";
                       if(designer->getObjektText(z)=="t::yello")  stream_oc << "w";
                       if(designer->getObjektText(z)=="t::gree")   stream_oc << "n";
                       if(designer->getObjektText(z)=="t::blu")    stream_oc << "e";
                       if(designer->getObjektText(z)=="t::whit")   stream_oc << "e";
                       if(designer->getObjektText(z)=="t::blac")   stream_oc << "k";
                       if(designer->getObjektText(z)=="t::cya")    stream_oc << "n";
                       if(designer->getObjektText(z)=="t::magent") stream_oc << "a";
                       if(designer->getObjektText(z)=="t::gra")    stream_oc << "y";
                    stream_oc << ",this);" << "\n";
*/
                    break;
         }
         stream_oc << "   " << designer->getName(z) << "->setGeometry(";
            stream_oc << designer->objekt[z]->x() << "," << designer->objekt[z]->y() << ",";
            stream_oc << designer->objekt[z]->width() << "," << designer->objekt[z]->height() << ");" << "\n";
         stream_oc << "   " << designer->getName(z) << "->show();" << "\n";
      }
      stream_oc << "\n/* </UFGdesigner> */" << "\n";
      if(UFGdesignerIndikator < 0)
         stream_oc << puffer << "\n";

      // Rest von .cpp einlesen
      //------------------------
      do
      {
         puffer = stream_ic.readLine();
         stream_oc << puffer << "\n";
      }while(!stream_ic.atEnd());
      file_ic.close();
      file_oc.close();

      // .cpp umkopieren dazu erst in aktivem Reiter laden
      //---------------------------------------------------
      //QFile file_c("/tmp/tmp.bdp");
      QFile file_c(projektVerzeichnis+"/"+zielDatei+".temp");
      if(!file_c.open(QIODevice::ReadOnly))
      {
         meldungsFenster->setPlainText( landestext->getText("Kann Datei '"+projektVerzeichnis+"/"+zielDatei+".temp' nicht oeffnen.") );
         return -1;
      }
      QTextStream stream_c(&file_c);

      // Datei einlesen d.h. Reiter neu fuellen
      //----------------------------------------
      listing[aktive]->setPlainText(stream_c.readAll());
      file_c.close();

      // .cpp-Datei speichern
      //----------------------
      QFile file_cpp( projektVerzeichnis+"/"+zielDatei+".cpp" );
      if ( file_cpp.open( QIODevice::WriteOnly ) )
      {
         QTextStream stream_cpp( &file_cpp );
         stream_cpp << listing[aktive]->toPlainText();
         file_cpp.close();
      }

      // tmp-Dateien loeschen
      //----------------------
      QFile file_tmp;
      file_tmp.remove(projektVerzeichnis+"/"+zielDatei+".temp");
   }

   this->setEnabled(true);
   // Designer loeschen
   designer->hide();
   QTimer::singleShot(200, this, SLOT(loescheDesigner()));
   return 0;
}


/* -------------------------------------------------------------------------- */
/* ----------------------------------------------------- Hilfe - Debugger --- */
/* -------------------------------------------------------------------------- */
void BabyDevelop::startDebugger()
{
    QString binary = this->projektName;
    if(binary.indexOf(".") != -1) {
        binary = binary.left(binary.indexOf("."));
    }

    debugger = new Debugger(NULL, this->meldungsFenster, this->projektTyp, this->projektVerzeichnis, binary);
    debugger->show();

    mpNeu                 ->setEnabled( false );
    mpOeffnen             ->setEnabled( false );
    mpSpeichern           ->setEnabled( false );
    mpSpeichernUnter      ->setEnabled( false );
    mpDateiSpeichern      ->setEnabled( false );
    mpSchliessen          ->setEnabled( false );
    mbRundschlag          ->setEnabled( false );
    mbKompilieren         ->setEnabled( false );
    mbLinken              ->setEnabled( false );
    mbAusfuehren          ->setEnabled( false );
    mbAlleKompilieren     ->setEnabled( false );
    mbNeuerPrototyp       ->setEnabled( false );
    mbNeueAllgemeineKlasse->setEnabled( false );
    mbNeueGrafischeKlasse ->setEnabled( false );
    mbPrototypImportieren ->setEnabled( false );
    mbKlasseImportieren   ->setEnabled( false );
    mbPrototypLoeschen    ->setEnabled( false );
    mbKlasseLoeschen      ->setEnabled( false );
    mhGUIDesigner         ->setEnabled( false );
    mhDebugger            ->setEnabled( false );

    connect(debugger, SIGNAL(beendeDebugger()), SLOT(debuggerBeenden()));
    connect(debugger, SIGNAL(springeZeile(QString, QString)), SLOT(zeileMarkieren(QString, QString)));

    statusDebugger = 1;
}


void BabyDevelop::zeileMarkieren(QString file, QString line)
{
	// Zahl in eine "int" mit Basis 10 konvertieren und ok-Flag setzen bzw. loeschen
	//-------------------------------------------------------------------------------
	bool ok = false;
	int nLine = line.toInt(&ok, 10); // Nummer der fehlerbehafteten Zeile
	if(ok == false) // da stimmt was nich :)
		return;

	//////////////////////////////////////////////////
	// Reiter mit dem fehlerhaften Listing suchen
	int tabs = this->tabulatorRahmen->count(); // Anzahl Reiter

	int i;
	bool found = false;
	for(i=0; i<tabs; i++)
	{
		QString l = tabulatorRahmen->tabText(i);

		if((l == file) || (l == "["+file+"]"))
		{ // gefunden?
			found = true;
			break;
		}
	}

	//////////////////////////////////////////////////
	// Stelle markieren
	if(found == true)
	{
		///////////////////////////////
		// Alte Markierung entfernen //
		///////////////////////////////
		if(fehleranzeige == 1) {
			// Auf einen anderen Fehler geklickt
			// also zunaechst die letzte Markierung wieder loeschen = Originalformat aktivieren
			// mb: alte markierung nicht im reiter 'i' sondern im 'fehler_reiter' entfernen
			QTextCursor _cl = listing[fehler_reiter+1]->textCursor();
			_cl.setPosition(fehler_start_pos, QTextCursor::MoveAnchor); // Zeile ganz nach vorne
			_cl.setPosition(fehler_ende_pos, QTextCursor::KeepAnchor);  // Zeile ganz nach hinten
			_cl.setCharFormat(format_original);                         // Originalformat einschalten
			_cl.setPosition(fehler_ende_pos, QTextCursor::MoveAnchor);
			listing[fehler_reiter+1]->setTextCursor(_cl);               // Originalformat wieder aktivieren
		}

		//////////////////////////////////
		// Jetzt neue Markierung setzen //
		//////////////////////////////////
		this->tabulatorRahmen->setCurrentIndex(i); 							// Reiter aktivieren

		QTextCursor cl = listing[i+1]->textCursor();
		cl.clearSelection(); 												// Alle "anchor" aufheben
		cl.setPosition(0); 													// Erste Zeile ganz nach vorne

		cl.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, nLine-1);	// Cursoer runterscrollen
		fehler_start_pos = cl.position();									// Startposition des Markierten Textes
		cl.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);	// Cursor ans Zeilenende
		fehler_ende_pos = cl.position();									// Endeposition des Markierten Textes
		fehler_reiter = i;													// mb: merken in welchem reiter die markierung gemacht wurde

		QTextCharFormat format = format_original;							// aktuelles Format
		format.setBackground(Qt::red);										// Papierfarbe rot
		cl.setCharFormat(format);											// Format einschalten

		cl.clearSelection();												// mb: selektion entfernen
		listing[i+1]->setTextCursor(cl);									// Format aktivieren

		fehleranzeige = 1; 													// d.h. es wurde auf Fehler doppelklick gemacht
	}
}


/* ------------------------------------------.------------------------------- */
/*                                           | Debugger - [Beenden] gedrueckt */
/*                                           '------------------------------- */
void BabyDevelop::debuggerBeenden()
{
   delete debugger;
   statusDebugger = 0;

   mpNeu                   ->setEnabled( true );
   mpOeffnen               ->setEnabled( true );
   mpSpeichern             ->setEnabled( true );
   mpSpeichernUnter        ->setEnabled( true );
   mpDateiSpeichern        ->setEnabled( true );
   mpSchliessen            ->setEnabled( true );
   mbRundschlag            ->setEnabled( true );
   mbKompilieren           ->setEnabled( true );
   mbLinken                ->setEnabled( true );
   mbAusfuehren            ->setEnabled( true );
   mbAlleKompilieren       ->setEnabled( true );
   if((projektTyp==1)||(projektTyp==4))
      mbNeuerPrototyp      ->setEnabled( true );
   mbNeueAllgemeineKlasse  ->setEnabled( true );
   if(projektTyp==3)
      mbNeueGrafischeKlasse->setEnabled( true );
   if((projektTyp==1)||(projektTyp==4))
      mbPrototypImportieren->setEnabled( true );
   if((projektTyp==2)||(projektTyp==3)||(projektTyp==5))
      mbKlasseImportieren  ->setEnabled( true );
   if(((projektTyp==1)||(projektTyp==4))&&(nKlassen>0))
      mbPrototypLoeschen   ->setEnabled( true );
   if(((projektTyp==3)||(projektTyp==5))&&(nKlassen>0))
      mbKlasseLoeschen     ->setEnabled( true );
   if(projektTyp==3)
      mhGUIDesigner        ->setEnabled( true );
   mhDebugger              ->setEnabled( true );
}


/* -------------------------------------------------------------------------- */
/* ---------------------------------------- Hilfsfunktionen/Hilfsmethoden --- */
/* -------------------------------------------------------------------------- */


/* -------------------------------------------------------------------------- */
/* ------------------------ Schon ein Projekt geladen ->alle Objekte loeschen */
/* -------------------------------------------------------------------------- */
void BabyDevelop::deleteAll()
{
   for(int z=2;z<nListings+1;z++)
   {
      delete listing[z];
      delete tabulator[z];
   }
   projektName       = "";

// QFile fileu( QDir::homePath()+"/.babydevelop_user.rc" );

   projektVerzeichnis= (QString)QDir::homePath();
   compilerFlags     = "";
   linkerFlags       = "";
   nListings         = 1;
   nKlassen          = 0;
   tabulatorRahmen->setTabText( nListings, QString("-/-") );
   listing[nListings]->setPlainText(landestext->getText("Kein Projekt geladen."));
   listing[nListings]->setPlainText(listing[nListings]->toPlainText()+"\n\n\n\n\n\n"+
"                   ____        _           ____                 _"+"\n"+
"                  | __ )  __ _| |__  _   _|  _ \\  _____   _____| | ___  _ __"+"\n"+
"                  |  _ \\ / _` | |_ \\| | | | | | |/ _ \\ \\ / / _ \\ |/ _ \\|  _ \\"+"\n"+
"                  | |_) | (_| | |_) | |_| | |_| |  __/\\ V /  __/ | (_) | |_) |"+"\n"+
"                  |____/ \\__,_|_.__/ \\__, |____/ \\___| \\_/ \\___|_|\\___/| .__/"+"\n"+
"                                     |___/                             |_|"+version);



   projektTyp = 0;   // 0 = kein Projejt geladen
   escape     = 0;

   // deaktivieren von Signal currentChanged
   //----------------------------------------
   disconnect(tabulatorRahmen, SIGNAL(currentChanged(QWidget*)));
   lastReiterText="";
}


/* -------------------------------------------------------------------------- */
/* ----------------- Script zum ausfuehren und projektdatei erzeugen --- */
/* -------------------------------------------------------------------------- */


/* ---------------------------------------.---------------------------------- */
/*        | Kompilierscript fuer Projektdatei      -> projektdatei            */
/*        '------------------------------------------------------------------ */
int BabyDevelop::script(QString variante)
{
   if(variante=="projektdatei")   /* ----------------.----------------------- */
                                  /*                 | Projektdatei schreiben */
                                  /*                 '----------------------- */
   {
      QFile file_bdp( projektVerzeichnis+"/"+projektName.toLower()+".bdp" );
      if(!file_bdp.open(QIODevice::WriteOnly))
      {
         meldungsFenster->setPlainText( landestext->getText("Kann Datei") );
         meldungsFenster->setPlainText( meldungsFenster->toPlainText() + " " + projektName.toLower() + ".bdp" );
         meldungsFenster->setPlainText( meldungsFenster->toPlainText() + " " + landestext->getText("nicht anlegen.") );
         return -1;
      }
      QTextStream stream(&file_bdp);
      stream << "BabyDevelop-Projektdatei\n";
      stream << "ProjektName=";
         stream << projektName;
         stream << "\n";
      stream << "ProjektTyp=";
         stream << QString::number(projektTyp);
         stream << "\n";
      stream << "nKlassen=" + QString::number(nKlassen) + "\n";

      // Eintraege fuer Klassen
      //------------------------
      if(nKlassen>0)
      {
         for(int z=1; z<=nKlassen; z++)
         {
            stream << "KlassenName" + QString::number(z) + "=" + klassenName[z] + "\n";
            stream << "KlassenArt" + QString::number(z) + "=" + QString::number(klassenArt[z]) + "\n";
         }
      }

      file_bdp.close();
   }


   if(variante=="ausfuehren")   /* ------------------.------------------ */
                                /*                   | ausfuehren-Script */
                                /*                   '------------------ */
   {
      QFile file_a_sh( projektVerzeichnis+"/ausfuehren.sh" );

      if(!file_a_sh.open(QIODevice::WriteOnly))
      {
         meldungsFenster->setPlainText( landestext->getText("Kann Datei ausfuehren.sh nicht anlegen.") );
         return -1;
      }

      QTextStream stream_a_sh( &file_a_sh );

      stream_a_sh << "#!/bin/sh\n\n";
      stream_a_sh << "./" << projektName.toLower();
      stream_a_sh << "\n";
      file_a_sh.close();
   }

   return 0;
}



/********************************************************/
/* Erzeugt ein Makefile fuer das aktuelle Projekt       */
/* Sollte aufgerufen werden                             */
/* - beim Anlegen eines neuen Projekts                  */
/* - beim Erzeugen/Importieren neuer Prototypen/Klassen */
/* - beim Löschen von Prototypen/Klassen                */
/* - usw.                                               */
/* damit das Makefile stets auf dem neusten Stand ist.  */
/********************************************************/
int BabyDevelop::Makefile(void)
{
	QString cc, ld, qtdir, moc, rm, run, cflags, ldflags, programmfenster_objekte, libs, objects, binary;
	int i;

	/*******************************/
	/* Kompiler-Optionen bestimmen */
	/*******************************/
	switch(this->projektTyp)
	{
		case 1: /* C */
		{
			cc		  = "gcc";
			ld		  = "gcc";
			cflags  = "-c -Wall -g " + compilerFlags;
			ldflags = linkerFlags;
			libs	  = "";
         programmfenster_objekte = "";
			break;
		}

		case 2: /* C++ */
		{
			cc		  = "g++";
			ld		  = "g++";
			cflags  = "-c -Wall -g " + compilerFlags;
			ldflags = linkerFlags;
			libs	  = "";
         programmfenster_objekte = "";
			break;
		}

		case 3: /* C++/Qt */
		{
			cc  = "g++";
			ld  = "g++";
			moc = "moc";

			#if defined(LINUX)
				cflags = "-c -Wall -g -I$(QTDIR) -I$(QTDIR)/Qt -I$(QTDIR)/QtCore -I$(QTDIR)/QtGui " + compilerFlags;
				ldflags	= "-L/usr/lib " + linkerFlags;
				libs	= "-lQtCore -lQtGui -lQt3Support";
            programmfenster_objekte = "/opt/babyDevelop/programmfenster.moc.o /opt/babyDevelop/programmfenster.o";
			#elif defined(WIN32)
				cflags	= "-c -Wall -g -I$(QTDIR)/include -I$(QTDIR)/include/Qt -I$(QTDIR)/include/QtCore -I$(QTDIR)/include/QtGui " + compilerFlags;
				ldflags	= "-L$(QTDIR)/lib " + linkerFlags;
				libs	= "-lQtCore4 -lQtGui4 -lQt3Support4";
            programmfenster_objekte = "C:\\opt\\babyDevelop\\programmfenster.moc.o C:\\opt\\babyDevelop\\programmfenster.o";
			#endif

			break;
		}

		default: /* gibts nicht */
		{
			qWarning("BabyDevelop::Makefile() unbekannter ProjektTyp %d!", this->projektTyp);
			return -1;
		}
	}

	#if defined(LINUX)
		rm  = "rm -f";
		run = "./$(BIN)";
	#elif defined(WIN32)
		rm  = "del";
		run = "$(BIN)";
	#endif

	/****************************************/
	/* Liste aller Objekt-Dateien bestimmen */
	/****************************************/
	objects = "main.o";

	if(this->projektTyp == 1 || this->projektTyp == 2) /* C oder C++ -> pro1.o, pro2.o, pro3.o, ... */
	{
		if(this->nKlassen > 0)
		{
			for(i=1; i<=(nListings-3)/2+1; i++)
			{
				objects += " ";
				objects += klassenName[i].toLower();
				objects += ".o";
			}
		}
	}

	else if(this->projektTyp == 3) /* C++/Qt */
	{
		// Basisklasse -> basis.o basis.moc.o
		objects += " ";
		objects += this->projektName.toLower();
		objects += ".o";

		objects += " ";
		objects += this->projektName.toLower();
		objects += ".moc.o";

		// eigene Klassen
		if(this->nKlassen > 0)
		{
			for(i=1; i<=(nListings-3)/2; i++) //Klassen durchzaehlen
			{
				// allgemeine und alle Klassen -> klasse.o
				objects += " ";
				objects += klassenName[i].toLower();
				objects += ".o";

				if(klassenArt[i] == 1) //Qt-Klasse zusaetzlich -> klasse.moc.o
				{
					// QtKlasse
					objects += " ";
					objects += klassenName[i].toLower();
					objects += ".moc.o";
				}
			}
		}
	}
	//qWarning("BabyDevelop::Makefile() objects = '%s'", objects.toAscii().constData());

	/*****************************/
	/* Name der Binary bestimmen */
	/* foobar.bdp     -> foobar  */
	/* foobar.bdp.bdp -> foobar  */
	/*****************************/
	binary = this->projektName;
	i = binary.indexOf(".");
	if(i != -1) {
		binary = binary.left(i);
	}

	#if defined(WIN32)
        binary += ".exe";
	#endif

	/********************************/
	/* Makefile anlegen und fuellen */
	/********************************/
	QFile file(projektVerzeichnis + "/Makefile");
	if(!file.open(QIODevice::WriteOnly))
	{
		this->meldungsFenster->clear();
		this->schreibeMeldungsfenster("Kann Datei \"" + projektVerzeichnis + "/Makefile" + "\" nicht anlegen!");
		return -1;
	}

	QTextStream stream(&file);

	stream << "# ---------------------------------\n";
	stream << "# Makefile for BabyDevelop projects\n";
	stream << "# ---------------------------------\n";
	stream << "\n";
	stream << "CC          = " + cc      + "\n";
	stream << "LD          = " + ld      + "\n";
	if(this->projektTyp == 3) //Qt-Projekt -> braucht moc
   {
      stream << "QTDIR       = " + QtDir + "\n"; //Globale Variable
      stream << "MOC         = " + moc   + "\n";
   }
	stream << "RM          = " + rm      + "\n";
	stream << "RUN         = " + run     + "\n";
	stream << "CFLAGS      = " + cflags  + "\n";
	stream << "LDFLAGS     = " + ldflags + "\n";
	stream << "LIBS        = " + libs    + "\n";
   stream << "PROGRAMMFENSTER_OBJ        = " + programmfenster_objekte    + "\n"; //braucht der Paedagoge
	stream << "\n";
	stream << "# ---------------------------------\n";
	stream << "OBJECTS     = " + objects + "\n";
	stream << "BIN         = " + binary  + "\n";
	stream << "# ---------------------------------\n";
	stream << "\n";
	stream << "all: clean $(OBJECTS) link\n";
	stream << "\n";
	stream << "clean:\n";

	if(this->projektTyp == 3){
		stream << "\t-$(RM) *.moc.cpp\n";
		stream << "\t-$(RM) *.moc.o\n";
	}

	stream << "\t-$(RM) *.o\n";
	stream << "\t-$(RM) $(BIN)\n";
	stream << "\n";
	stream << "compile_all: $(OBJECTS)\n";
	stream << "\n";
	stream << "link:\n";
	stream << "\t$(CC) $(OBJECTS) $(PROGRAMMFENSTER_OBJ) $(LDFLAGS) $(LIBS) -o $(BIN)\n";
	stream << "\n";

	if(this->projektTyp == 1) {
		stream << ".c.o:\n";
	}
	else if(this->projektTyp == 2 || this->projektTyp == 3) {
		stream << ".cpp.o:\n";
	}

	stream << "\t$(CC) $(CFLAGS) $<\n";
	stream << "\n";

	if(this->projektTyp == 3) {
		stream << "%.moc.cpp: %.h\n";
		stream << "\t$(MOC) -o $@ $<\n";
		stream << "\n";
		stream << "%.moc.o: %.moc.cpp\n";
		stream << "\t$(CC) $(CFLAGS) -o $@ $<\n";
		stream << "\n";
	}

	stream << "run:\n";
	stream << "\t$(RUN)\n";

	file.close();

	return 0;
}

void BabyDevelop::speichereScripte()
{
   // Makefile anpassen
   //-------------------
   this->Makefile();
}


/* -------------------------------------------------------------------------- */
/* ---------------------------------------------------- speichereListings --- */
/* -------------------------------------------------------------------------- */
void BabyDevelop::speichereListings()
{
   // alle Dateien speichern - 1. main.c|cpp = listing[1]
   //-----------------------------------------------------
   QString endung;
   if(projektTyp==1)
   {
      endung="c";
   }
   else
   {
      endung="cpp";
   }

   QFile file( projektVerzeichnis + "/main." + endung );
   if ( file.open( QIODevice::WriteOnly ) )
   {
      QTextStream stream( &file );
      stream << listing[1]->toPlainText();
      file.close();
   }

   if(projektTyp==3)   // Qt-Projekt
   {
      // alle Dateien speichern - 2. basisklasse.cpp = listing[2]
      //----------------------------------------------------------
      QFile file_cpp( projektVerzeichnis+"/"+projektName.toLower()+"."+endung );
      if ( file_cpp.open( QIODevice::WriteOnly ) )
      {
         QTextStream stream( &file_cpp );
         stream << listing[2]->toPlainText();
         file_cpp.close();
      }

      // alle Dateien speichern - 3. basisklasse.h = listing[3]
      //--------------------------------------------------------
      QFile file_h( projektVerzeichnis+"/"+projektName.toLower()+".h" );
      if ( file_h.open( QIODevice::WriteOnly ) )
      {
         QTextStream stream( &file_h );
         stream << listing[3]->toPlainText();
         file_h.close();
      }
   }

   if(nKlassen>0)
   {
      /*
         Qt-Anmerkung:  listing[2] ist BasisKlasse.cpp
                        listing[3] ist BasisKlasse.h
                        listing[4] ist die erste eigene Klasse.cpp
                        usw.
       C/C++-Anmerkung: listing[2] ist 1.Prototyp.c, 1.Klasse.cpp
                        listing[3] ist 1.Prototyp.h, 1.Klasse.h
                        listing[4] ist 2.Prototyp.c, 2.Klasse.cpp
                        usw.
      */
      int z=0;
      while(z<nKlassen)
      {
         z++;
         // alle KlassenDateien speichern - 2. *.c|cpp
         //--------------------------------------------
         QFile file_cc( projektVerzeichnis+"/"+klassenName[z].toLower()+"."+endung );
         if ( file_cc.open(QIODevice::WriteOnly ) )
         {
            QTextStream stream( &file_cc );
            if( projektTyp!=3 )   // C-, C++-Projekt
            {
               stream << listing[(z-1)*2+2]->toPlainText();
            }
            else   // Qt-Projekt
            {
               stream << listing[(z-1)*2+4]->toPlainText();
            }
            file_cc.close();
         }

         // alle KlassenDateien speichern - 3. *.h
         //----------------------------------------
         QFile file_hh( projektVerzeichnis+"/"+klassenName[z].toLower()+".h" );
         if ( file_hh.open( QIODevice::WriteOnly ) )
         {
            QTextStream stream( &file_hh );
            if( projektTyp!=3 )   // C-, C++-Projekt
            {
               stream << listing[(z-1)*2+3]->toPlainText();
            }
            else // Qt-Projekt
            {
               stream << listing[(z-1)*2+5]->toPlainText();
            }
            file_hh.close();
         }
      }
   }
}


/* -------------------------------------------------------------------------- */
/* ----------------------------------------- [ ] in aktivem Reiter setzen --- */
/* -------------------------------------------------------------------------- */
void BabyDevelop::reiterHervorheben(int reiter)
{
   if(lastReiterText!="")
   {
      tabulatorRahmen->setTabText(lastReiterObjektNr,lastReiterText);
   }
   else   // beim erstmaligen Aufruf der Methode war die main.c|cpp aktiv
   {
      QString text=tabulatorRahmen->tabText(0);
      text=text.remove("[");
      text=text.remove("]");
      tabulatorRahmen->setTabText( 0, text );
   }

   lastReiterText=tabulatorRahmen->tabText(tabulatorRahmen->currentIndex());
   lastReiterText=lastReiterText.remove("[");
   lastReiterText=lastReiterText.remove("]");
   lastReiterObjektNr=reiter;
   QString text;
   text = "[" + lastReiterText + "]";
   tabulatorRahmen->setTabText(lastReiterObjektNr,text);

}


/* -------------------------------------------------------------------------- */
/* ------------------------------------------ Tabulator-Strukturen bilden --- */
/* -------------------------------------------------------------------------- */
void BabyDevelop::bildeStruktur(QString reiterText)
{
   // file:///usr/share/doc/qt4-doc-html/html/qhboxlayout.html
   //----------------------------------------------------------

   tabulator[nListings]  = new QWidget( tabulatorRahmen ); // neuer Tabulator

   // Variante ohne/mit BEdit----------------------------------------------------------
   // Editor-Fenster
   //listing[nListings] = new QTextEdit(tabulator[nListings]); // neuer Editor im neuen Tabulator
   listing[nListings] = new CodeEditor(tabulator[nListings]);     // neuer Editor im neuen Tabulator
   //----------------------------------------------------------------------------------

   if(zeilenumbruch==0)
      listing[nListings]->setWordWrapMode(QTextOption::NoWrap);

   listingBox = new QHBoxLayout(); // enthaelt das Listing-Fenster

   listingBox->addWidget(listing[nListings]);

   tabulator[nListings]->setLayout(listingBox);

   // Einstellungen fuer listing[...]
   listing[nListings]->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
   //listing[nListings]->ensureCursorVisible();

   connect(listing[nListings], SIGNAL(cursorPositionChanged()), SLOT(zeileAnzeigen()));  // ufg, qt4: funktioniert für maus und tastatur

   tabulatorRahmen->addTab(tabulator[nListings], reiterText ); // Reitertext
   listing[nListings]->setFont( listingfont );

   // zusaetzlich evtl. notwendig - bei aelterer Version
   //connect(listing[nListings], SIGNAL(pos_changed(int,int)), this, SLOT(zeileAnzeigen(int,int)));   // Marcel
}


/* -------------------------------------------------------------------------- */
/* ------------------------------------------------ Aktive Zeile anzeigen --- */
/* ------------------------------------------------ fuer Maus-Klick       --- */
/* -------------------------------------------------------------------------- */
void BabyDevelop::zeileAnzeigen(void)
/* nicht mehr Ueberladen     */
/* Parameter: nix */
{
   // Aktiven Reiter ermitteln
   //--------------------------
   int aktiverReiter = tabulatorRahmen->currentIndex();
   if(projektTyp<1) // kein Projekt geoeffnet
      return;

   // Cursorposition ermitteln
   //--------------------------
   QTextCursor c = listing[aktiverReiter+1]->textCursor();
   int spalte = c.columnNumber();

   // Aktuelle Cursor-Zeile ermitteln
   //---------------------------------
   int zeile = c.blockNumber();

   // Anzahl der Zeilen berechen
   //----------------------------
   QString str = listing[aktiverReiter+1]->toPlainText();
   int nZeilen = str.count( "\n",Qt::CaseInsensitive )+1;

   QString text = landestext->getText("Zeile")+"="+QString::number(zeile+1)+" von "+QString::number(nZeilen)+" ("+landestext->getText("Spalte")+" "+QString::number(spalte+1)+")";
   this->statusBar()->showMessage(text);

   // Fehlermarkierung in Normaldarstellung
   //---------------------------------------
   if(fehleranzeige != 0 )
   {
		// mb: alte markierung nicht im aktiven reiter sonderm im 'fehler_reiter' entfernen

		QTextCursor cl = listing[fehler_reiter+1]->textCursor();
		cl.setPosition(fehler_start_pos,QTextCursor::MoveAnchor); // Zeile ganz nach vorne
		cl.setPosition(fehler_ende_pos,QTextCursor::KeepAnchor);  // Zeile ganz nach hinten
		cl.setCharFormat(format_original);                        // Originalformat einschalten
		cl.setPosition(fehler_ende_pos,QTextCursor::MoveAnchor);
		listing[fehler_reiter+1]->setTextCursor(cl);              // Format aktivieren
		fehleranzeige = 0;
   }

   if(statusDebugger == 1)
   {
      QString text=tabulatorRahmen->tabText(aktiverReiter);
      text=text.remove("[");
      text=text.remove("]");
      debugger->setzeDatei(text);
      debugger->setzeZeile(++zeile);
   }
}


/* ------------------------------------------------------------------------- */
/* ------------------------------------------ an fehlerhafte Stelle springen */
/* ------------------------------------------           Made by Marcel Block */
/* ------------------------------------------------------------------------- */
void BabyDevelop::meldung_doppelklick()
{
   QTextCursor cm = meldungsFenster->textCursor();
   cm.select(QTextCursor::LineUnderCursor);
   QString t = cm.selectedText(); // ganze Zeile
   if(t=="")
      return;

   //-----------------------------------------------------------------------------------------------------
   //                   p   d d
   //typische               1 2
   //Fehlermeldung: test.cpp:9: Fehler: Ã‚Â»inttÃ‚Â« wurde in diesem Gueltigkeitsbereich nicht definiert
   //-----------------------------------------------------------------------------------------------------
   int p  = t.indexOf('.');        // Punkt von Dateiname, vor Dateiendung             ->.cpp:9: Fehler:...
   int d1 = t.indexOf(':');        // Doppelpunkt hinter Dateiendung, vor Zeilennummer ----->:9: Fehler:...
   int d2 = t.indexOf(':',d1+1);   // Doppelpunkt hinter Zeilennummer                  ------->: Fehler:...

   if(p == -1 || d1 == -1 || d2 == -1) // keine gcc/g++ Fehlermeldung
     return;

   QString file = t;
   file.remove(d1, t.length() - d1);   // schneidet alles hinter Zeilennummer ab. Rest: ->test.cpp

   QString line = t;
   line.remove(0, d1 + 1);             // schneidet alles vor der Zeilennummer ab ->9: Fehler:...

   line.remove(line.indexOf(':'), line.length() - line.indexOf(':',-1) + 1); // schneidet alles hinter der Zeilennummer ab

	zeileMarkieren(file, line);
}



/* -------------------------------------------------------------------------- */
/* -------------------------------------------- alle Fenster neu aufbauen */
/* -------------------------------------------------------------------------- */
void BabyDevelop::darstellung()
{
   int i;
   for(i=0; i<nListings; i++)
   {
      if(this->listing[i+1])
      {
         QString t = this->listing[i+1]->toPlainText();
         this->listing[i+1]->setPlainText(t);
      }
   }
}


/* -------------------------------------------------------------------------- */
/* ----------------------------- Sichtbarkeit des Meldungsfensters umschalten */
/* -------------------------------------------------------------------------- */
void BabyDevelop::meldungsfensterEinAus()
{
   if (meldungsFenster->parent() != 0) {
      // als eigenständiges Fenster
      meldungsFenster->setParent(0);
      meldungsFenster->setGeometry(x0mf, y0mf, xmf, ymf);
      meldungsFenster->setWindowTitle(landestext->getText("- Meldungsfenster -"));
      meldungsFenster->setWindowIcon(QIcon(bdpInstallVerzeichnis+"/babyDevelop/bilder/meldungsfenster_mini.xpm"));
      meldungsFenster->show();
   } else {
      // sichtbarkeit an/aus
      meldungsFenster->setVisible(!meldungsFenster->isVisible());
   }
}


/* -------------------------------------------------------------------------- */
/* --------------------------------- Ueberpruefen ob Name schon vorhanden ist */
/* -------------------------------------------------------------------------- */
int BabyDevelop::pruefeNameVorhanden(QString n)
{
   if("main"==n.toLower())
      return -1;
   if(projektName.toLower()==n.toLower())
      return -1;
   for(int z=1; z<=nKlassen;z++)
   {
      if(klassenName[z].toLower()==n.toLower())
         return -1;
   }
   return 0;
}


/* -------------------------------------------------------------------------- */
/* ------------------------------------------------------- ausgabeTimeout --- */
/* -------------------------------------------------------------------------- */
void BabyDevelop::ausgabeTimeout()
{
	// versuche Ausgaben vom Arbeiter zu lesen und schreibe diese ins Meldungsfenster
	char buffer[1024] = "";
	int ret = this->arbeiter->leseAusgabe(buffer, 1023); // !!! -1 wegen nullterminierung !!!
	if(ret > 0) {
		this->meldungsFenster->setPlainText(meldungsFenster->toPlainText()+buffer);
		QTextCursor tc = meldungsFenster->textCursor();
		tc.movePosition(QTextCursor::End,QTextCursor::MoveAnchor);
		meldungsFenster->setTextCursor(tc);
	}
	return;
}


/* ------------------------------------------------------------------------- */
/* ------------------------------------------------ RC-Dateien schreiben --- */
/* ------------------------------------------------------------------------- */
void BabyDevelop::schreibeRCFile(QString typ)
{
   if(typ=="projekt")
   {
      /* bdpProjekt.rc */
      QFile file( projektVerzeichnis + "/bdpProjekt.rc" );
      if ( !file.open( QIODevice::WriteOnly ) )
      {
         meldungsFenster->setPlainText( landestext->getText("Kann Datei bdpProjekt.rc nicht anlegen.") );
         return;
      }

      QTextStream stream( &file );
      stream << "BabyDevelopProjektRC-File\n";
      stream << "n.c.=n.c.\n";
      stream << "CompilerFlags="     << compilerFlags+"\n";
      stream << "LinkerFlags="       << linkerFlags+"\n";
      stream << "n.c.=n.c.\n";
      stream << "n.c.=n.c.\n";
      stream << "n.c.=n.c.\n";
      stream << "escapeSequenzen=" << escape << "\n";
      stream << "n.c.=n.c.\n";
      stream << "n.c.=n.c.\n";
      file.close();
   }
   else   //user_rc_file schreiben
   {
      // .babydevelop_user.rc
      //----------------------
      QFile fileu( QDir::homePath()+"/.babydevelop_user.rc" );
      if ( !fileu.open( QIODevice::WriteOnly ) )
      {
         qWarning("%s", landestext->getText("Kann Datei .babydevelop.user.rc nicht anlegen.").toLatin1().data() );
         return;
      }
      QTextStream streamu(&fileu);
      streamu << "BabyDevelopUserRC-File\n";
      streamu << "n.c.=n.c.\n";
      streamu << "n.c.=n.c.\n";
      streamu << "n.c.=n.c.\n";
      streamu << "autoSpeichern=" << autoSpeichern << "\n";
      streamu << "browserBefehl=" << browserBefehl << "\n";
      streamu << "n.c.=n.c.\n";
      streamu << "n.c.=n.c.\n";
      streamu << "n.c.=n.c.\n";
      streamu << "n.c.=n.c.\n";
      streamu << "n.c.=n.c.\n";
      streamu << "n.c.=n.c.\n";
      fileu.close();
   }
}


/* -------------------------------------------------------------------------- */
/* --------------------------------------    babydevelop.rc einlesen      --- */
/* --------------------------------------       System-Einstellungen      --- */
/* -------------------------------------------------------------------------- */
void BabyDevelop::ladeRCFile()
{
   /* ---------------------------------------- */
   /* 1. System-Einstellungen = babydevelop.rc */
   /* ---------------------------------------- */
   QString s = bdpInstallVerzeichnis + "/babyDevelop/babydevelop.rc";
   QFile file(s);

//   qWarning("ladeRCFile: lade Datei '%s'", s.toAscii().constData());

   if(!file.open(QIODevice::ReadOnly))
   {
      //meldungsFenster->setText("Kann Datei babydevelop.rc nicht oeffnen.");
      qWarning("Kann Datei babydevelop.rc nicht oeffnen.");

	  // Standardwerte damit BabyDevelop startet
	  x0bd = 25; y0bd = 25;  xbd = 800; ybd = 600;
	  x0mf = 25; y0mf = 651; xmf = 800; ymf = 115;
	  laenderkuerzel = "de";

      return;
   }

   QTextStream stream(&file);
   // Datei einlesen
   //----------------
   QString line;
   line = stream.readLine();   // BabyDevelopRC-File
   line = stream.readLine();   // FensterStartGroesse=0,0,800,600
      line=line.mid (line.indexOf("=")+1);
      x0bd=line.left(line.indexOf(",")).toInt();
      line=line.mid (line.indexOf(",")+1);
      y0bd=line.left(line.indexOf(",")).toInt();
      line=line.mid (line.indexOf(",")+1);
      xbd =line.left(line.indexOf(",")).toInt();
      line=line.mid (line.indexOf(",")+1);
      ybd =line.toInt();
   line = stream.readLine();   // MeldungsFensterStartGroesse=0,0,400,300
      line=line.mid (line.indexOf("=")+1);
      x0mf=line.left(line.indexOf(",")).toInt();
      line=line.mid (line.indexOf(",")+1);
      y0mf=line.left(line.indexOf(",")).toInt();
      line=line.mid (line.indexOf(",")+1);
      xmf =line.left(line.indexOf(",")).toInt();
      line=line.mid (line.indexOf(",")+1);
      ymf =line.toInt();
   line = stream.readLine();   // Font=Courier
      schriftArt=line.mid(line.indexOf("=")+1);
      listingfont = schriftArt;
   line = stream.readLine();   // n.c.

   line = stream.readLine();   // n.c.

   line = stream.readLine();   // QtHilfePfadDatei
      qtHilfePfadDatei=line.mid (line.indexOf("=")+1);
   line = stream.readLine();   // n.c.

   line = stream.readLine();   // QtDir
      QtDir=line.mid (line.indexOf("=")+1);
   line = stream.readLine();   // QtLib
      QtLib=line.mid (line.indexOf("=")+1);
   line = stream.readLine();   // Linker-Libs
      Libs=line.mid (line.indexOf("=")+1);
   line = stream.readLine();   // MetaObjektCompiler-Verzeichnis
      MocDir=line.mid (line.indexOf("=")+1);
      if(MocDir=="-/-")
      {
         MocDir="";
      }
   line = stream.readLine();   // laenderkuerzel de, en, es
      laenderkuerzel=line.mid (line.indexOf("=")+1);

   line = stream.readLine();   // n.c.
   line = stream.readLine();   // n.c.
   line = stream.readLine();   // n.c.
   line = stream.readLine();   // n.c.
   line = stream.readLine();   // n.c.
   line = stream.readLine();   // Schulversion (undokumentiert)

//und noch weitere 2 n.c.

   file.close();


#if defined(WIN32)
	if(x0bd < 4)  x0bd = 4;  //Menüleiste & Meldungsfenster
	if(y0bd < 24) y0bd = 24; //nicht außerhalb des Bildschirm
	if(x0mf < 4)  x0mf = 4;  //...
#endif

}


/* -------------------------------------------------------------------------- */
/* --------------------------------------    babydevelop_user.rc einlesen --- */
/* --------------------------------------       User-Einstellungen        --- */
/* -------------------------------------------------------------------------- */
void BabyDevelop::ladeUserRCFile()
{
   /* ------------------------------------------- */
   /* 2. User-Einstellungen = .babydevelop_user.rc */
   /* ------------------------------------------- */

   if( QFile::exists( QDir::homePath() + "/.babydevelop_user.rc") )
   {
      QFile fileu( QDir::homePath() + "/.babydevelop_user.rc" );
      if(!fileu.open(QIODevice::ReadOnly))
      {
         //meldungsFenster->setText( landestext->getText("Kann Datei babydevelop.user.rc nicht oeffnen.") );
         qWarning("%s", landestext->getText("Kann Datei babydevelop.user.rc nicht oeffnen.").toAscii().constData() );
         return;
      }
      QTextStream streamu(&fileu);

      // Datei einlesen
      //----------------
      QString line;
      line = streamu.readLine();   // BabyDevelopUserRC-File
      line = streamu.readLine();   // n.c.
      line = streamu.readLine();   // n.c.
      line = streamu.readLine();   // n.c.
      line = streamu.readLine();   // autoSpeichern=0
         autoSpeichern=line.mid(line.lastIndexOf("=",-1)+1).toInt();
      line = streamu.readLine();   // browserBefehl=firefox
         browserBefehl=line.mid(line.lastIndexOf("=",-1)+1);
      line = streamu.readLine();   // n.c.
      line = streamu.readLine();   // escapeSequenzen=0 ist Standard
         if(line.contains("1",Qt::CaseInsensitive))
         {
            escape=1;
         }
         else
         {
            escape=0;
         }
      line = streamu.readLine();   // n.c.
      line = streamu.readLine();   // n.c.
      line = streamu.readLine();   // n.c.
      line = streamu.readLine();   // n.c.
      fileu.close();
   }
   else
   {
      autoSpeichern = 1;
      browserBefehl = "firefox";

      qWarning("%s", landestext->getText("- Fehler -").toAscii().constData() );
      qWarning("%s", landestext->getText(".babyDevelop_user.rc nicht gefunden. Das integrierte Hilfesystem wird evtl. nicht funktionieren.").toAscii().constData() );
      qWarning("%s", landestext->getText("Bitte stellen Sie im Menue Bearbeiten unter Einstellungen die gewuenschten Werte ein.").toAscii().constData() );

      schreibeRCFile("user");
   }
}


void BabyDevelop::closeEvent(QCloseEvent *e)
{
   //wird benoetigt um Klick auf [X] abzufangen
   qApp->exit();
}

void BabyDevelop::schreibeMeldungsfenster(QString s)
{
	this->meldungsFenster->setPlainText(meldungsFenster->toPlainText() + s);
}

int BabyDevelop::pruefeProjektName(QString projektName)
{
	QRegExp rx = QRegExp("[^0-9-._/a-z]",Qt::CaseInsensitive,QRegExp::Wildcard); //RegulÃ¤rer_Ausdruck, KeySensitive_ja/nein, Wildcard_ja/nein
	if(projektName.contains(rx) > 0) {
		return -1;
	}
	return 0;
}

int BabyDevelop::pruefeVerzeichnisName(QString verzeichnisName)
{
	// erlaubt sind:
    // 0-9 = alle Zahlen
    // -._ = Minus, Punkt, Unterstrich
    // /   = Schraegstrich
    // a-z = alle Buchstaben
    // ^ = und das alles NICHT
	//
	// windows: :\ = Doppelpunkt,Backslash für Pfadangaben wie z.b. C:/babydevelop oder C:\babydevelop

#if defined(LINUX)
	QRegExp rx = QRegExp("[^0-9-._/a-z]",Qt::CaseInsensitive,QRegExp::Wildcard);
	if(verzeichnisName.contains(rx) > 0) {
		return -1;
	}

#elif defined(WIN32)
	QRegExp rx = QRegExp("[^0-9-._/\a-z]",Qt::CaseInsensitive,QRegExp::Wildcard);
	// C:/foo/bar
	// C:\foo\bar
	if(verzeichnisName.mid(1, 1) != ":") {
		return -1;
	}
	if(verzeichnisName.right(verzeichnisName.length()-2).contains(rx) > 0) {
		return -1;
	}

#endif

	return 0;
}

