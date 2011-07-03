/* --------- */
/* ufgi18n.h */
/* --------- */

#ifndef UFGI18N_H
#define UFGI18N_H

#include <qwidget.h>
#include <qstring.h>
#include <qfile.h>
#include <QTextStream>
#include <QtDebug>

class UFGi18n
{
public:
   UFGi18n();
  ~UFGi18n();

private:
   int nZeilen;             // Anzahl der Zeilen
   QString textzeile[250];  // die einzelnen Zeilen
   int nSprachdateiGeladen;

public:
   QString getText(QString);

};

#endif
