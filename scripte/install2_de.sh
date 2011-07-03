#!/bin/sh

#----------------------------------------------------------------
#install2_de.sh Version 10.0
#Aufgabe: Alle benoetigten Komponenten auf Vorhandensein pruefen
#            g++, moc, Qt-Hilfe, ...
#         Hinweis: "root-Kennwort erforderlich"
#         Frage:   "Wirklich installieren?"
#         Link fuer die Installation erzeugen
#         Wechseln zum root-User
#         install3_xx.sh sprachabhaengig starten
#         Rueckgabe auswerten
#         Link wieder loeschen
#----------------------------------------------------------------
# Rueckgabecodes
#    0 = kein Fehler, alles ok
#    1 = Es ist ein Fehler aufgetreten
#----------------------------------------------------------------

clear

echo "-----------------------------"
echo "BabyDevelop 10 - Installation"
echo "-----------------------------"
echo ""


# Test ob gcc installiert ist
gcc -dumpversion >/dev/null 2>&1
if [ $? -ne 0 ] ;
   then #--- kein gcc gefunden ---
   echo Kein gcc gefunden.
   echo Installation von Babydevelop nicht moeglich.
   echo "apt-get install qt4-dev-tools qt4-doc-html qt4-qtconfig g++ make libqt4-dev gdb"
   echo "koennte das Problem loesen."
   exit 1 ;
fi
echo gcc gefunden


# Test ob g++ installiert ist
g++ -dumpversion >/dev/null 2>&1
if [ $? -ne 0 ] ;
   then #--- kein g++ gefunden ---
   echo ""
   echo Kein g++ gefunden.
   echo Installation von Babydevelop nicht moeglich.
   echo "apt-get install qt4-dev-tools qt4-doc-html qt4-qtconfig g++ make libqt4-dev gdb"
   echo "koennte das Problem loesen."
   exit 1 ;
fi
echo g++ gefunden


# Test ob Qt-Dokumentation installiert ist
if [ -f /usr/share/qt4/doc/html/index.html ] ; then
   echo Qt-Dokumentation gefunden
else
   echo ""
   echo Keine Qt-Dokumentation gefunden :\(
   echo BabyDevelop wird die Qt-Hilfe nicht anzeigen koennen.
   echo "apt-get install qt4-doc-html"
   echo "koennte das Problem loesen."
fi


# Test ob Qt-Header-Dateien installiert sind
if [ -f /usr/include/qt4/Qt/qapplication.h ] ; then
   echo Qt-Header-Dateien gefunden
else
   echo ""
   echo Fehler: Keine Qt-Header-Dateien gefunden :\(
   echo Es koennen keine Qt-Programme kompiliert werden.
   echo "apt-get install qt4-dev-tools qt4-doc-html qt4-qtconfig g++ make libqt4-dev gdb"
   echo "koennte das Problem loesen."
   exit 1 ;
fi


# Test ob Qt-so-Dateien vorhanden sind
if [ -f /usr/lib/libQtCore.so ] ; then
   echo Qt-so-Dateien gefunden
else
   echo ""
   echo Fehler: Keine Qt-so-Dateien gefunden :\(
   echo Es koennen keine Qt-Programme kompiliert werden.
   echo "apt-get install qt4-dev-tools qt4-doc-html qt4-qtconfig g++ make libqt4-dev gdb"
   echo "koennte das Problem loesen."
   exit 1 ;
fi

# Test ob moc-Version 4
# thx to http://www.arachnoid.com/linux/shell_programming.html
m=$(moc -v 2>&1)

# vorne wegradieren
m=${m##* }

# hinten wegradieren
m=${m%%.*}

if [ "$m" = "4" ]; then
   echo moc-Version 4 gefunden
else
   echo ""
   echo Fehler: Keine moc-Version 4 gefunden :\(
   echo Es koennen keine Qt-Programme kompiliert werden.
   echo "apt-get install qt4-dev-tools qt4-doc-html qt4-qtconfig g++ make libqt4-dev gdb"
   echo "koennte das Problem loesen."
   echo "Evtl. zeigt auch Link \"/etc/alternatives/moc\" nicht auf \"/usr/bin/moc-qt4\""
   exit 1 ;
fi

echo ""


echo Es ist wohl alles notwendige installiert - let\'s go...
echo ""


echo ""
#-----------------------
# wirklich installieren?
#-----------------------
echo "Dieses Programm wird BabyDevelop auf Ihrem Rechner installieren."
echo "Sie brauchen dazu das root-Kennwort!"
echo "Moechten Sie BabyDevelop installieren?"
echo "Bitte waehlen..."
echo " 1 = ja"
echo " 0 = nein"
read antwort
if [ $antwort -ne 1 ] ;
   then echo Installation durch Benutzereingabe abgebrochen.
        exit 1
fi
antwort=


#Link erzeugen
###if [ -w /tmp/babyDevelop-tmp ] ; then rm /tmp/babyDevelop-tmp ; fi
###ln -s $PWD /tmp/babyDevelop-tmp


#----------
#root-User?
#----------
if [ `id -u` -ne 0 ] ;
then echo "-----------------------------"
     echo "BabyDevelop 10 - Installation"
     echo "-----------------------------"
     echo ""
     echo ""
     echo "Sie benoetigen root-Rechte"
     echo "zur Installation von BabyDevelop"
     echo "Installation abgebrochen. Fehlende Rechte."
     exit 1 ;
fi

scripte/install3_de.sh
antwort=$?


#--------------------
#Link wieder loeschen
#--------------------
###rm /tmp/babyDevelop-tmp


#---Auswertung---
if [ $antwort -eq 0 ] ;
then
   exit 0 ;
else
   exit 1;
fi

#ProgrammEnde

