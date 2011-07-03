/*-----------------*/
/* ufgdesigner.cpp */
/*-----------------*/

#include "ufgdesigner.h"

/* Konstruktor */
UFGdesigner::UFGdesigner(QWidget* parent) : QWidget(parent)
{
   landestext = new UFGi18n();

   zustand       = 0;
   nummer        = 0;
   anzahlObjekte = 0;
   wunschobjekt  = 0;

   this->setGeometry(200, 200, 400, 285);   // die GUI
   this->show();

   Qt::WindowFlags f = Qt::Window;
   //f = Qt::Widget;
   //f = Qt::Window;
   //f = Qt::Tool;
   //f = Qt::SubWindow;
   //f = Qt::FramelessWindowHint; //notfall
   //??f = Qt::CustomizeWindowHint;

   werkzeug = new QWidget(0, f);   //Werkzeugbox
   //   werkzeug = new QWidget(0);   //Werkzeugbox
   //Qt::WType_Dialog nur [X]
   //Qt::WType_Popup garkein Rahmen
   //Qt::WType_Desktop jedes Objekt freifliegend
   //Qt::WStyle_DialogBorder
   //Qt::WStyle_NoBorder kein Rand
   //Qt::WStyle_NoBorderEx wirkungslos


   //werkzeug->setGeometry(0,30,100,305); //Werkzeugkasten fuer Widgets
   werkzeug->move(0, 30);
   werkzeug->setFixedSize(100, 305);

   QColor farbe_gelb;
      //farbe_gelb.setHsv(252,255,0); //yellow
      //farbe_gelb.setHsv(yellow); //yellow
      farbe_gelb.setRgb(252, 255, 0); //yellow
   QPalette p_gelb;
      p_gelb.setColor(QPalette::Window, farbe_gelb); //alt: Background
   werkzeug->setPalette(p_gelb);
   werkzeug->setBackgroundRole( QPalette::Window );
   werkzeug->show();

   tasteEsc = new QPushButton("Esc", werkzeug);
   tasteEsc->setGeometry(10, 5, 80, 25);
   tasteEsc->show();
   connect(tasteEsc, SIGNAL(clicked()), SLOT(esc()));
   tasteEsc->setDisabled(true);

   tasteLabel = new QPushButton("Label", werkzeug);
   tasteLabel->setGeometry(5, 35, 90, 25);
   tasteLabel->show();
   connect(tasteLabel, SIGNAL(clicked()), SLOT(label()));
   nameLabel = new QLineEdit("", werkzeug);
   nameLabel->setGeometry(5, 35, 90, 25);
   nameLabel->hide();

   tasteLineEdit = new QPushButton("LineEdit", werkzeug);
   tasteLineEdit->setGeometry(5, 65, 90, 25);
   tasteLineEdit->show();
   connect(tasteLineEdit, SIGNAL(clicked()), SLOT(lineEdit()));
   nameLineEdit = new QLineEdit("", werkzeug);
   nameLineEdit->setGeometry(5, 65, 90, 25);
   nameLineEdit->hide();

   tastePushButton = new QPushButton("PushButton", werkzeug);
   tastePushButton->setGeometry(5,95,90,25);
   tastePushButton->show();
   connect(tastePushButton, SIGNAL(clicked()), SLOT(pushButton()));
   namePushButton = new QLineEdit("", werkzeug);
   namePushButton->setGeometry(5, 95, 90, 25);
   namePushButton->hide();

   tasteLed = new QPushButton("Led", werkzeug);
   tasteLed->setGeometry(5, 125, 90, 25);
   tasteLed->show();
   connect(tasteLed, SIGNAL(clicked()), SLOT(led()));

   nameLed = new QLineEdit("", werkzeug);
   nameLed->setGeometry(5, 125, 90, 25);
   nameLed->hide();

   //---------------------------------------------------------------------------
   tasteAbbrechen = new QPushButton(landestext->getText("Abbrechen"), werkzeug);
   tasteAbbrechen->setGeometry(5, 215, 90, 25);
   tasteAbbrechen->show();

   tasteBeenden = new QPushButton(landestext->getText("Beenden"), werkzeug);
   tasteBeenden->setGeometry(5, 245, 90, 25);
   tasteBeenden->show();

   tasteLoeschen = new QPushButton("Kill", werkzeug);
   tasteLoeschen->setGeometry(5, 275, 60, 25);
   tasteLoeschen->show();
   connect(tasteLoeschen, SIGNAL(clicked()), SLOT(loeschen()));

   timerled = new BLed(werkzeug);
   timerled->setGeometry(70, 275, 25, 25);
   timerled->setColor(Qt::red);
   timerled->off();
   timerled->show();

   timer = new QTimer(this);
   connect(timer, SIGNAL(timeout()), SLOT(takt()));

   //--------------------------------------------------------------------------------------
   // ohne die folgenden beiden Zeilen wird
   // ohne das GUI bewegt zu haben
   // beim Beenden fuer x() und y() Null ausgelesen (siehe auch UFGdesigner::fuellen())
   this->move(200-1, 200-1);
   this->move(200, 200);
}


