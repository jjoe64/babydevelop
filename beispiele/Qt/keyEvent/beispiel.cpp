/* beispiel.cpp */

#include "beispiel.h"

/* Konstruktor */
Beispiel::Beispiel() : ProgrammFenster()
{
   this->setGeometry(10,270,130,70);

   qWarning("Druecken Sie eine Taste z.B. x oder Pfeil-links");
}

/* Destruktor */
Beispiel::~Beispiel()
{
}

void Beispiel::keyPressEvent(QKeyEvent *e)
{
qWarning("Taste::keyPressEvent(QKeyEvent *e)");
   //e->accept();  // Annehmen des KeyEvents
   switch ( e->key() )
   {                     // Hinweis: die Rueckgabecodes der einzelnen Tasten findet man in der "qnamespace.h"
      case Qt::Key_Left:     // Pfeiltaste "links" gedueckt?
         qWarning("Taste links");
         break;
      case Qt::Key_X:     // Taste "x" gedueckt?
         qWarning("Taste x");
         break;
   }
}
