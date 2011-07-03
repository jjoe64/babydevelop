/*---------------*/
/* eingabe_1.cpp */
/*---------------*/

#include "eingabe_1.h"

/* Konstruktor */
Eingabe_1::Eingabe_1(QWidget *elternObjekt, int projektTyp) : QWidget(elternObjekt)
{
   landestext=new UFGi18n();

   this->setFixedSize(280,100);
   this->move(200,200);

   QColor farbe;
      farbe.setHsv(56,132,255);
   QPalette p;
      p.setColor(QPalette::Background, farbe);
   this->setPalette(p);
   this->setBackgroundRole( QPalette::Background );

   if(projektTyp==1)   // C-Projekt
   {
      this->setWindowTitle(landestext->getText("PrototypName eingeben..."));
      txtKlassenName = new QLabel(landestext->getText("PrototypName"), this);
   }
   else   // C++- oder Qt-Projekt
   {
      this->setWindowTitle(landestext->getText("KlassenName eingeben..."));
      txtKlassenName = new QLabel(landestext->getText("KlassenName"), this);
   }
   txtKlassenName->setGeometry(10, 10, 120, 30);
   this->setBackgroundRole(QPalette::Base);
   txtKlassenName->show();

   klassenName = new QLineEdit("", this);
   klassenName->setGeometry(140, 10, 130, 30);
   klassenName->show();
   
   tasteOk = new QPushButton(landestext->getText("Ok"), this);
   tasteOk->setGeometry(170, 50, 100, 40);
   tasteOk->show();
   
   tasteAbbrechen = new QPushButton(landestext->getText("Abbrechen"), this);
   tasteAbbrechen->setGeometry(10, 50, 100, 40);
   tasteAbbrechen->show();
}


/* Destructor */
Eingabe_1::~Eingabe_1()
{
}


/*-----------------------------*/
/*--- Methoden ----------------*/
/*-----------------------------*/
QString Eingabe_1::gibText()
{
   return klassenName->text();
}


// Vorgabetext
//-------------
void Eingabe_1::setzeText(QString text)
{
   klassenName->setText(text);
}


void Eingabe_1::keyPressEvent(QKeyEvent *e)
{
   switch ( e->key() )
   {                     // Hinweis: die Rueckgabecodes der einzelnen Tasten findet man in der "qnamespace.h"
      case Qt::Key_Escape:
         emit abbruch();
         break;
   }
}
