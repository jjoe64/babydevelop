// Kapitel 10 - Programm 1 - VIRTL1.CPP
#include <iostream.h>

class Vehikel
{
private:
   int Raeder;
   float Gewicht;
public:
   void Nachricht(void) {cout << "Nachricht vom Vehikel\n";}
};

//--------------------------------------------------------------
class Auto : public Vehikel
{
private:
   int Passagieranzahl;
public:
   void Nachricht(void) {cout << "Nachricht vom Auto\n";}
};

//--------------------------------------------------------------
class Laster : public Vehikel
{
private:
   int Passagieranzahl;
   float Ladung;
public:
   int Passagiere(void) {return Passagieranzahl;}
};

//--------------------------------------------------------------
class Boot : public Vehikel
{
private:
   int Passagieranzahl;
public:
   int Passagiere(void) {return Passagieranzahl;}
   void Nachricht(void) {cout << "Nachricht vom Boot\n";}
};

//--------------------------------------------------------------
int main()
{
Vehikel Hochrad;
Auto Sedan;
Laster Sattelschlepper;
Boot Segelboot;

   Hochrad.Nachricht();
   Sedan.Nachricht();
   Sattelschlepper.Nachricht();
   Segelboot.Nachricht();

   return 0;
}


// Ergebnis beim Ausführen
//
// Nachricht vom Vehikel
// Nachricht vom Auto
// Nachricht vom Vehikel
// Nachricht vom Boot
