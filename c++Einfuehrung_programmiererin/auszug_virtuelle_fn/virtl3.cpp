// Kapitel 10 - Programm 3 - VIRTL3.CPP
#include <iostream.h>

class Vehikel
{
private:
   int Raeder;
   float Gewicht;
public:
   void Nachricht(void) {cout << "Nachricht vom Vehikel\n";}
};

//-------------------------------------------------------------------
class Auto : public Vehikel
{
private:
   int Passagieranzahl;
public:
   void Nachricht(void) {cout << "Nachricht vom Auto\n";}
};

//-------------------------------------------------------------------
class Laster : public Vehikel
{
private:
   int Passagieranzahl;
   float Ladung;
public:
   int Passagiere(void) {return Passagieranzahl;}
};

//-------------------------------------------------------------------
class Boot : public Vehikel
{
private:
   int Passagieranzahl;
public:
   int Passagiere(void) {return Passagieranzahl;}
   void Nachricht(void) {cout << "Nachricht vom Boot\n";}
};

//-------------------------------------------------------------------
int main()
{
Vehikel *Hochrad;
Auto	  *Sedan;
Laster  *Sattelschlepper;
Boot	  *Segelboot;

   Hochrad = new Vehikel;
   Hochrad->Nachricht();
   Sedan = new Auto;
   Sedan->Nachricht();
   Sattelschlepper = new Laster;
   Sattelschlepper->Nachricht();
   Segelboot = new Boot;
   Segelboot->Nachricht();

   return 0;
}


// Ergebnis beim Ausführen
//
// Nachricht vom Vehikel
// Nachricht vom Auto
// Nachricht vom Vehikel
// Nachricht vom Boot
