/*--------------*/
/* debugger.cpp */
/*--------------*/

/*------------------------------*/
/* Implemented by Jonas Gehring */
/*------------------------------*/

#include "debugger.h"

/* Constructor */
Debugger::Debugger(QWidget *elternWidget, QPlainTextEdit *meldungsFenster, int projektTyp, QString projektVerzeichnis, QString binary) : QWidget(elternWidget)
{
   this->meldungsFenster = meldungsFenster;
   this->meldungsFenster->clear();
   this->meldungsFenster->setPlainText("Debugger gestartet.\n");

   this->setWindowTitle("- Debugger -");
   this->setFixedSize(200,290);
   this->move(200,200);

   // Fenster immer im Vordergrund
   Qt::WindowFlags WFlags = this->windowFlags();
   WFlags |= Qt::WindowStaysOnTopHint;
   this->setWindowFlags(WFlags);


//   QColor farbeHintergrund;
//      farbeHintergrund.setHsv(56,132,255);
//   QPalette p;
//      p.setColor(QPalette::Background, farbeHintergrund);

   //Gelbe Papierfarbe ist leider etwas aufwaendig
   QColor farbe_gelb;                       //Gelb soll es sein
      farbe_gelb.setRgb(252,255,0);         //yellow
      QPalette palette_gelb;                //Bestimmt die Behandlung z.B. Aufhellen beim Ueberfahren mit der Maus
      palette_gelb.setColor(QPalette::Window, farbe_gelb);
   this->setPalette(palette_gelb);

//??????????????????????????
   QColor farbe_blau;                       //Blau soll es sein
      farbe_blau.setRgb(0,255,255);         //blau
      QPalette palette_blau;                //Bestimmt die Behandlung z.B. Aufhellen beim Ueberfahren mit der Maus
      palette_blau.setColor(QPalette::Window, farbe_blau);

//   this->setPalette(p);
//   this->setBackgroundRole( QPalette::Background );

   landestext=new UFGi18n();

   meldung = new QLabel(landestext->getText(":)"),this);
   meldung->setGeometry(5,5,180,20);
   meldung->setPalette(palette_blau);
//   meldung->setBackgroundRole(QPalette::Base );
   meldung->setPalette(palette_blau);
   meldung->show();

   tasteWeiter = new QPushButton(landestext->getText("weiter"),this);
   tasteWeiter->setGeometry(5,35,90,30);
   tasteWeiter->show();
	tasteWeiter->setEnabled( false );
   connect(tasteWeiter,SIGNAL(clicked()),SLOT(weiter()));

   tasteEinzelschritt = new QPushButton(landestext->getText("Einzelschritt"),this);
   tasteEinzelschritt->setGeometry(100,35,90,30);
	tasteEinzelschritt->setEnabled( false );
   tasteEinzelschritt->show();
   connect(tasteEinzelschritt,SIGNAL(clicked()),SLOT(einzelschritt()));

   txtBreakpoints = new QLabel("Breakpoints",this);
   txtBreakpoints->setGeometry(5,70,100,20);
//   txtBreakpoints->setAutoFillBackground(true);  //Hintergrund automatisch zeichnen, wenn notwendig
   txtBreakpoints->setPalette(palette_gelb);
   txtBreakpoints->show();

   breakpoints = new QComboBox(this);
   breakpoints->setGeometry(5,91,190,30);
   breakpoints->show();

   tasteSpeichern = new QPushButton(landestext->getText("Speichern"),this);
   tasteSpeichern->setGeometry(5,125,90,30);
	tasteSpeichern->setEnabled( false );
   tasteSpeichern->show();
   connect(tasteSpeichern,SIGNAL(clicked()),SLOT(speichern()));

   tasteEntfernen = new QPushButton(landestext->getText("Entfernen"),this);
   tasteEntfernen->setGeometry(105,125,90,30);
	tasteEntfernen->setEnabled( false );
   tasteEntfernen->show();
   connect(tasteEntfernen,SIGNAL(clicked()),SLOT(entfernen()));

   tasteStart = new QPushButton(landestext->getText("Start"),this);
   tasteStart->setGeometry(5,170,90,30);
   tasteStart->show();
   connect(tasteStart,SIGNAL(clicked()),SLOT(start()));

   tasteStop = new QPushButton(landestext->getText("Stop"),this);
   tasteStop->setGeometry(105,170,90,30);
   tasteStop->show();
	tasteStop->setEnabled(0);
   connect(tasteStop,SIGNAL(clicked()),SLOT(stop()));

   txtBefehl = new QLabel("Befehl",this);
   txtBefehl->setGeometry(5,212,65,20);
   txtBefehl->show();

   befehl = new QLineEdit("",this);
   befehl->setGeometry(50,210,70,25);
   befehl->show();

   tasteSenden = new QPushButton(landestext->getText("Senden"),this);
   tasteSenden->setGeometry(125,210,70,30);
	tasteSenden->setEnabled( true );
   tasteSenden->show();
   connect(tasteSenden,SIGNAL(clicked()),SLOT(senden()));

   tasteBeenden = new QPushButton(landestext->getText("Beenden"),this);
   tasteBeenden->setGeometry(5,250,90,30);
   tasteBeenden->show();
   connect(tasteBeenden, SIGNAL(clicked()), SIGNAL(beendeDebugger())); // signal forwarding

    //----------------------------------------------------------------------------
    runtimer = new QTimer(this);
    runtimer->start(10);
    connect(this->runtimer, SIGNAL(timeout()), this, SLOT(leseAusgabe()));
    //----------------------------------------------------------------------------

    //----------------------------------------------------------------------------
    this->arbeiter = new CArbeiter();
    this->arbeiter->start(ARBEITER_DEBUGGER, projektVerzeichnis, binary);
    //----------------------------------------------------------------------------
}

