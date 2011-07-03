/* suchen.h */

#ifndef SUCHEN_H
#define SUCHEN_H

#include "/opt/babyDevelop/programmfenster.h"
#include <qdir.h>


class Suchen : public ProgrammFenster
{
   Q_OBJECT
public:
   Suchen (QString);   /* Konstruktor */
  ~Suchen ();          /* Destruktor  */

private:
   QString derBegriff;
};

#endif
