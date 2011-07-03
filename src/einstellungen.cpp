/*-------------------*/
/* einstellungen.cpp */
/*-------------------*/

#include "einstellungen.h"

extern int x0mf, y0mf, xmf, ymf;
extern int x0bd, y0bd, xbd, ybd;
extern int autoSpeichern;
extern int escape;

extern QString bdpInstallVerzeichnis;
extern QString schriftArt;
extern QString linkerFlags;
extern QString compilerFlags;
extern QString browserBefehl;
extern QString qtHilfePfadDatei;
extern QString QtLib;
extern QString Libs;
extern QString QtDir;
extern QString MocDir;

// Konstruktor
Einstellungen::Einstellungen(QWidget *parent) : QWidget(parent)
{
   landestext=new UFGi18n();

   this->setWindowTitle(landestext->getText("- Einstellungen -"));
   this->setFixedSize(655,516);

   QColor farbe_gelb;
      farbe_gelb.setHsv(56,132,255);
   QPalette p_gelb;
      p_gelb.setColor(QPalette::Background, farbe_gelb);
   this->setPalette(p_gelb);
   this->setBackgroundRole( QPalette::Background );

   this->setWindowIcon(QIcon(bdpInstallVerzeichnis+"/babyDevelop/bilder/einstellungen_mini.xpm"));

   // Rahmen um die einzelnen Bereiche
   //----------------------------------
   rahmenBdp = new QGroupBox( this );
   rahmenBdp->setGeometry(5,0,645,293);
   rahmenBdp->setTitle(landestext->getText("BabyDevelop-Einstellungen"));

   rahmenProjekt = new QGroupBox( this );
   rahmenProjekt->setGeometry(5,297,645,158);
   rahmenProjekt->setTitle(landestext->getText("Projekt-Einstellungen"));

   rahmenTasten = new QGroupBox( this );
   rahmenTasten->setGeometry(5,467,645,45);

   // Einstellungen fuer Babydevelop
   //--------------------------------
   txtFensterStartGroesse = new QLabel("<font color=magenta>B</font><font color=blue>a</font><font color=red>b</font><font color=green>y</font>Develop "+landestext->getText("Startgroesse"),rahmenBdp);
   txtFensterStartGroesse->setGeometry(5,20,280,20);
   txtFensterStartGroesse->show();
      txtX0F = new QLabel("X0=",this);   // hier sollte ueberall rahmenBdp stehen anstelle von this
      txtX0F->setGeometry(295,20,30,20);
      txtX0F->show();
      x0F = new QLineEdit(QString::number(x0bd),this);
      x0F->setGeometry(330,20,30,20);
      x0F->setEnabled(false);
      x0F->show();
      txtY0F = new QLabel("Y0=",this);
      txtY0F->setGeometry(370,20,30,20);
      txtY0F->show();
      y0F = new QLineEdit(QString::number(y0bd),this);
      y0F->setGeometry(405,20,30,20);
      y0F->setEnabled(false);
      y0F->show();
      txtBreiteF = new QLabel(landestext->getText("Breite")+"=",this);
      txtBreiteF->setGeometry(445,20,55,20);
      txtBreiteF->show();
      breiteF = new QLineEdit(QString::number(xbd),this);
      breiteF->setGeometry(505,20,30,20);
      breiteF->setEnabled(false);
      breiteF->show();
      txtHoeheF = new QLabel(landestext->getText("Hoehe")+"=",this);
      txtHoeheF->setGeometry(545,20,60,20);
      txtHoeheF->show();
      hoeheF = new QLineEdit(QString::number(ybd),this);
      hoeheF->setGeometry(610,20,30,20);
      hoeheF->setEnabled(false);
      hoeheF->show();

   txtMeldungsFensterStartGroesse = new QLabel(landestext->getText("Meldungsfenster Startgroesse"),this);
   txtMeldungsFensterStartGroesse->setGeometry(10,42,280,20);
   txtMeldungsFensterStartGroesse->show();
      txtX0MF = new QLabel("X0=",this);
      txtX0MF->setGeometry(295,42,30,20);
      txtX0MF->show();
      x0MF = new QLineEdit(QString::number(x0mf),this);
      x0MF->setGeometry(330,42,30,20);
      x0MF->setEnabled(false);
      x0MF->show();
      txtY0MF = new QLabel("Y0=",this);
      txtY0MF->setGeometry(370,42,30,20);
      txtY0MF->show();
      y0MF = new QLineEdit(QString::number(y0mf),this);
      y0MF->setGeometry(405,42,30,20);
      y0MF->setEnabled(false);
      y0MF->show();
      txtBreiteMF = new QLabel(landestext->getText("Breite")+"=",this);
      txtBreiteMF->setGeometry(445,42,55,20);
      txtBreiteMF->show();
      breiteMF = new QLineEdit(QString::number(xmf),this);
      breiteMF->setGeometry(505,42,30,20);
      breiteMF->setEnabled(false);
      breiteMF->show();
      txtHoeheMF = new QLabel(landestext->getText("Hoehe")+"=",this);
      txtHoeheMF->setGeometry(545,42,60,20);
      txtHoeheMF->show();
      hoeheMF = new QLineEdit(QString::number(ymf),this);
      hoeheMF->setGeometry(610,42,30,20);
      hoeheMF->setEnabled(false);
      hoeheMF->show();

   txtSchriftArt = new QLabel(landestext->getText("Schriftart"),this);
   txtSchriftArt->setGeometry(10,64,280,20);
   txtSchriftArt->show();
   schriftArtFeld = new QLineEdit(schriftArt,this);
   schriftArtFeld->setGeometry(295,64,345,20);
   schriftArtFeld->setEnabled(false);
   schriftArtFeld->show();

   txtbdpInstallationsVerzeichnis = new QLabel(landestext->getText("Verzeichnis der Installation"),this);
   txtbdpInstallationsVerzeichnis->setGeometry(10,86,280,20);
   txtbdpInstallationsVerzeichnis->show();
   bdpInstallationsVerzeichnis = new QLineEdit(bdpInstallVerzeichnis,this);
   bdpInstallationsVerzeichnis->setGeometry(295,86,345,20);
   bdpInstallationsVerzeichnis->setEnabled(false);
   bdpInstallationsVerzeichnis->show();

   txtBrowserBefehl = new QLabel(landestext->getText("Browserbefehl mit oder ohne Pfad"),this);
   txtBrowserBefehl->setGeometry(10,108,280,20);
   txtBrowserBefehl->show();
   browserFeld = new QLineEdit(browserBefehl,this);
   browserFeld->setGeometry(295,108,345,20);
   browserFeld->show();

   txtQtHilfePfadDatei = new QLabel(landestext->getText("Qt Hilfedatei mit Pfad"),this);
   txtQtHilfePfadDatei->setGeometry(10,130,280,20);
   txtQtHilfePfadDatei->show();
   qtHilfePfadDateiFeld = new QLineEdit(qtHilfePfadDatei,this);
   qtHilfePfadDateiFeld->setGeometry(295,130,345,20);
   qtHilfePfadDateiFeld->setEnabled(false);
   qtHilfePfadDateiFeld->show();

   txtBetriebssystem = new QLabel(landestext->getText("Betriebssystem"),this);
   txtBetriebssystem->setGeometry(10,152,280,20);
   txtBetriebssystem->show();
   betriebssystemFeld = new QLineEdit("Linux",this);
   betriebssystemFeld->setGeometry(295,152,345,20);
   betriebssystemFeld->setEnabled(false);
   betriebssystemFeld->show();

   txtQtDir = new QLabel(landestext->getText("Verzeichnis der Qt-Header-Dateien"),this);
   txtQtDir->setGeometry(10,174,280,20);
   txtQtDir->show();
   qtDir = new QLineEdit(QtDir,this);
   qtDir->setGeometry(295,174,345,20);
   qtDir->setEnabled(false);
   qtDir->show();

   txtQtLib = new QLabel(landestext->getText("Verzeichnis der Qt-Libraries"),this);
   txtQtLib->setGeometry(10,196,280,20);
   txtQtLib->show();
   qtLib = new QLineEdit(QtLib,this);
   qtLib->setGeometry(295,196,345,20);
   qtLib->setEnabled(false);
   qtLib->show();

   txtBdpLibs = new QLabel(landestext->getText("Libraries fuer den Linker"),this);
   txtBdpLibs->setGeometry(10,218,280,20);
   txtBdpLibs->show();
   bdpLibs = new QLineEdit(Libs,this);
   bdpLibs->setGeometry(295,218,345,20);
   bdpLibs->setEnabled(false);
   bdpLibs->show();

   txtMocDir = new QLabel(landestext->getText("Verzeichnis des MetaObjektCompilers"),this);
   txtMocDir->setGeometry(10,240,280,20);
   txtMocDir->show();
   mocDir = new QLineEdit(MocDir,this);
   mocDir->setGeometry(295,240,345,20);
   mocDir->setEnabled(false);
   mocDir->show();

   schalterAS = new QPushButton("",this);
   schalterAS->setGeometry(550,264,40,25);
   schalterAS->show();
   connect(schalterAS,SIGNAL(clicked()),SLOT(wechselnAS()));

   txtSyntaxHighlighting = new QLabel("n.c.",this);
   txtSyntaxHighlighting->setGeometry(10,268,140,20);
   txtSyntaxHighlighting->show();
   syntaxHighlightingFeld = new QLineEdit("n.c.",this);
   syntaxHighlightingFeld->setGeometry(155,267,40,20);
   syntaxHighlightingFeld->setReadOnly(true);
   syntaxHighlightingFeld->show();

   schalterSH = new QPushButton(":-)",this);
   schalterSH->setGeometry(205,264,40,25);
   schalterSH->show();
   connect(schalterSH,SIGNAL(clicked()),SLOT(wechselnSH()));

   txtAutoSpeichern = new QLabel(landestext->getText("Automatisch speichern"),this);
   txtAutoSpeichern->setGeometry(295,268,190,20);
   txtAutoSpeichern->show();
   QString as;
   if(autoSpeichern==0)
   {
      as=landestext->getText("Nein");
      schalterAS->setText(":-(");
   }
   else
   {
      as=landestext->getText("Ja");
      schalterAS->setText(":-)");
   }
   autoSpeichernFeld = new QLineEdit(as,this);
   autoSpeichernFeld->setGeometry(500,267,40,20);
   autoSpeichernFeld->setReadOnly(true);
   autoSpeichernFeld->show();

   // Einstellungen fuer das Projekt
   //--------------------------------
   txtCompilerFlags = new QLabel("Compiler-Flags",this);
   txtCompilerFlags->setGeometry(10,322,140,20);
   txtCompilerFlags->show();
   compilerFlagsFeld = new QLineEdit(compilerFlags,this);
   compilerFlagsFeld->setGeometry(165,322,475,20);
   compilerFlagsFeld->show();

   txtLinkerFlags = new QLabel("Linker-Flags",this);
   txtLinkerFlags->setGeometry(10,347,140,20);
   txtLinkerFlags->show();
   linkerFlagsFeld = new QLineEdit(linkerFlags,this);
   linkerFlagsFeld->setGeometry(165,347,475,20);
   linkerFlagsFeld->show();

   txtEscape = new QLabel(landestext->getText("EscapeSequenzen"),this);
   txtEscape->setGeometry(10,425,190,20);
   txtEscape->show();

   schalterEsc = new QPushButton("",this);
   schalterEsc->setGeometry(205,423,40,25);
   schalterEsc->show();
   connect(schalterEsc,SIGNAL(clicked()),SLOT(wechselnEsc()));

   QString esc;
   if(escape==0)
   {
      esc=landestext->getText("Nein");
      schalterEsc->setText(":-(");
   }
   else
   {
      esc=landestext->getText("Ja");
      schalterEsc->setText(":-o");
   }
   escapeFeld = new QLineEdit(esc,this);
   escapeFeld->setGeometry(155,425,40,20);
   escapeFeld->setReadOnly(true);
   escapeFeld->show();

   // allgemeine Tasten
   //-------------------
   tasteAbbrechen = new QPushButton(landestext->getText("Abbrechen"),this);
   tasteAbbrechen->setGeometry(10,472,95,35);
   tasteAbbrechen->show();

   tasteSpeichern = new QPushButton(landestext->getText("Speichern"),this);
   tasteSpeichern->setGeometry(110,472,95,35);
   tasteSpeichern->show();
}


