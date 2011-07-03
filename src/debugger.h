/*------------*/
/* debugger.h */
/*------------*/

/*------------------------------*/
/* Implemented by Jonas Gehring */
/*------------------------------*/

#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <qlabel.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qstring.h>
#include <qevent.h>
#include <QComboBox>
//#include <QTextEdit>
#include <QPlainTextEdit>

#include <qtimer.h>
#include <stdlib.h>
#include <stdio.h>

#include "ufgi18n.h"
#include "arbeiter.h"

class Debugger : public QWidget
{
    Q_OBJECT
public:
    Debugger(QWidget *parent, QPlainTextEdit *meldungsFenster, int projektTyp, QString projektVerzeichnis, QString binary);
    ~Debugger();

    void setzeZeile(int);
    void setzeDatei(QString);

private slots:
    void senden();
    void einzelschritt();
    void weiter();
    void speichern();
    void entfernen();
    void start();
    void stop();
    void leseAusgabe();

    void closeEvent(QCloseEvent*);    //wird benoetigt um Klick auf [X] abzufangen
    void keyPressEvent(QKeyEvent*);

signals:
    void springeZeile(QString,QString);
    void beendeDebugger();

private:
    int         zeile;
    QString     datei;
    CArbeiter   *arbeiter;
    UFGi18n     *landestext;
    QLabel      *txtBreakpoints;
    QLabel      *txtBefehl;
    QLineEdit   *befehl;
    QPushButton *tasteSenden;
    QLabel      *meldung;
    QPushButton *tasteWeiter;
    QPushButton *tasteEinzelschritt;
    QComboBox   *breakpoints;
    QPushButton *tasteSpeichern;
    QPushButton *tasteEntfernen;
    QPushButton *tasteBeenden;
    QPushButton *tasteStart;
    QPushButton *tasteStop;
//    QTextEdit   *meldungsFenster;
    QPlainTextEdit   *meldungsFenster;
    QTimer      *runtimer;
};

#endif