// Destruktor
//------------
UFGdesigner::~UFGdesigner()
{
   delete werkzeug;
}


//-------------------------------------------------------
int UFGdesigner::rasten(int z)
{
   return (z+5)/10*10;
}


//----------------------------------------------------.------------------------.
//                                                    | Start Objekt aufziehen |
//                                                    '------------------------'
void UFGdesigner::mousePressEvent( QMouseEvent* e )
{
   if(timer->isActive())   // =Kill (Objekt loeschen) ist aktiviert
   {
      timerled->off();
      timer->stop();
      tasteLoeschen->setText("Kill");
      tasteLabel->setDisabled(false);
      tasteLineEdit->setDisabled(false);
      tastePushButton->setDisabled(false);
      tasteLed->setDisabled(false);
   }

   if(wunschobjekt > 0)   // ein Objekt soll "aufgezogen" werden
   {
      nummer += 1;
      anzahlObjekte += 1;
      objektTyp[nummer] = wunschobjekt;   //1=QLabel, 2=QPushButton, 3=QLineEdit, 4=BLed

      switch(wunschobjekt)
      {
      case 1: // =QLabel
//         objekt = (QWidget **)realloc(objekt, 100 * sizeof(QWidget*));
//         objekt[nummer] = (QWidget *)malloc(sizeof(QWidget));

         objekt[nummer]      = new UFGLabel(this, nummer, nameLabel->text());
         objektName[nummer]  = nameLabel->text();
         objektText[nummer]  = nameLabel->text();
         objektFarbe[nummer] = "Qt::yellow";   // Vorgabe
         connect(objekt[nummer], SIGNAL(sendeNummer(int)), SLOT(signalauswertung(int)));
         break;
      case 2:
         objekt[nummer]     = new UFGPushButton(this, nummer, namePushButton->text());
         objektName[nummer] = namePushButton->text();
         objektText[nummer] = namePushButton->text();
         connect(objekt[nummer], SIGNAL(sendeNummer(int)), SLOT(signalauswertung(int)));
         break;
      case 3:
         objekt[nummer]     = new UFGLineEdit(this, nummer, nameLineEdit->text());
         objektName[nummer] = nameLineEdit->text();
         objektText[nummer] = nameLineEdit->text();
         connect(objekt[nummer], SIGNAL(sendeNummer(int)), SLOT(signalauswertung(int)));
         break;
      case 4:
         objekt[nummer]     = new UFGLed(this, nummer, nameLed->text());
         objektName[nummer] = nameLed->text();
//         objektText[nummer] = nameLed->text();
         objektText[nummer] = "Qt::green"; // Vorgabe
         connect(objekt[nummer], SIGNAL(sendeNummer(int)), SLOT(signalauswertung(int)));
         break;
      }
      pos0 = e->pos();             // add point

      objekt[nummer]->setGeometry(rasten(pos0.x()), rasten(pos0.y()), 0, 0);
      objekt[nummer]->show();
   }
}


//-------------------------------------------------------
void UFGdesigner::mouseMoveEvent( QMouseEvent* e )
{
   if(wunschobjekt > 0)  // nur beim Aufziehen des Objekts
   {
      pos2 = e->pos();
      objekt[nummer]->setGeometry(rasten(pos0.x()), rasten(pos0.y()), rasten(e->x()-pos0.x()), rasten(e->y()-pos0.y()) );
      //update();
   }
}


