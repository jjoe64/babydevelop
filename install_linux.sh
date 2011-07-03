#!/bin/sh

#-------------------------------------------------------
#install.sh Version 10.0
#Aufgabe: Sprache waehlen
#         scripte/install2_xx.sh sprachabhaengig starten
#-------------------------------------------------------

clear

echo "-----------------------------"
echo "BabyDevelop 10 - Installation"
echo "-----------------------------"
echo ""


#---------------
#Sprache waehlen
#---------------
echo "en-Choose \"1\" for english language"
echo "de-Waehle \"2\" fuer deutsche Sprache"
echo "es-Elija  \"3\" para la lengua espanola"
read sprache

if [ $sprache -eq 1 ] ; then sh scripte/install2_en.sh ; antwort=$? ; fi
if [ $sprache -eq 2 ] ; then sh scripte/install2_de.sh ; antwort=$? ; fi
if [ $sprache -eq 3 ] ; then sh scripte/install2_es.sh ; antwort=$? ; fi

if [ $antwort -ne 0 ] ;
then
   if [ $sprache -eq 1 ] ; then echo Installation broken.      ; fi
   if [ $sprache -eq 2 ] ; then echo Installation abgebrochen. ; fi
   if [ $sprache -eq 3 ] ; then echo Installation broken.      ; fi
fi ;

if [ $sprache -eq 1 ] ; then echo "End of program - Please press Enter-Key" ; fi
if [ $sprache -eq 2 ] ; then echo "Programmende - Bitte Eingabetaste betaetigen" ; fi
if [ $sprache -eq 3 ] ; then echo "End of program - Please press Enter-Key" ; fi
read q