/* Destructor */
Debugger::~Debugger()
{
    if(this->arbeiter) {
        delete this->arbeiter;
        this->arbeiter = NULL;
    }
}

/* --- Methoden ---------------- */
void Debugger::setzeZeile(int z)
{
    if(tasteBeenden->isEnabled()){
        tasteSpeichern->setEnabled( true );
        zeile = z;
    }
}

void Debugger::setzeDatei(QString d)
{
    datei = d;
}

void Debugger::senden()
{
    QString buf = befehl->text() + "\n";
    this->arbeiter->schreibeEingabe(buf.toAscii().constData());
}

void Debugger::einzelschritt()
{
    this->arbeiter->schreibeEingabe("step\n");
}

void Debugger::weiter()
{
    this->arbeiter->schreibeEingabe("c\n");
}

void Debugger::speichern()
{
    if(datei=="") datei="main.cpp";
    QString entry = datei+":"+QString::number(zeile);

    breakpoints->addItem(entry);
    tasteEntfernen->setEnabled( true );
}

void Debugger::entfernen()
{
    if(breakpoints->count() <= 1){
        tasteSpeichern->setEnabled( false );
        tasteEntfernen->setEnabled( false );
    }
    breakpoints->removeItem(breakpoints->currentIndex());
}

void Debugger::start()
{
    /* setze breakpoints */
    int i;
    for(i=0; i<breakpoints->count(); i++) {
        char buffer[1024] = "";
        sprintf(buffer, "b %s\n", breakpoints->itemText(i).toLatin1().data());
        this->arbeiter->schreibeEingabe(buffer);
    }

    /* starte Programm */
    this->arbeiter->schreibeEingabe("r\n");

    tasteStart->setEnabled(false);
    tasteBeenden->setEnabled(false);
}

void Debugger::stop()
{
    this->arbeiter->schreibeEingabe("q\n");
    this->arbeiter->stop();

    tasteBeenden->setEnabled(1);
}

