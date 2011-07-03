/* ---------------------------------------------------- */
/* Das Projekt ist evtl. schreibgeschuetzt              */
/* Speichern Sie es zunaechst in Ihrem home-Verzeichnis */
/* ---------------------------------------------------- */

/* ---------------------------------------------------- */
/* Beachten Sie den Schalter EscapeSequenzen unter:     */
/* Bearbeiten->Einstellungen->EscapeSequenzen           */
/* ---------------------------------------------------- */

/* thermometer.h */

#ifndef THERMOMETER_H
#define THERMOMETER_H

#include <stdio.h>

#include "funktionen.h"

/* PräcompilerAnweisungen */
#define blau    5
#define gruen   3
#define rot     2
#define normal 12

/* ThermometerSkala anzeigen */
void thermometer (int,int,int);

#endif
