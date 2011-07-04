#!/bin/sh

#-----------------------------------------
#install3_de.sh Version 10.0 fuer Makefile
#Aufgabe: root-User sicherstellen
#         Kompilieren, linken,
#         Installieren
#-----------------------------------------


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


#------------------
#schon installiert?
#------------------
if [ -d /opt/babyDevelop ] ;
   then echo "-----------------------------"
   echo "BabyDevelop 10 - Installation"
   echo "-----------------------------"
   echo ""
   echo ""
   echo "BabyDevelop scheint auf Ihrem Computer schon installiert zu sein!"
   echo "Moechten Sie die vorhandene Version ueberschreiben"
   echo "und BabyDevelop erneut installieren?"
   echo "Bitte waehlen..."
   echo " 1 = ja"
   echo " 0 = nein"
   read antwort
   if [ $antwort -ne 1 ] ;
      then echo "Installation durch Benutzereingabe abgebrochen."
      exit 1 ;
   fi
fi
antwort=


#--------------------------------------------------------
#Quellcode kompilieren
#Ich gehe davon aus, dass hier kein Fehler auftreten kann
#--------------------------------------------------------

echo "-----------------------------"
echo "BabyDevelop 10 - Installation"
echo "-----------------------------"
echo ""

echo ""
cd src
make -f ../makefiles/Makefile_Linux clean
make -f ../makefiles/Makefile_Linux arbeiter
make -f ../makefiles/Makefile_Linux ufgi18n
make -f ../makefiles/Makefile_Linux codeeditor
make -f ../makefiles/Makefile_Linux eingabe_1
make -f ../makefiles/Makefile_Linux import
make -f ../makefiles/Makefile_Linux einstellungen
make -f ../makefiles/Makefile_Linux ufgdesigner
make -f ../makefiles/Makefile_Linux ufgbasis
make -f ../makefiles/Makefile_Linux ufgpushbutton
make -f ../makefiles/Makefile_Linux ufglineedit
make -f ../makefiles/Makefile_Linux ufglabel
make -f ../makefiles/Makefile_Linux ufgled
make -f ../makefiles/Makefile_Linux ufgbild
make -f ../makefiles/Makefile_Linux debugger
make -f ../makefiles/Makefile_Linux programmfenster
make -f ../makefiles/Makefile_Linux bled
make -f ../makefiles/Makefile_Linux main
make -f ../makefiles/Makefile_Linux bdp
make -f ../makefiles/Makefile_Linux highlighter
make -f ../makefiles/Makefile_Linux linken
cd .. ;


#------------
#installieren
#------------

#-------------------------------
#Verzeichnisstruktur und Dateien
#-------------------------------
if [ -d /opt/babyDevelop ] ; then echo \:-\) ; else mkdir /opt/babyDevelop ; fi
cp -R beispiele /opt/babyDevelop
cp -R c++Einfuehrung_programmiererin /opt/babyDevelop
cp -R babyDevelopFAQ /opt/babyDevelop
cp -R babyDevelopQtHilfe /opt/babyDevelop
cp -R einfuehrung /opt/babyDevelop
cp -R bilder /opt/babyDevelop
cp -R icons /opt/babyDevelop
cp readmes/StandDerDinge.txt /opt/babyDevelop
cp icons/babydevelop-icon.png /opt/babyDevelop
cp i18n/i18n.texte /opt/babyDevelop
cp src/programmfenster.h /opt/babyDevelop
cp obj/programmfenster.o /opt/babyDevelop
cp obj/programmfenster.moc.o /opt/babyDevelop
cp babydevelop /opt/babyDevelop
chmod -R ugo+r /opt/babyDevelop
chmod ugo+x /opt/babyDevelop/babydevelop
chmod ugo+x /opt/babyDevelop/beispiele
chmod ugo+x /opt/babyDevelop/bilder
chmod ugo+x /opt/babyDevelop/icons
chmod ugo+x /opt/babyDevelop/c++Einfuehrung_programmiererin
chmod ugo+x /opt/babyDevelop/babyDevelopFAQ
chmod ugo+x /opt/babyDevelop/babyDevelopQtHilfe
chmod ugo+x /opt/babyDevelop/einfuehrung


#--------------
#babydevelop.rc
#--------------
cd rcfiles
cat babydevelop.rc_part1 > /opt/babyDevelop/babydevelop.rc
echo "Sprache=de" >> /opt/babyDevelop/babydevelop.rc
cat babydevelop.rc_part2 >> /opt/babyDevelop/babydevelop.rc
cd ..
chmod ugo+r /opt/babyDevelop/babydevelop.rc


#---------------------------------
#Icon auf dem (Gnome-)User-Desktop
#---------------------------------
echo "-----------------------------"
echo "BabyDevelop 10 - Installation"
echo "-----------------------------"
echo ""

echo ""
echo "Bitte geben Sie Ihren Benutzernamen ein: "
read username ;

if [ -d /home/$username ] ;
then cp rcfiles/BabyDevelop.desktop /home/$username/Desktop
     chown $username.$username /home/$username/Desktop/BabyDevelop.desktop
     chmod ugo+rw  /home/$username/Desktop/BabyDevelop.desktop
     cp rcfiles/babydevelop_user.rc /home/$username/.babydevelop_user.rc
     chown $username.$username /home/$username/.babydevelop_user.rc
     chmod ugo+rw /home/$username/.babydevelop_user.rc

else 
     echo "Es ist in"
     echo "/home"
     echo "kein Userverzeichnis fuer \"$username\"!"
     echo "Kann kein Desktop-Icon erzeugen."
     echo "Kann babydevelop_user.rc nicht in Ihr Homeverzeichnis kopieren!"
     echo "Bitte kopieren Sie die Datei babydevelop_user.rc in Ihr Homeverzeichnis!"
     echo "Bitte Eingabetaste betaetigen"
     read q
fi


#-----------------------
#Icon in IconVerzeichnis
#-----------------------
if [ -d /usr/share/pixmaps ] ;
then cp icons/babydevelop-icon.png /usr/share/pixmaps/ ;
fi


#o-Dateien usw. loeschen
cd src
make -f ../makefiles/Makefile_Linux clean
cd ..


#-----------------------------------------------
#Link von /bin nach /opt/babyDevelop/babydevelop
#-----------------------------------------------
ln -fs /opt/babyDevelop/babydevelop /bin/babydevelop


echo ""
echo "-----------------------------------------------------------------"
echo "Hinweis"
echo "- BabyDevelop starten durch Eingabe von: babydevelop"
echo "- Installiert wurde BabyDevelop im Verzeichnis: /opt/babyDevelop"
echo "- Beispiele finden Sie im Verzeichnis: /opt/babyDevelop/beispiele"
echo "-----------------------------------------------------------------"