//----------------------------------------------------------.------------------.
//                                                          | Objekt aufziehen |
//                                                          | abschliessen     |
//                                                          '------------------'
void UFGdesigner::mouseReleaseEvent( QMouseEvent* e)
{
//      UFGbasis* x = (UFGbasis*) objekt[nummer]; //
   if(wunschobjekt>0)
   {
      UFGbasis* brilleUFGBasis = (UFGbasis*) objekt[nummer]; // (c)Jonas

      switch(wunschobjekt)
      {
         case 1: objekt[nummer]->setObjectName(nameLabel->text());        // Label
                 nameLabel->hide();
                 tasteLabel->show();
                    //tasteLabel->setDisabled(false);
                    tastePushButton->setDisabled(false);
                    tasteLineEdit->setDisabled(false);
                    tasteLed->setDisabled(false);
                 break;
         case 2: objekt[nummer]->setObjectName(namePushButton->text());   // PushButton
                 namePushButton->hide();
                 tastePushButton->show();
                    tasteLabel->setDisabled(false);
                    //tastePushButton->setDisabled(false);
                    tasteLineEdit->setDisabled(false);
                    tasteLed->setDisabled(false);
//                    objektPushButton->fertigAufziehen();
                 break;
         case 3: objekt[nummer]->setObjectName(nameLineEdit->text());     // LineEdit
                 nameLineEdit->hide();
                 tasteLineEdit->show();
                    tasteLabel->setDisabled(false);
                    tastePushButton->setDisabled(false);
                    //tasteLineEdit->setDisabled(false);
                    tasteLed->setDisabled(false);
  //                  objektLineEdit->fertigAufziehen();
                 break;
         case 4: objekt[nummer]->setObjectName(nameLed->text());          // Led
                 nameLed->hide();
                 tasteLed->show();
                    tasteLabel->setDisabled(false);
                    tastePushButton->setDisabled(false);
                    tasteLineEdit->setDisabled(false);
                    //tasteLed->setDisabled(false);
//                    objektLed->fertigAufziehen();
                 break;
      }

     brilleUFGBasis->fertigAufziehen();

      pos1 = e->pos();
      wunschobjekt = 0;

      tasteLoeschen->setDisabled(false);
      tasteEsc->setDisabled(true);
   } // Ende if
}


//--------------------------------------------------.--------------------------.
//                                                  | Klick auf Werkzeugkasten |
//                                                  | auswerten                |
//                                                  '--------------------------'

// esc-Taste
//-----------
void UFGdesigner::esc()
{
   wunschobjekt = 0;
   tasteEsc->setDisabled(true);
   tasteLabel->show();
      tasteLabel->setDisabled(false);
      nameLabel->hide();
   tastePushButton->show();
      tastePushButton->setDisabled(false);
      namePushButton->hide();
   tasteLineEdit->show();
      tasteLineEdit->setDisabled(false);
      nameLineEdit->hide();
   tasteLed->show();
      tasteLed->setDisabled(false);
      nameLed->hide();
   tasteLoeschen->setDisabled(false);
}


// Label-Taste
//-------------
void UFGdesigner::label()
{
   wunschobjekt = 1;
   tasteLabel->hide();
      tasteEsc->setDisabled(false);
      //tasteLabel->setDisabled(true);
      tastePushButton->setDisabled(true);
      tasteLineEdit->setDisabled(true);
      tasteLed->setDisabled(true);
   nameLabel->setText("label" + QString::number(nummer + 1)); //ergibt Objektname
   nameLabel->show();
   activateWindow();
   tasteLoeschen->setDisabled(true);
}


// PushButton-Taste
//------------------
void UFGdesigner::pushButton()
{
   wunschobjekt = 2;
   tastePushButton->hide();
      tasteEsc->setDisabled(false);
      tasteLabel->setDisabled(true);
      //tastePushButton->setDisabled(true);
      tasteLineEdit->setDisabled(true);
      tasteLed->setDisabled(true);
   namePushButton->setText("pushButton" + QString::number(nummer + 1));
   namePushButton->show();
   activateWindow();
   tasteLoeschen->setDisabled(true);
}


// LineEdit-Taste
//----------------
void UFGdesigner::lineEdit()
{
   wunschobjekt = 3;
   tasteLineEdit->hide();
      tasteEsc->setDisabled(false);
      tasteLabel->setDisabled(true);
      tastePushButton->setDisabled(true);
      tasteLed->setDisabled(true);
   nameLineEdit->setText("lineEdit" + QString::number(nummer+1));
   nameLineEdit->show();
   activateWindow();
   tasteLoeschen->setDisabled(true);
}


