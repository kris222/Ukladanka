#include "gracz.h"

Gracz::Gracz()
{

}
Gracz::Gracz(std::string i)
{
    _imie=i;
}
Gracz::~Gracz()
{

}
string Gracz::get_imie()
{
    return _imie;
}

bool Gracz::operator<( const Gracz& r)
{
      return this->_imie< r._imie;
}

bool Gracz::operator>( const Gracz& r)
{
   return this->_imie> r._imie;
}