// Destruktor
Einstellungen::~Einstellungen()
{
}


void Einstellungen::wechselnAS()
{
   if(autoSpeichern==0)
   {
      autoSpeichernFeld->setText(landestext->getText("Ja"));
      autoSpeichern=1;
      schalterAS->setText(":-)");
   }
   else
   {
      autoSpeichernFeld->setText(landestext->getText("Nein"));
      autoSpeichern=0;
      schalterAS->setText(":-(");
   }
}


void Einstellungen::wechselnSH()
{
   syntaxHighlightingFeld->setText("n.c.");
}


void Einstellungen::wechselnEsc()
{
   if(escape==0)
   {
      escapeFeld->setText(landestext->getText("Ja"));
      escape=1;
      schalterEsc->setText(":-o");
   }
   else
   {
      escapeFeld->setText(landestext->getText("Nein"));
      escape=0;
      schalterEsc->setText(":-(");
   }
}


// CFlags und LFlags enabled/disabled setzen
//-------------------------------------------
void Einstellungen::setNoProjekt(int status)
{
   if(status==1)
   {
      compilerFlagsFeld->setEnabled(false);
      linkerFlagsFeld->setEnabled(false);
   }
   else
   {
      compilerFlagsFeld->setEnabled(true);
      linkerFlagsFeld->setEnabled(true);
   }
}


// nicht auf [X] reagieren
//-------------------------
void Einstellungen::closeEvent(QCloseEvent *event)
{
   event->ignore();
}

