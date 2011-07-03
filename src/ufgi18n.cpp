/* ----------- */
/* ufgi18n.cpp */
/* ----------- */
#include <QMessageBox>

#include "ufgi18n.h"

extern QString laenderkuerzel;
extern QString bdpInstallVerzeichnis;

// Konstruktor
//-------------
UFGi18n::UFGi18n()
{
   this->nSprachdateiGeladen = 0;
   QFile file(bdpInstallVerzeichnis+"/babyDevelop/i18n.texte");
   if(!file.open(QIODevice::ReadOnly))
   {
      QString s = bdpInstallVerzeichnis+"/babyDevelop/i18n.texte";
      qWarning("-en-Can not read language-file (%s)!",s.toLatin1().data());
      qWarning("-de-Kann Sprachdatei (%s) nicht lesen!",s.toLatin1().data());
      qWarning("-es-No puede leer el archivo de la lengua inglesa (%s)!",s.toLatin1().data());
      return;
   }

   QTextStream stream(&file);

   //Datei einlesen
   nZeilen=-1;
   do
   {
      nZeilen++;
      textzeile[nZeilen] = stream.readLine();
   }
   while(textzeile[nZeilen]!="@@@@");
   file.close();
   this->nSprachdateiGeladen = 1;
}


UFGi18n::~UFGi18n()
{
}


QString UFGi18n::getText(QString text)
{
   if(laenderkuerzel=="de") // Uebersetzung nicht notwendig
      return text;
   if(nSprachdateiGeladen==0)
      return text;

   //de-Text suchen
   int de=-1;
   do
   {
      de++;
      if(de==nZeilen)
      {
         de=-1;
         break;
      }
   }while(textzeile[de].indexOf("@de@"+text+"$de$")==-1);

   if(de==-1)
   {
      qWarning("Keine Uebersetzung gefunden fuer: >%s<",text.toLatin1().data());
      return text;
   }

   // Uebersetzungstext suchen
   int start, ende;
   start = textzeile[de].indexOf("@"+laenderkuerzel+"@");
   ende  = textzeile[de].indexOf("$"+laenderkuerzel+"$");
   return  textzeile[de].mid(start+4,ende-start-4);
}
