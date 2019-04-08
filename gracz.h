#ifndef GRACZ_H
#define GRACZ_H
#include <string>
using  std::string;

///
/// \brief The Gracz class: Klasa eprezentuja Gracza
struct Gracz
{
public:
    ///
    /// \brief Gracz: Domyslny konstruktor
    ///
    Gracz();

    ///
    /// \brief Gracz: Konstruktor, tworzacy gracza i nadajacy mu imie
    /// \param imie: Imie gracza
    ///
    Gracz(string imie);

    ///
    /// \brief Destruktor
    ///
    ~Gracz();
public:
    ///
    /// \brief getImie: Odczytuje imie gracza
    /// \return
    ///
    string get_imie();

private:
    ///
    /// \brief _imie: Imie gracza
    ///
    string _imie;
public:
    ///
    /// \brief operator <: Definicja operatora porownania
    /// \param r prawa strona operatora
    /// \return true, jesli <
    ///
    bool operator<( const Gracz& r);
    ///
    /// \brief operator <: Definicja operatora porownania
    /// \param r prawa strona operatora
    /// \return true, jesli <
    ///
    bool operator>( const Gracz& r);


};

#endif // GRACZ_H
