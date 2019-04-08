/**
 * class Pozycja
 * Okresla pozycje klocka na planszy
 *
 */

#ifndef POZYCJA_H
#define POZYCJA_H

///
/// \brief The Pozycja struct: Struktura opisujaca pozycje na planszy
///
struct Pozycja
{
private:
    ///
    /// \brief Pozycja na planszy y
    ///
    int _wiersz;

    ///
    /// \brief Pozycja na planszy x
    ///
    int _kolumna;
public:
    ///
    /// Tworzy instancje klasy o wspolrzednych 0,0
    ///
    Pozycja();

    ///
    /// \brief Pozycja Tworzy instancje klasy o wspolrzednych kolumna, wiersz
    /// \param wiersz: Wspolrzedna Y
    /// \param kolumna: Wspolrzedna x
    ///
    Pozycja(int wiersz,int kolumna);

    ///
    /// \brief Destruktor
    ///
    ~Pozycja();

    ///
    /// \brief Przypisuje wartosc kolumnie
    /// \param kolumna
    ///
    void set_kolumna (int kolumna);

    ///
    /// \brief Przypisuje wartosc wierszowi
    /// \param kolumna
    ///
    void set_wiersz(int wiersz);

    ///
    /// \brief Pobiera wspolrzedna X na planszy
    /// \return wspolrzedna X na planszy
    ///
    int get_kolumna ();

    ///
    /// \brief Pobiera wspolrzedna Y na planszy
    /// \return wspolrzedna Y na planszy
    ///
    int get_wiersz();
};

#endif // POZYCJA_H
