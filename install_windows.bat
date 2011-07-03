@rem BabyDevelop-Installation fuer Windows
@rem --------------------------------------

@echo off

echo.
echo BabyDevelop-Installation - Voraussetzungen
echo -------------------------------------------
echo.
echo 1. Der MinGW-Compiler muss installiert sein.
echo Den bekommst du hier: http://www.mingw.org/
echo.
pause
echo.

echo 2. Qt muss installiert sein.
echo Qt bekommst du hier: http://qt.nokia.com/
echo Anmerkung: Mit Qt 4.6.3 sind _keine_ Anpassungen noetig.
echo            Bei anderen Versionen sind vor der Installation
echo            die Pfade anzupassen in:
echo               win\babydevelop.rc
echo               win\start_babydevelop.bat
echo               makefiles\Makefile_Win32
echo            Siehe LiesMich.txt
echo.
pause
echo.

echo Und los geht's...
echo ----------------------------------------
echo kompilieren...
mingw32-make -f makefiles\Makefile_Win32

rem Verzeichnisstruktur erzeugen
if not exist C:\opt mkdir C:\opt
if not exist C:\opt\babyDevelop mkdir C:\opt\babyDevelop
if not exist C:\opt\babyDevelop\beispiele mkdir C:\opt\babyDevelop\beispiele
if not exist C:\opt\babyDevelop\c++Einfuehrung_programmiererin mkdir C:\opt\babyDevelop\c++Einfuehrung_programmiererin
if not exist C:\opt\babyDevelop\babyDevelopFAQ mkdir C:\opt\babyDevelop\babyDevelopFAQ
if not exist C:\opt\babyDevelop\babyDevelopQtHilfe mkdir C:\opt\babyDevelop\babyDevelopQtHilfe
if not exist C:\opt\babyDevelop\einfuehrung mkdir C:\opt\babyDevelop\einfuehrung
if not exist C:\opt\babyDevelop\bilder mkdir C:\opt\babyDevelop\bilder
if not exist C:\opt\babyDevelop\icons mkdir C:\opt\babyDevelop\icons


rem Verzeichnisse kopieren
xcopy "beispiele" "C:\opt\babyDevelop\beispiele" /E /Y
xcopy "c++Einfuehrung_programmiererin" "C:\opt\babyDevelop\c++Einfuehrung_programmiererin" /E /Y
xcopy "babyDevelopFAQ" "C:\opt\babyDevelop\babyDevelopFAQ" /E /Y
xcopy "babyDevelopQtHilfe" "C:\opt\babyDevelop\babyDevelopQtHilfe" /E /Y
xcopy "einfuehrung"  "C:\opt\babyDevelop\einfuehrung" /E /Y
xcopy "bilder" "C:\opt\babyDevelop\bilder" /E /Y
xcopy "icons" "C:\opt\babyDevelop\icons" /E /Y
xcopy "StandDerDinge.txt" "C:\opt\babyDevelop" /Y


rem Dateien kopieren
copy "icons\babydevelop-icon.png" "C:\opt\babyDevelop" /Y
copy "win\i18n.texte" "C:\opt\babyDevelop" /Y
copy "src\programmfenster.h" "C:\opt\babyDevelop" /Y
copy "obj\programmfenster.o" "C:\opt\babyDevelop" /Y
copy "obj\programmfenster.moc.o" "C:\opt\babyDevelop" /Y
copy "win\babydevelop.rc" "C:\opt\babyDevelop" /Y
copy "win\.babydevelop_user.rc" "%USERPROFILE%" /Y
copy "icons\babydevelop-icon.ico" "C:\opt\babyDevelop" /Y
copy "win\BabyDevelop.lnk" "%ALLUSERSPROFILE%\Desktop" /Y


rem Und nun das liebe BabyDevelop
copy "babydevelop.exe" "C:\opt\babyDevelop" /Y
mingw32-make -f makefiles\Makefile_Win32 clean


rem Notwendige dll's
copy "C:\Qt\4.6.3\bin\QtCore4.dll" "C:\opt\babyDevelop" /Y
copy "C:\Qt\4.6.3\bin\QtGui4.dll" "C:\opt\babyDevelop" /Y


rem Start-Batch
copy "win\start_babydevelop.bat" "C:\opt\babyDevelop" /Y


:ende
rem Umgebungsvariablen setzen
rem besser nicht :(
rem reg add "HKLM\System\CurrentControlSet\Control\Session Manager\Environment" /v QTDIR /d "C:\Qt\4.4.3"
rem reg add "HKLM\System\CurrentControlSet\Control\Session Manager\Environment" /v QMAKESPEC /d "win32-g++"
rem reg add "HKLM\System\CurrentControlSet\Control\Session Manager\Environment" /v Path /t REG_EXPAND_SZ /d "%%SystemRoot%%\system32;%%SystemRoot%%;%%SystemRoot%%\System32\Wbem;C:\Qt\4.4.3\bin;C:\MinGW\bin;"

echo ----------------------------------------------------------
echo fertig.
echo BabyDevelop starten mit/in: c:\opt\babyDevelop\start_babydevelop.bat
pause
