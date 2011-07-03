/* gui.h */

#ifndef GUI_H
#define GUI_H

#include <qwidget.h>

#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlistwidget.h>
#include <qfile.h>
#include <qdir.h>
#include <qmessagebox.h>
#include <qlabel.h>

#define MAXLIEDER 1024

class GUI : public QWidget
{
   Q_OBJECT
public:
   GUI (QWidget* elternWidget=0);   /* Konstruktor */
  ~GUI ();                          /* Destruktor  */

private:
   QString pfad[MAXLIEDER];

private:
   QLabel*      copy;
   QLineEdit*   zeile;
   QPushButton* tasteFinde;
   QPushButton* tasteEnde;
   QPushButton* tasteInfo;
   QPushButton* tastePlay;
   QListWidget* tabelle;

private slots:
   void nimmText();
   void auswahlLied(QListWidgetItem*);
   void spiele();
   void ende();
   void informieren();

public:
   void ladeListe();

signals:
   void finde(QString);
   void ladeLied(QString);
   void sigEnde();
};

#endif