// LED-Taste
//-----------
void UFGdesigner::led()
{
   wunschobjekt = 4;
   tasteLed->hide();
      tasteEsc->setDisabled(false);
      tasteLabel->setDisabled(true);
      tastePushButton->setDisabled(true);
      tasteLineEdit->setDisabled(true);
   nameLed->setText("led" + QString::number(nummer + 1));
   nameLed->show();
   activateWindow();
   tasteLoeschen->setDisabled(true);
}


// Loeschen-Taste
//----------------
void UFGdesigner::loeschen()
{
   if(timer->isActive())
   {
      timerled->off();
      timer->stop();
      tasteLoeschen->setText("Kill");
      tasteLoeschen->setText("Kill-off");
      tasteLabel->setDisabled(false);
      tastePushButton->setDisabled(false);
      tasteLineEdit->setDisabled(false);
      tasteLed->setDisabled(false);
   }
   else
   {
      timer->start(321);
      tasteLoeschen->setText("Kill-off");
      tasteLabel->setDisabled(true);
      tastePushButton->setDisabled(true);
      tasteLineEdit->setDisabled(true);
      tasteLed->setDisabled(true);
   }
}


// Blink-Takt fuer Loesch-LED
//----------------------------
void UFGdesigner::takt()
{
   timerled->toggle();
}


//--------------------------------------------------------------------------
// wird aufgerufen, wenn Objekt Signal sendeNummer(int objektNummer) sendet
// Objekt sendet sendeNummer(int objektNummer), wenn es angeklickt wird
//--------------------------------------------------------------------------
void UFGdesigner::signalauswertung(int objektNummer)
{
qWarning("UFGdesigner::signalauswertung");
   // objektNummer ist das Objekt das das Signal gesendet hat
   // Objekt loeschen, wenn Timer aktiv
   if(timer->isActive())
   {
      // nun gewuenschtes Objekt loeschen und Array packen
      while(objektNummer < anzahlObjekte)
      {
         // gewuenschtes Objekt loeschen
         delete objekt[objektNummer];

         // alle folgenden Objekte runterschaufeln

         // 1. Objekt
         // 1=QLabel, 2=QPushButton, 3=QLineEdit, 4=BLed
         switch(objektTyp[objektNummer + 1])
         {
            case 1: objekt[objektNummer] = new UFGLabel(this, objektNummer, objektText[objektNummer + 1]);
                    break;
            case 2: objekt[objektNummer] = new UFGPushButton(this, objektNummer, objektText[objektNummer + 1]);
                    break;
            case 3: objekt[objektNummer] = new UFGLineEdit(this, objektNummer, objektText[objektNummer + 1]);
                    break;
            case 4: objekt[objektNummer] = new UFGLed(this, objektNummer);
                    break;
         }
         // 2. ObjektName
         objektName[objektNummer]  = objektName[objektNummer + 1];
         // 3. ObjektText
         objektText[objektNummer]  = objektText[objektNummer+1];
         // 4. ObjektTyp
         objektTyp[objektNummer]   = objektTyp[objektNummer+1];
         // 5. ObjektFarbe
         objektFarbe[objektNummer] = objektFarbe[objektNummer+1];

         objekt[objektNummer]->setGeometry( objekt[objektNummer+1]->geometry() );
         objekt[objektNummer]->show();
         connect(objekt[objektNummer], SIGNAL(sendeNummer(int)), SLOT(signalauswertung(int)));
         objektNummer += 1;
      }

      // Durch geloeschtes Objekt freigewordenen Speicher loeschen
      // Es muss nur der Speicher des letzten Objekts geloescht werden
      delete objekt[anzahlObjekte];
      anzahlObjekte -= 1;
      nummer = anzahlObjekte;

      timerled->off();
      timer->stop();

      tasteLoeschen->setText("Kill");
      tasteLabel->setDisabled(false);
      tasteLineEdit->setDisabled(false);
      tastePushButton->setDisabled(false);
      tasteLed->setDisabled(false);
   }
   else //Edit-Feld im Werkzeugkasten aktivieren
   {
      if(nameLabel->isHidden()) //Editmode einschalten
      {
         tasteLabel->hide();
         nameLabel->setText(objektName[objektNummer]);
         nameLabel->show();
         editObjekt = objektNummer;
      }
      else //Editmode ausschalten und name uebernehmen
      {
         tasteLabel->show();
         nameLabel->hide();
         objektName[editObjekt] = nameLabel->text();
         objekt[editObjekt]->setObjectName(nameLabel->text());
      }
   }
}


