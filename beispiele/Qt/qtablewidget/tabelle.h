/* tabelle.h */

#ifndef TABELLE_H
#define TABELLE_H

#include <QTableWidget>
#include <QMouseEvent>

class Tabelle : public QTableWidget
{
   Q_OBJECT
public:
   Tabelle(int, int, QWidget*);   /* Konstruktor */
  ~Tabelle();                     /* Destruktor  */

public slots:
   void mousePressEvent(QMouseEvent*);
};

#endif
