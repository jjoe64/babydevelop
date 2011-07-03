/* btabelle.h */

#ifndef BTABELLE_H
#define BTABELLE_H

#include <qwidget.h>
#include <QHeaderView> //Header fuer Spalten-/Zeilenkoepfe entfernen koennen
#include <QStringList>
#include <QTableWidget>
#include <qicon.h>
#include <qlist.h>
#include <QKeyEvent>

class BTabelle : public QWidget
{
   Q_OBJECT
public:
   BTabelle(int, int, QWidget *elternObjekt = 0);   /* Konstruktor */
  ~BTabelle();                                      /* Destruktor  */

private:
   int breite;
   int hoehe;
   QColor bg; // Hintergrundfarbe
   QColor fg; // Vordergrundfarbe

private:
   QTableWidget* t;

private slots:
   void zelleKlick(int, int);
   void keyPressEvent(QKeyEvent*);   /* virtuelle Methode */

public slots:
   void setzeText(int, int, QString);
   void setzeAnzahlReihen(int);
   void setzeAnzahlSpalten(int);
   void setzeSpaltenbreite(int, int);
   void setzeReihenhoehe(int, int);
   void setzeTabellenbreite(int);
   void setzeTabellenhoehe(int);
   void setzeBild(int, int, QIcon);
   void setzeHintergrundfarbe(QColor);
   void setzeVordergrundfarbe(QColor);

signals:
   void angeklicktZelle(int, int);
   void enter();
};

#endif
