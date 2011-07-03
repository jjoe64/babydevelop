#!/bin/sh

clear

echo "-----------------------------"
echo "BabyDevelop 10 - Installation"
echo "-----------------------------"
echo ""


# Test ob gcc installiert ist
gcc -dumpversion >/dev/null 2>&1
if [ $? -ne 0 ] ;
   then #--- kein gcc gefunden ---
   echo gcc not found.
   echo It is not possible to install BabyDevelop.
   echo "Perhaps"
   echo "apt-get install qt4-dev-tools qt4-doc-html qt4-qtconfig g++ make libqt4-dev gdb"
   echo "will solve the problem."
   exit 1 ;
fi
echo gcc found


# Test ob g++ installiert ist
g++ -dumpversion >/dev/null 2>&1
if [ $? -ne 0 ] ;
   then #--- kein g++ gefunden ---
   echo ""
   echo No g++ found.
   echo It is not possible to install BabyDevelop.
   echo "Perhaps"
   echo "apt-get install qt4-dev-tools qt4-doc-html qt4-qtconfig g++ make libqt4-dev gdb"
   echo "will solve the problem."
   exit 1 ;
fi
echo g++ found


# Test ob Qt-Dokumentation installiert ist
if [ -f /usr/share/qt4/doc/html/index.html ] ; then
   echo Qt-Dokumentation found
else
   echo ""
   echo Qt-Dokumentation not found :\(
   echo It\'s BabyDevelop not possible to show Qt-Help.
   echo "Perhaps"
   echo "apt-get install qt4-doc-html"
   echo "will solve the problem."
fi


# Test ob Qt-Header-Dateien installiert sind
if [ -f /usr/include/qt4/Qt/qapplication.h ] ; then
   echo Qt-Header-Files found
else
   echo ""
   echo Error: Qt-Header-Files not found :\(
   echo It\'s not possible to compile Qt-Programs.
   echo "Perhaps"
   echo "apt-get install qt4-dev-tools qt4-doc-html qt4-qtconfig g++ make libqt4-dev gdb"
   echo "will solve the problem."
   exit 1 ;
fi


# Test ob Qt-so-Dateien vorhanden sind
if [ -f /usr/lib/libQtCore.so ] ; then
   echo Qt-so-Files found
else
   echo ""
   echo Error: Qt-so-Files not found :\(
   echo It\'s not possible to compile Qt-Programs.
   echo "Perhaps"
   echo "apt-get install qt4-dev-tools qt4-doc-html qt4-qtconfig g++ make libqt4-dev gdb"
   echo "will solve the problem."
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
   echo moc-Version 4 found
else
   echo ""
   echo Error: No moc-Version 4 found :\(
   echo It\'s not possible to compile Qt-Programs.
   echo "Perhaps"
   echo "apt-get install qt4-dev-tools qt4-doc-html qt4-qtconfig g++ make libqt4-dev gdb"
   echo "will solve the problem."
   echo "Perhaps did not show the link \"/etc/alternatives/moc\" to \"/usr/bin/moc-qt4\""
   exit 1 ;
fi

echo ""

echo It seems that all needed things are there - let\'s go...
echo ""

echo ""
#----------------------
#wirklich installieren?
#----------------------
echo "This program will install BabyDevelop on your computer."
echo "They need in addition the root password!"
echo "You would like to install for BabyDevelop?"
echo "Please select..."
echo " 1 = yes"
echo " 0 = no"
read antwort
if [ $antwort -ne 1 ] ;
   then echo "Installation by user input broken off."
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
     echo "They need root-right"
     echo "to the installation of BabyDevelop"
     echo "Installation broken off.  Missing rights."
     exit 1 ;
fi

scripte/install3_en.sh
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

