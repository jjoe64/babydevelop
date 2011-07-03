/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* vielenamen.h */

#ifndef VIELENAMEN_H
#define VIELENAMEN_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

class VieleNamen
{
public:
   VieleNamen();          /* Konstruktor                    */
   VieleNamen(int);       /* weitere Konstruktoren, die den */
   VieleNamen(int,int);   /* default-Konstruktor überladen  */
  ~VieleNamen();          /* Destruktor                     */
private:
   int laenge;
   int breite;
public:                  /* Anzeigefunktionen                   */
   void zeige(void);     /* Methode 'zeige'                     */
   void zeige(int);      /* weitere gleichnamige Methoden, also */
   void zeige(int,int);  /* Methodenueberladung                 */
   void zeige(float);    /*                                     */
};

#endif
