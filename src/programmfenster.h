/*-------------------*/
/* programmfenster.h */
/*-------------------*/

#ifndef PROGRAMMFENSTER_H
#define PROGRAMMFENSTER_H

#include <QWidget>

class ProgrammFenster : public QWidget
{
   Q_OBJECT
public:
   ProgrammFenster(QWidget* parent=0); // Konstruktor
  ~ProgrammFenster();                  // Destruktor
};

#endif
