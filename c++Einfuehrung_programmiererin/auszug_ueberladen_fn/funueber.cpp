// Kapitel 6 - Programm 9 - FUNUEBER.CPP
#include <iostream.h>

class VieleNamen
{
private:
   int Laenge;
   int Breite;
public:
   VieleNamen(void);		   // Konstruktoren
   VieleNamen(int L);
   VieleNamen(int L, int B);
   void Zeige(void);		   // Anzeigefunktionen
   void Zeige(int Eins);
   void Zeige(int Eins, int Zwei);
   void Zeige(float Zahl);
};

//--------------------------------------------------------------
VieleNamen::VieleNamen(void)
{
   Laenge = 8;
   Breite = 8;
}

//--------------------------------------------------------------
VieleNamen::VieleNamen(int L)
{
   Laenge = L;
   Breite = 8;
}

//--------------------------------------------------------------
VieleNamen::VieleNamen(int L, int B)
{
   Laenge = L;
   Breite = B;
}

//--------------------------------------------------------------
void VieleNamen::Zeige(void)
{
   cout << "Anzeigefunktion (void), Flaecheninhalt = " <<
							Laenge * Breite << "\n";
}

//--------------------------------------------------------------
void VieleNamen::Zeige(int Eins)
{
   cout << "Anzeigefunktion (int), Flaecheninhalt = " <<
							Laenge * Breite << "\n";
}

//--------------------------------------------------------------
void VieleNamen::Zeige(int Eins, int Zwei)
{
   cout << "Anzeigefunktion (int, int), Flaecheninhalt = " <<
							Laenge * Breite << "\n";
}

//--------------------------------------------------------------
void VieleNamen::Zeige(float Zahl)
{
   cout << "Anzeigefunktion (float), Flaecheninhalt = " <<
							Laenge * Breite << "\n";
}

//--------------------------------------------------------------
int main()
{
VieleNamen Klein, Mittel(10), Grosz(12, 15);
int BIP = 144;
float Pi = 3.1415, Lohn = 12.50;

   Klein.Zeige();
   Klein.Zeige(100);
   Klein.Zeige(BIP,100);
   Klein.Zeige(Lohn);

   Mittel.Zeige();
   Grosz.Zeige(Pi);

   return 0;
}


// Ergebnis beim Ausführen
//
// Anzeigefunktion (void), Flaecheninhalt = 64
// Anzeigefunktion (int), Flaecheninhalt = 64
// Anzeigefunktion (int, int), Flaecheninhalt = 64
// Anzeigefunktion (float), Flaecheninhalt = 64
// Anzeigefunktion (void), Flaecheninhalt = 80
// Anzeigefunktion (float), Flaecheninhalt = 180
