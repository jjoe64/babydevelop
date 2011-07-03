/* spielen.h */

#ifndef SPIELEN_H
#define SPIELEN_H

#include "/opt/babyDevelop/programmfenster.h"

class Spielen : public ProgrammFenster
{
   Q_OBJECT
public:
   Spielen (QString);   /* Konstruktor */
  ~Spielen ();          /* Destruktor  */

private:
   FILE* fp;
};

#endif
