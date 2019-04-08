#ifndef KLOCEK_H
#define KLOCEK_H
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include "pozycja.h"

///
/// \brief The Klocek class: Reprezentuje kwadratowy klocek z numerem na kwadratowej planszy
/// Jest odpowiedzialna za przemieszczanie i rysowanie pojedynczego klocka na scenie graficznej
///
class Klocek
{

public:
    /// \brief Tablica z referencjami do klockow, ktore sa sasiadami klocka
    /// 0-lewy
    /// 1 gorny
    /// 2-prawy
    /// 3- dolny
    /// Jesli klocek nie ma sasiada (jest na krawedzi), wowczas sasiad =-1
    ///
    Klocek* sasiedzi[4];

public:
    ///
    /// \brief Tworzy nowy klocek i ustawia go poza plansza (na pozycji-1,-1)
    /// oraz ustawia go jako blokujacego ruchy innych klockow
    ///
    Klocek();

    /// \brief Tworzy nowy klocek o numerze nr i ustawia go na planszy (lub poza) (na pozycji(kolumna,wiersz))
    /// oraz ustawia go nieblokujacego blokujacego ruchy innych klockow
    /// \param nr: numer klocka
    /// \param pozycja: pozycja na planszy
    ///
    Klocek(int nr, Pozycja pozycja,int rozmKlocka);
    ///
    /// \brief Destruktor
    ///
    ~Klocek();
public:
    ///
    /// \brief Znajduje kierunek przeciwny do danego
    /// \param kierunek Dany kierunek (0,1,2,3),
    /// \return Kierunek przeciwny (0,1,2,3),
    ///
    int KierunekPrzeciwny(int kierunek);

    ///
    /// \brief Pobiera rozmiar klocka w pixelach
    /// \return  Numer klocka
    ///
    int get_rozmiar();

    ///
    /// \brief Ustawia rozmiar klocka w pixelach
    /// \param rozmiar Rozmiar klocka
    ///
    void set_rozmiar(int rozmiar);

    ///
    /// \brief Pobiera numer klocka
    /// \return  Numer klocka
    ///
    int get_numer();

    ///
    /// \brief Ustawia numer klocka
    /// \param numer Numer klocka
    ///
    void set_numer(int numer);

    ///
    /// \brief Pobiera tablice wskaznikow do sasiadow klocka
    /// \return Tablica wskaznikow do sasiadow
    ///
    Klocek ** get_sasiedzi();

    ///
    /// \brief Ustawia tablice wskaznikow do sasiadow klocka
    /// \param Tablica 4 elementowa sasiadow
    ///
    void set_sasiedzi(Klocek* sasiedzi[4]);

    ///
    /// \brief Ustawia pozycje
    /// \param wiersz: Wiersz
    /// \param kolumna: Kolumna
    ///
    void set_pozycja(int wiersz, int kolumna);

    ///
    /// \brief Ustawia pozycje
    /// \param Pozycja na planszy
    ///
    void set_pozycja(Pozycja pozycja);

    ///
    /// \brief Pobiera pozycje na planszy
    /// \return  Pozycja na planszy
    ///
    Pozycja get_pozycja();
    ///
    /// \brief Ustawia Blokowanie przez klocek dla innych klockow
    /// (mowi czy klocek mozna przesunac )
    /// \param Rozmiar klocka
    ///
    void set_blokujeInneKlocki(bool blokuje);

    ///
    /// \brief Pobiera info czy klocek blokuje inne klocki
    /// (czy nie moze zostac przesuniety)
    /// \return  Numer klocka
    ///
    int get_blokujeInneKlocki();

private:

    /// \brief Rozmiar klocka= szerokosc=wysokosc w pixelach
    ///
    int _rozmiar;

    /// \brief Numer klocka
    ///
    int _numer;

    /// \brief Pozycja klocka na planszy
    ///
    Pozycja _pozycja;

    /// \brief Mowi czy dany klocek blokuje ruch innych klockow (nie moze byc przesuniety)
    ///
    bool _blokujeInneKlocki;


public:
    /// \brief Sprawdza czy klocek sasiaduje z pustym polem (klockiem nr 0)
    ///
    bool SasiadujeZPustym();

    /// \brief Ustal mozliwy kierunek przesuwu klocka (jesli styka sie z pustym polem)
    /// \return mozliwy kierunek przesuwu (Jesli nie ma mozliwosci ruchu zwraca -1)
    ///
    int KierunekPrzesuwuWStronePustego();

    /// \brief Oblicza kierunki ruchu klocka, aby znalezc sie najszybciej w poblizu celu
    /// \return dwa kierunki : dwa ortogonalne kierunki w kierunku celu
    ///
    std::array<int, 2> KierunkiDoCelu(Pozycja cel);

    /// \brief Rysuje klocek na scenie
    ///  \param kolor: kolor tla klocka
    ///  \param scena: referencja do sceny
    ///
    void Rysuj(QColor kolor,QGraphicsScene *scena);
};

#endif // KLOCEK_H
