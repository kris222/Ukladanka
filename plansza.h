#ifndef PLANSZA_H
#define PLANSZA_H
#include "klocek.h"
#include "myscene.h"
#include "mojeszablony.h"
#include <QGraphicsScene>
#include <chrono>

///
/// \brief The Plansza class:Przedstawia kwadratowa plansze wraz z ukladem klockow na niej, i informacjami o stanie klockow
/// Jest rowniez odpowiedzialna za narysowanie aktualnego stanu planszy na scenie graficznej
///
class Plansza
{

private:

    ///
    /// \brief Referencja do sceny , na ktorej bedzie rysowana plansza
    ///
    MyScene* _scena;

    ///
    /// \brief Liczba wierszy planszy
    ///
    int _liczbaWierszy;

    ///
    /// \brief Referencja do pustego pola
    /// (reprezentoanego przez klocek o numerze 0)
    ///
    Klocek* _pustePole;

    ///
    /// \brief Rozmiar klocka w pixelach
    ///
    int _rozmiarKlocka;

    ///
    /// \brief Vector z kierunkami ruchu pustego pola
    /// otrzymany podczas losowego przemieszania klockow
    ///
    std::vector<int>  _sentencjaKrokowLosowych;

    ///
    /// \brief Vector z kierunkami ruchu pustego pola
    /// otrzymany podczas przemieszczania pustego pola przez gracza
    ///
    std::vector<int> _krokiRozwiazania ;
public:
    ///
    /// \brief Przedstawia tablice dwuwymiarowa z klockami
    ///
    Klocek** ukladKlockow;

public:
    ///
    /// \brief Tworzy nowa plansze
    ///
    Plansza();

    ///
    /// \brief Plansza: Tworzy nowa plansze i ustawia jej parametry startowe
    /// \param scena: Scena na ktorej bedzie rysowana plansza
    /// \param liczbaWierszy: Liczba wierszy planszy (rowna liczbie kolumn)
    /// \param rozmiarKlocka: Rozmiar klocka w pixelach (szerokosc=wysokosc)
    ///
    Plansza(MyScene* scena,int liczbaWierszy, int rozmiarKlocka);

    ///
    /// \brief Destruktor
    ///
    ~Plansza();
public:

    ///
    /// \brief get_scena: Zwraca wskaznik do sceny
    /// \return
    ///
    MyScene* get_scena();

    ///
    /// \brief set_scena: Ustawia wskaznik do sceny
    /// \param scena: wskaznik do sceny graficznej
    ///
    void set_scena(MyScene* scena);

    ///
    /// \brief get_liczbaWierszy: Zwraca liczbe wierszy planszy
    /// (rowna liczbie kolumn)
    /// \return
    ///
    int get_liczbaWierszy();

    ///
    /// \brief set_liczbaWierszy: Ustawia liczbe wierszy planszy
    /// \param liczbaWierszy: Liczba wierszy planszy
    ///
    void set_liczbaWierszy(int liczbaWierszy);

    ///
    /// \brief get_pustePole: Zwraca wskaznik do klaocka o numerze 0
    /// \return
    ///
    Klocek* get_pustePole();

    ///
    /// \brief set_PustePole: Ustawia wskaznk do klocka o numerze 0
    /// \param pusty: Wskaznik do pustego klocka
    ///
    void set_PustePole(Klocek* pusty);

    ///
    /// \brief get_rozmiarklocka: Zwraca rozmiar klocka w pixelach
    /// \return Rozmiar klocka w pixelach
    ///
    int get_rozmiarklocka();

    ///
    /// \brief set_rozmiarKlocka: Ustawia rozmiar klocka w pixelach
    /// \param rozmiarKlocka: Rozmiar klocka w pixelach
    ///
    void set_rozmiarKlocka(int rozmiarKlocka);

    std::vector<int> get_sentencjaKrokowLosowych();


    void set_sentencjaKrokowLosowych(std::vector<int> sentencjaKrokowLosowych);
    ///
    /// \brief Rysuje plansze pusta na scenie
    ///
    void RysujPlanszeBezKlockow();

    ///
    /// \brief Tworzy uklad klockow na planszy bazujacy na rozwiazaniu
    ///
    void UtworzUkladKlockowRozwiazania();

    ///
    /// \brief Mowi czy ruch pustego pola w danym kierunku jest mozliwy
    /// \param kier:kierunek ruchu (0 lewy, 1 gora,2 prawy, 3 dol)
    /// \return true jesli ruch jest mozliwy
    ///
    bool kierunekPustegoKlockaJestMozliwy(int kier);

    ///
    /// \brief Znajduje losowy kierunek
    /// \return Losowy kierunek (0 lewy, 1 gora,2 prawy, 3 dol)
    ///
    int LosowyKierunek();

    ///
    /// \brief Przesuwa pusty klocek o jedno pole
    /// \param kierunek: kierunek przesuwu klocka pustego
    ///
    void przesunPusty(int kierunek);

    ///
    /// \brief Przesuwa puste pole (zamieniajac pozycje z sasiednim klockiem) tak aby znalezc sie w celu
    /// \param cel Pozycja na ktora checemy przesunac puste pole
    ///
    void PrzesunPustyKlocekWSasiedztwoCelu(Pozycja cel);

    ///
    /// \brief Tworzy plansze z losowym ustawieniem klockow (poprzez losowe przesuniecie pustego pola n razy)
    /// \param n: Liczba przesuniec losowych pustego klocka
    ///
    void PomieszajKlockiLosowo(int n);

    ///
    /// \brief Rysuje na planszy (scenie) biezacy uklad klockow
    /// \param kolor: Kolor w jakim rysowane sa klocki
    ///
    void RysujUkladKlockow(QColor kolor);

    ///
    /// \brief Znajduje sasiadow klockow dla biezacego ukladu na planszy
    /// (jest wykonywany tylko raz, przy pierwszym ulozeniu klockow z rozwiazania)
    ///
    void ZnajdzSasiadowKlockow();

    ///
    /// \brief Mowi czy pusty klocek jest sasiadem celu
    /// \param cel: Pozycja klocka celu
    /// \return  True jesli pusty klocek graniczy z celem bokami
    ///
    bool PustyJestSasiademCelu(Pozycja cel);

    ///
    /// \brief Wczytuje plansze na podstawie tablicy numerow klockow
    /// \param tablica Dwuwymiarowa tablica z numerami klockow
    ///
    void WczytajZTablicy(int** tablica);

    ///
    /// \brief Zapisuje numery klockow do tablicy
    /// \param tablica Dwuwymiarowa tablica z numerami klockow
    ///
    void ZapiszDoTablicy(int** tablica);

    ///
    /// \brief Miesza klocki na planszy, przesuwajac pusty klocek n razy
    /// \param tablica Dwuwymiarowa tablica z numerami klockow uzyta jako start do wymieszania klockow
    /// \param n Liczba losowych przemieszczen pustego klocka o jedno pole
    ///
    void PrzemieszajKlocki(int n, int** tablica);
};


#endif // PLANSZA_H
