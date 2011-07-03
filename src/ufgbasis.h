/*------------*/
/* ufgbasis.h */
/*------------*/

#ifndef UFGBASIS_H
#define UFGBASIS_H

#include <QString>

#include <qpixmap.h>
#include <qpainter.h>
#include <qwidget.h>
#include <qlabel.h>

#include <qobject.h>

class UFGbasis
{
public:
   UFGbasis();  // Konstruktor
  ~UFGbasis();  // Destruktor

public:
   int     objektNummer;
   int     objektTyp;
   QString objektName;
   int     x0, y0, breite,hoehe;
   int     xgm, ygm, xm, ym;
   int     aktion;

public:
   int      rasten(int);
   void     setNummer(int);
   int      getObjektTyp();
   void     setObjektName(QString);
   QString  getObjektName();
   void fertigAufziehen();

};

#endif