//-------------------------------------------------------
int UFGdesigner::getAnzahlObjekte()
{
   return anzahlObjekte;
}


//-------------------------------------------------------
int UFGdesigner::getObjektTyp(int n)
{
   return objektTyp[n]; // ->getObjektTyp();
}


//-------------------------------------------------------
QString UFGdesigner::getName(int n)
{
   return objektName[n]; // ->getObjektName[nummer];
}


//-------------------------------------------------------
QString UFGdesigner::getObjektText(int n)
{
   return objektText[n];
}


//------------------------------------------------------.----------------------.
//                                                      | GUI mit den bereits  |
//                                                      | vorhandenen Objekten |
//                                                      | fuellen              |
//                                                      '----------------------'
int UFGdesigner::fuellen(QString q)
{
   QString puffer_h;   // Puffer fuer .h-Datei
                       // dient nur zum Feststellen ob /* <UFGdesigner> */ enthalten ist

   // .h einlesen bis /* <UFGdesigner> */ oder EOF
   //----------------------------------------------
   QFile file_h(q + ".h");   // einlesen
   if(!file_h.open(QIODevice::ReadOnly))
      return -1;
   QTextStream stream_h(&file_h);
   do   // erster Block = #include-Dateien
   {
      puffer_h = stream_h.readLine();   // Inhalt interessiert nicht
      if( stream_h.atEnd() )
      {
         file_h.close();
         return 0;   // nix drin
      }
   }while( puffer_h.lastIndexOf("/* <UFGdesigner> */", -1) < 0 );


   // Also Eintragungen vorhanden
   //-----------------------------
   QString puffer;   // Puffer fuer .cpp-Datei

   // .cpp einlesen bis /* <UFGdesigner> */
   //---------------------------------------
   QFile file(q + ".cpp");
   if(!file.open(QIODevice::ReadOnly))
      return -2;   // Fehler
   QTextStream stream(&file);
   do
   {
      puffer = stream.readLine();
      if( stream.atEnd() )
         return -3;   // Fehler
   }while( puffer.lastIndexOf("/* <UFGdesigner> */", -1) < 0 );


   // Text /* <UFGdesigner> */ gefunden
   // und los gehts

   // Zeile: this->setGeometry(...
   //------------------------------
   puffer = stream.readLine();
   if(puffer.contains("this->setGeometry(", Qt::CaseInsensitive) == 0)
   {
      // Struktur veraendert -> Fehler
      werkzeug->hide();
      this->hide();
      return -4;
   }

   // nun Geometriedaten auslesen - setGeometry(10,10,100,70);
   //----------------------------------------------------------
   puffer = puffer.mid( puffer.indexOf("(") + 1 );
   int x0 = puffer.left(puffer.indexOf(",")).toInt();

   puffer = puffer.mid( puffer.indexOf(",") + 1 );
   int y0 = puffer.left(puffer.indexOf(",")).toInt();

   puffer = puffer.mid( puffer.indexOf(",") + 1 );
   int b = puffer.left(puffer.indexOf(",")).toInt();

   puffer = puffer.mid( puffer.indexOf(",") + 1 );
   int h = puffer.left(puffer.indexOf(")")).toInt();

   this->setGeometry(x0, y0, b, h);

   // ohne die folgenden beiden Zeilen wird beim Beenden
   // ohne das GUI bewegt zu haben
   // fuer x() und y() Null ausgelesen (siehe auch im Konstruktor)
   this->move(x0-1, y0-1);
   this->move(x0, y0);

   // Leerzeile
   //-----------
   puffer = stream.readLine().trimmed();
   if(puffer.length() != 0)
   {
      // Struktur veraendert -> Fehler
      werkzeug->hide();
      this->hide();
      return -5;
   }

   // jetzt alle Objekte einlesen
   //-----------------------------
   int setPaletteIndikator = 0; // falls bei QLabel Zeile setPalette() = Farbsteuerung nicht vorhanden
   do
   {
      puffer = stream.readLine().trimmed();   // Zeile einlesen
      if( puffer.indexOf("/* </UFGdesigner> */") >= 0)
         break;

      nummer += 1;
      objektFarbe[nummer]=landestext->getText("keine");   // "keine" - fuer Objekte ohne Farbsteuerung
                                                          // Farbsteuerung nur bei Objekt QLabel
      // Objekt-Name
      //-------------
      QString istName = puffer.left(puffer.lastIndexOf("=", -1)).trimmed();
      objektName[nummer] = istName;

      // Objekt-Art=QLabel, QPushButton, QLineEdit oder BLed
      //-----------------------------------------------------
      int objektArt = 0;
      if( puffer.indexOf(" = new QLabel(")      >= 0) objektArt = 1;  // QLabel
      if( puffer.indexOf(" = new QPushButton(") >= 0) objektArt = 2;  // QPushButton
      if( puffer.indexOf(" = new QLineEdit(")   >= 0) objektArt = 3;  // QLineEdit
      if( puffer.indexOf(" = new BLed(")        >= 0) objektArt = 4;  // QLed

      if(objektArt == 0)   // unbekanntes Objekt
      {
         // Struktur veraendert -> Fehler
         werkzeug->hide();
         this->hide();
         return -6;
      }

      // Text-Eigenschaft des Objekts bestimmen
      // bzw. Farbe der Led
      //----------------------------------------
      puffer             = puffer.mid( puffer.indexOf("(") + 2 );
      QString istText    = puffer.left(puffer.indexOf(",") - 1);
      objektText[nummer] = istText;


      // Auswertung und Objekt erzeugen
      //--------------------------------
      switch(objektArt)
      {
      case 1:   //---QLabel---
         objekt[nummer] = new UFGLabel(this, nummer, istText);
         objektTyp[nummer] = 1;   // 1=QLabel, 2=QPushButton, 3=QLineEdit, 4=BLed

         // setPalette(Qt::...
         // koennte aber auch geloescht sein

         // Beispiel
         //----------
         // papier_links->setPalette(Qt::yellow);
         // papier_links->setAutoFillBackground(true); // Hintergrund automatisch zeichnen, wenn notwendig

         puffer = stream.readLine().trimmed();
         setPaletteIndikator=1;
         if( puffer.indexOf("setPalette(Qt::")>=0 )  // gefunden
         {
            // Farbe bestimmen
            QString c = puffer.mid(puffer.indexOf("(")+1);
            c = c.left(c.indexOf(")")); // z.B. Qt::yellow
            objektFarbe[nummer]=c;

            // Beispiel
            // objekt[nummer]->setPalette(Qt::yellow);
            if(c=="Qt::white")       objekt[nummer]->setPalette(Qt::white);
            if(c=="Qt::black")       objekt[nummer]->setPalette(Qt::black);
            if(c=="Qt::red")         objekt[nummer]->setPalette(Qt::red);
            if(c=="Qt::darkRed")     objekt[nummer]->setPalette(Qt::darkRed);
            if(c=="Qt::green")       objekt[nummer]->setPalette(Qt::green);
            if(c=="Qt::darkGreen")   objekt[nummer]->setPalette(Qt::darkGreen);
            if(c=="Qt::blue")        objekt[nummer]->setPalette(Qt::blue);
            if(c=="Qt::darkBlue")    objekt[nummer]->setPalette(Qt::darkBlue);
            if(c=="Qt::cyan")        objekt[nummer]->setPalette(Qt::cyan);
            if(c=="Qt::darkCyan")    objekt[nummer]->setPalette(Qt::darkCyan);
            if(c=="Qt::magenta")     objekt[nummer]->setPalette(Qt::magenta);
            if(c=="Qt::darkMagenta") objekt[nummer]->setPalette(Qt::darkMagenta);
            if(c=="Qt::yellow")      objekt[nummer]->setPalette(Qt::yellow);
            if(c=="Qt::darkYellow")  objekt[nummer]->setPalette(Qt::darkYellow);
            if(c=="Qt::gray")        objekt[nummer]->setPalette(Qt::gray);
            if(c=="Qt::darkGray")    objekt[nummer]->setPalette(Qt::darkGray);
            if(c=="Qt::lightGray")   objekt[nummer]->setPalette(Qt::lightGray);
            objekt[nummer]->setAutoFillBackground(true);
            setPaletteIndikator=0;   // d.h. ist vorhanden
                                     // also fuer setGeometry() nochmal einlesen
            // ->setAutoFillBackground(true); muss dann kommen
            puffer = stream.readLine().trimmed();
            if(puffer.indexOf("setAutoFillBackground(true)")<0)
            {
               //Struktur veraendert -> Fehler
               werkzeug->hide();
               this->hide();
               return -7;
            }
         }
         break;
      case 2:   //---QPushButton---
         objekt[nummer] = new UFGPushButton(this,nummer,istText);
         objektTyp[nummer]=2;   // 1=QLabel, 2=QPushButton, 3=QLineEdit, 4=BLed
         break;
      case 3:   //---QLineEdit---
         objekt[nummer] = new UFGLineEdit(this,nummer,istText);
         objektTyp[nummer]=3;   // 1=QLabel, 2=QPushButton, 3=QLineEdit, 4=BLed
         break;
      case 4:   //---BLed---
         // 1=QLabel, 2=QPushButton, 3=QLineEdit, 4=BLed 

         // zunaechst die Farbe bestimmen
         // Vorgabe: Es muss immer die Farbe kommen
         puffer = stream.readLine().trimmed();       // Beispiel: led1->setColor(Qt::red);

         if( puffer.indexOf("setColor(Qt::") >= 0 )  // gefunden
         {
            // Farbe bestimmen
            QString c = puffer.mid(puffer.indexOf("(")+1);
            c = c.left(c.indexOf(")")); // z.B. Qt::yellow

            objektFarbe[nummer] = c;
            istText = c; // die text-Eigenschaft wird fuer die Farbe missbraucht bei BLed

            objektText[nummer] = istText;
            objekt[nummer] = new UFGLed(this, nummer, istText);

            setPaletteIndikator=0;   // setGeometry() nochmal einlesen aktivieren

            objektTyp[nummer] = 4; // Jetzt gibts die Led also Wert setzen
         }
         else
         {
            //Struktur veraendert -> Fehler
            werkzeug->hide();
            this->hide();
            return -8;
         }
         break;
      }


      // setGeometry()
      //---------------
      if(setPaletteIndikator == 0)
      {
         puffer = stream.readLine();   // setGeometry(...)
      }
      setPaletteIndikator = 0;

      puffer = puffer.mid( puffer.indexOf("(") + 1 );
          x0 = puffer.left( puffer.indexOf(",") ).toInt();

      puffer = puffer.mid( puffer.indexOf(",") + 1 );
          y0 = puffer.left( puffer.indexOf(",") ).toInt();

      puffer = puffer.mid( puffer.indexOf(",") + 1 );
           b = puffer.left( puffer.indexOf(",") ).toInt();

      puffer = puffer.mid( puffer.indexOf(",") + 1 );
           h = puffer.left( puffer.indexOf(")") ).toInt();

      objekt[nummer]->setGeometry(x0, y0, b, h);


qWarning("99999");


      //Anfasser positionieren
      UFGbasis* brilleUFGBasis = (UFGbasis*) objekt[nummer]; // (c)Jonas
qWarning("99999-1");

      brilleUFGBasis->fertigAufziehen();




qWarning("8888");



      // show()
      //--------
      puffer = stream.readLine();   // show() wird nicht ausgewertet, es muss nur da sein
      if(puffer.contains("->show();",Qt::CaseInsensitive)==0)
      {
         // Struktur veraendert -> Fehler
         werkzeug->hide();
         this->hide();
         return -9;
      }
      objekt[nummer]->show();
      connect(objekt[nummer], SIGNAL(sendeNummer(int)), SLOT(signalauswertung(int)));

      puffer = stream.readLine();   // Leerzeile
      if(puffer.length() != 0)
      {
         // Struktur veraendert -> Fehler
         werkzeug->hide();
         this->hide();
         return -10;
      }

   }while(1);
   file.close();
   anzahlObjekte = nummer;
   return 0;
}


// nicht auf [X] reagieren
//-------------------------
void UFGdesigner::closeEvent(QCloseEvent *e)
{
qDebug() << "Ich will nicht :o";
   e->ignore();
}


QString UFGdesigner::farbe(int n)
{
   return objektFarbe[n];
}

