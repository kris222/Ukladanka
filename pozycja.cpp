#include "pozycja.h"

Pozycja::Pozycja()
{

}
Pozycja::Pozycja(int wiersz, int kolumna)
{
    set_wiersz(wiersz);
    set_kolumna(kolumna);
}
Pozycja::~Pozycja()
{

}

void Pozycja::set_wiersz(int wiersz)
{
   _wiersz=wiersz;
}

void Pozycja::set_kolumna(int kolumna)
{
   _kolumna=kolumna;
}

int Pozycja::get_wiersz()
{
   return _wiersz;
}

int Pozycja::get_kolumna()
{
   return _kolumna;
}
