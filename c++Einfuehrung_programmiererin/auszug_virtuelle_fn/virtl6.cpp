// Kapitel 10 - Programm 6 - VIRTL6.CPP
#include <iostream.h>

class Vehikel
{
private:
   int Raeder;
   float Gewicht;
public:
   virtual void Nachricht(void) {cout << "Nachricht vom Vehikel\n";}
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

   Hochrad = new Vehikel;
   Hochrad->Nachricht();
   delete Hochrad;

   Hochrad = new Auto;
   Hochrad->Nachricht();
   delete Hochrad;

   Hochrad = new Laster;
   Hochrad->Nachricht();
   delete Hochrad;

   Hochrad = new Boot;
   Hochrad->Nachricht();
   delete Hochrad;

   return 0;
}


// Ergebnis beim Ausführen
//
// Nachricht vom Vehikel
// Nachricht vom Auto
// Nachricht vom Vehikel
// Nachricht vom Boot
