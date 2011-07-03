/* btabelle.h */

#ifndef BTABELLE_H
#define BTABELLE_H

#include <QHeaderView> //Header fuer Spalten-/Zeilenkoepfe entfernen koennen
#include <QStringList>
#include <QTableWidget>
#include <qicon.h>
#include <qlist.h>

class BTabelle : public QTableWidget
{
   Q_OBJECT
public:
   BTabelle(int, int, QWidget *elternObjekt = 0);   /* Konstruktor */
  ~BTabelle();                                      /* Destruktor  */

private:
   int breite;
   int hoehe;

private:
//   QTableWidget* t;

public slots:
   void setzeText(int, int, QString);
   void setzeAnzahlReihen(int);
   void setzeAnzahlSpalten(int);
   void setzeSpaltenbreite(int, int);
   void setzeReihenhoehe(int, int);
   void setzeTabellenbreite(int);
   void setzeTabellenhoehe(int);
   void setzeBild(int, int, QIcon);
//   void cellClicked(int, int);
};

#endif