void Debugger::leseAusgabe()
{
    char buffer[4096] = "";
    int len = this->arbeiter->leseAusgabe(buffer, 4095);

//    if(len > 0) {
//        qWarning("len=%d buffer='%s'", len, buffer);
//    }

   if(len > 0)
   {
      this->meldungsFenster->setPlainText(meldungsFenster->toPlainText()+buffer);

      //dass immer unterste Zeile zu sehen ist
      QTextCursor tc = meldungsFenster->textCursor();
      tc.movePosition(QTextCursor::End,QTextCursor::MoveAnchor);
      meldungsFenster->setTextCursor(tc);

      /* Ueberpruefen ob der Debugger beendet wurde */
		char* e = strstr(buffer,"Exit");
		char* c;

      if(e){
         tasteBeenden->setEnabled( true );
         c=NULL; // if(c AND e != EXIT)
   	}else c = strstr(buffer,"(gdb)"); // Abfragen ob der Debugger auf eine Eingabe wartet

		if(c){ // wenn der Debugger auf eine Eingabe wartet
         tasteWeiter->setEnabled( true );
         tasteStop  ->setEnabled( true );
         tasteSenden->setEnabled( true );
         tasteEinzelschritt->setEnabled(true);
			meldung->setText("Langweilig :("); //Debugger wartet auf einen Befehl
		}else{

			if(tasteBeenden->isEnabled()){ // wenn der Debugger beendet ist (stop-Befehl gesendet)
         	tasteStart    ->setEnabled( true );
         	tasteSpeichern->setEnabled( true );
         	tasteEntfernen->setEnabled( true );
         	tasteBeenden  ->setEnabled( true );
         	tasteStop         ->setEnabled( false );
         	tasteWeiter       ->setEnabled( false );
            tasteSenden       ->setEnabled( false );
            tasteEinzelschritt->setEnabled( false );
				meldung->setText("Debugger beendet.");
			}else{ // wenn der Debugger arbeitet und keine Eingabe moeglich ist
				meldung->setText("Arbeite...");
         	tasteStart        ->setEnabled( false );
         	tasteSpeichern    ->setEnabled( false );
         	tasteEntfernen    ->setEnabled( false );
         	tasteBeenden      ->setEnabled( false );
         	tasteStop         ->setEnabled( false );
         	tasteWeiter       ->setEnabled( false );
         	tasteSenden       ->setEnabled( false );
            tasteEinzelschritt->setEnabled( false );
         }
         /* Ueberpruefen ob der Debugger eine unerwartete Eingabe erwartet */
   		char* t = strstr(buffer,"---Type");
         if(t){
            tasteSenden->setEnabled( true );
      	}
		}
		/* suche nach breakpoints */
		int b_a=0;
		b_a = breakpoints->count();

		char* b;
		for(int i=0;i<b_a;i++){
			b = strstr(buffer,breakpoints->itemText(i).toLatin1().data());
			if(b) {
				QString t = breakpoints->itemText(i).toLatin1().data();
			   int d1 = t.indexOf(':');
			   QString file = t;
			   file.remove(d1, t.length());

			   QString line = t;
			   line.remove(0, d1 + 1);

//				springeZeile(file,line);
				meldung->setText(t);

                // zeile minus eins
                // sonst stimmt die angezeigte zeile nicht
                bool ok = false;
                int nLine = line.toInt(&ok, 10);
                if(ok == true) {
                    if(nLine > 0) nLine--;
                    line = QString::number(nLine);
                }

				emit springeZeile(file, line);

				break;
			}
		}
	}
}

void Debugger::closeEvent(QCloseEvent *e)
{
    //wird benoetigt um Klick auf [X] abzufangen
    e->ignore();
}

void Debugger::keyPressEvent(QKeyEvent *e)
{
//qWarning("Debugger::keyPressEvent(...)");
//   e->accept();  // Annehmen des KeyEvents
//releaseKeyboard();
//   if(klassenName->text().isEmpty())
//   {
//qWarning("leer");
//      tasteOk->setEnabled(false);
//   }
//   else
//   {
//qWarning("inhalt");
//      tasteOk->setEnabled(true);
//   }
//releaseKeyboard();
//
//   switch ( e->key() )
//   {                     // Hinweis: die Rueckgabecodes der einzelnen Tasten findet man in der "qnamespace.h"
//      case Qt::Key_Escape:
//         emit abbruch();
//         break;
//   }
}

