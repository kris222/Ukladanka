#ifndef GRA_H
#define GRA_H
#include "plansza.h"
#include <QElapsedTimer>
#include <QTimer>
using  std::string;

///
/// \brief The GraPrzesuwanka class: Reprezentuje gre planszowa polegajaca na przesuwaniu pustego pola na planszy NxN,
/// zeby znalezc uporzadkowany uklad ponumerowanych klockow
///
class Gra: public QObject
{
     Q_OBJECT


public:
    ///
    /// \brief GraPrzesuwanka: Domyslny konstruktor
    ///
    Gra();

    ///
    /// \brief GraPrzesuwanka: Konstruktor
    /// \param n: Liczba wierszy ukladanki
    /// \param rozmKlocka: Rozmiar klocka w pixelach
    /// \param s: Scena graficzna
    /// \param timer: Wskaznik na timer
    /// \param eltimer: Wskaznik na elapsed timer
    ///
    Gra(int n,  int rozmKlocka, MyScene* s,QTimer* timer, QElapsedTimer* eltimer  );
    ~Gra();
private:

    ///
    /// \brief Referencja do sceny , na ktorej bedzie rysowana plansza
    ///
    MyScene* _scena;

    ///
    /// \brief Rozmiar klocka w pixelach
    ///
    int _rozmiarKlocka;

    ///
    /// \brief _plansza: Wskaznik do planszy
    ///
    Plansza _plansza;

    ///
    /// \brief Liczba wierszy planszy
    ///
    int _liczbaWierszy;

    ///
    /// \brief _liczbaKrokow: Liczba krokow (przesunietych klockow)
    ///
    int _liczbaKrokow;

    ///
    /// \brief _aktualnyCzas: Aktualny czas gry w sekundach
    ///
    int _aktualnyCzas;

    ///
    /// \brief Mowi czy mozna klikac mysza na plansze
    /// (tzn czy jestesmy w czasie gry)
    ///
    bool _dozwoloneKlikanieNaPlansze;

    ///
    /// \brief Czas rozwiazania aktualnej gry w sekundach
    ///
    int  _czasRozwiazania;

    ///
    /// \brief Czas od jakiego zaczyna sie odliczanie
    /// (0 dla nowej gry lub liczba >0 dla gry ladowanej z pliku
    ///
    int  _czasStartowy;

    ///
    /// \brief Liczba od jakiej zaczyna sie odliczanie krokow
    /// (0 dla nowej gry lub liczba >0 dla gry ladowanej z pliku
    ///
    int  _startowaLiczbaKrokow;

    ///
    /// \brief Tablica dwuwymiarowa z numerami klockow w rozwiazaniu
    ///
    int ** _tablicaRozwiazania;

    ///
    /// \brief Tablica dwuwymiarowa z numerami klockow na planszy startowej
    ///
    int ** _tablicaStartowa;

    ///
    /// \brief _sentencjaKrokow: Wektor z numerami kierunkow pustego pola
    ///
    std::vector<int>  _sentencjaKrokow;

    ///
    /// \brief _timer: Wskaznik na timer z biblioteki QT
    ///
    QTimer*  _timer;
    ///
    /// \brief _elTimer:Wskaznik na elapsed timer z biblioteki QT
    ///
    QElapsedTimer*  _elTimer;


public:

    ///
    /// \brief UtworzTabliceRozwiazania: Tworzy tablice z klockami odpowiadajaca rozwiazaniu
    ///
    void UtworzTabliceRozwiazania();

    ///
    /// \brief UkladankaJestRozwiazana: Sprawdza czy gra jest rozwiazana
    /// \return true jesli rozwiazana
    ///
    bool graJestRozwiazana();

    ///
    /// \brief UtworzLosowaPlansze: Tworzy plansze z losowym ukladem klockow, powstalym przez n
    /// losowych ruchow pustego pola
    /// \param n Liczba losowych przesuniec pustego pola
    ///
    void UtworzLosowaPlansze(int n);

    ///
    /// \brief ZapiszGreDoPliku: Zapisuje biezacy stan gry do pliki
    /// \param nazwaPliku: Sciezka pliku
    ///
    void ZapiszGreDoPliku(string nazwaPliku);

    ///
    /// \brief WczytajGreZPliku: Wczytuje biezacy stan gry z pliku
    /// \param nazwaPliku: Sciezka pliku
    ///
    void WczytajGreZPliku(string nazwaPliku);

    ///
    /// \brief daneDoTabeliWynikow: Przygotowuje dane z wynikami w formacie QString, wczytane z pliku
    /// \param sciezkaPliku: Sciezka do pliku z zachowanymi danymi
    /// \param sortujCzas: Mowi czy dane powinny byc posortowane ze wzgledy na czas (false= ze wzgledu na liczbe krokow)
    /// \return
    ///
    QString daneDoTabeliWynikow(string sciezkaPliku,bool sortujCzas=true);

    ///
    /// \brief PodzielonyText:Zapisuje text jako vector stringow, oddzielonych w tekscie za pomoca delimitera
    /// \param s: Text do podzielenia
    /// \param delimiter: Ciag stringow, uzyty jako delimiter
    /// \return Vector z wydzielonymi textami
    ///
    std::vector<string> PodzielonyText(string s,string delimiter );

    ///
    /// \brief vectorStringTovectorInt: Zamienia wektor stringow na vector liczb calkowitych
    /// (o ile sie da)
    /// \param vecString: Vector ze stringami
    /// \return  Vector z liczbami calkowitymi
    ///
    std::vector<int> vectorStringTovectorInt(std::vector<string> vecString);

    ///
    /// \brief KierunekPrzeciwny: Znajduje kierunek przeciwny do danego
    /// (np dla 0 zwraca 2)
    /// \param kierunek: Dany kierunek
    /// \return: Kierunek przeciwny
    ///
    int KierunekPrzeciwny(int kierunek);

    ///
    /// \brief WlaczCzas: Zaczyna mierzyc czas gry
    ///
    void WlaczCzas();

    ///
    /// \brief get_dozwoloneKlikanieNaPlansze: Sprawdza czy dozwolone jest klikanie na plansze
    /// (czy jestesmy w stanie gry)
    /// \return  Czy dozwolone jest klikanie na plansze.
    ///
    bool get_dozwoloneKlikanieNaPlansze();

    ///
    /// \brief set_timer
    /// \param dozwoloneKlikanieNaPlansze
    ///
    void set_dozwoloneKlikanieNaPlansze(bool dozwoloneKlikanieNaPlansze);

    ///
    /// \brief get_czasRozwiazania: Pobiera czas rozwiazania gry
    /// \return
    ///
    int get_czasRozwiazania();

    ///
    /// \brief set_czasRozwiazania: Ustawia czas rozwiazania gry
    /// \param Czas rozwiazania gry
    ///
    void set_czasRozwiazania(int czasRozwiazania);

    ///
    /// \brief get_plansza: Pobiera wskaznik do planszy
    /// \return
    ///
    Plansza* get_plansza();

    ///
    /// \brief set_plansza: Zwraca wskaznik do planszy
    ///
    void set_plansza(Plansza);

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
    /// \brief get_rozmiarklocka: Zwraca rozmiar klocka w pixelach
    /// \return Rozmiar klocka w pixelach
    ///
    int get_rozmiarklocka();

    ///
    /// \brief set_rozmiarKlocka: Ustawia rozmiar klocka w pixelach
    /// \param rozmiarKlocka: Rozmiar klocka w pixelach
    ///
    void set_rozmiarKlocka(int rozmiarKlocka);

    ///
    /// \brief get_scena: Zwraca wskaznik do sceny
    /// \return Wskaznik do sceny
    ///
    MyScene* get_scena();

    ///
    /// \brief set_scena: Ustawia wskaznik do sceny
    /// \param scena: wskaznik do sceny graficznej
    ///
    void set_scena(MyScene* scena);

    ///
    /// \brief get_liczbaKrokow: Pobiera aktualna liczbe krokow gracza
    /// \return Liczba krokow
    ///
    int get_liczbaKrokow();

    ///
    /// \brief set_liczbaKrokow: Ustawia aktualna liczbe krokow
    /// \param liczbaKrokow
    ///
    void set_liczbaKrokow(int liczbaKrokow);

    ///
    /// \brief get_aktualnyCzas: Pobiera aktualny czas gry w sekundach
    /// \return Czas gry w sekundach
    ///
    int get_aktualnyCzas();

    ///
    /// \brief set_aktualnyCzas: Ustawia aktualny czas
    /// \param aktualnyCzas
    ///
    void set_aktualnyCzas(int aktualnyCzas);

    ///
    /// \brief get_czasStartowy Pobiera czas starowy
    /// \return Czas starowy gry w sekundach
    ///
    int get_czasStartowy();

    ///
    /// \brief set_czasStartowy: Ustawia czas startowy
    /// \param czasStartowy: Czas starowy w sekundach
    ///
    void set_czasStartowy(int czasStartowy);

    ///
    /// \brief get_startowaLiczbaKrokow
    /// \return
    ///
    int get_startowaLiczbaKrokow();

    ///
    /// \brief set_startowaLiczbaKrokow: Ustawia startowa liczbe krokow
    /// \param startowaLiczbaKrokow
    ///
    void set_startowaLiczbaKrokow(int startowaLiczbaKrokow);

    ///
    /// \brief get_tablicaRozwiazania: Pobiera dwuwymiarowa tablice z numerami klockow
    /// \return Dwuwymiarowa tablice z numerami klockow
    ///
    int ** get_tablicaRozwiazania();

    ///
    /// \brief get_tablicaStartowa Pobiera dwuwymiarowa tablice startowa z wymieszanymi numerami klockow
    /// \return
    ///
    int ** get_tablicaStartowa();

    ///
    /// \brief get_sentencjaKrokow: Pobiera wektor z numerami kierunkow pola pustego
    /// \return Wektor z numerami kierunkow pola pustego
    ///
    const std::vector<int> get_sentencjaKrokow();

    ///
    /// \brief set_sentencjaKrokow: Ustawia wektor z numerami kierunkow pola pustego
    /// \param sentencjaKrokow: Wektor z numerami kierunkow pola pustego
    ///
    void set_sentencjaKrokow(std::vector<int> sentencjaKrokow);


    ///
    /// \brief get_timer Zwraca wskaznik do timera
    /// \return  timer: Wskaznika do timera
    ///
    QTimer* get_timer();

    ///
    /// \brief set_timer Ustawia nowy timer
    /// \param timer :Timer
    ///
    void set_timer(QTimer timer);

    ///
    /// \brief get_timer Zwraca elapsed timer z biblioteki QT
    /// \return  timer: Elapsed timer z biblioteki QT
    ///
    QElapsedTimer* get_elTimer();

    ///
    /// \brief set_timer Ustawia nowy timer
    /// \param timer :Timer
    ///
    void set_elTimer(QElapsedTimer timer);

public slots:
    ///
    /// \brief Obsluguje klikniecie na scene
    ///
    void KlikniecieNaPlansze();

    ///
    /// \brief ZapiszDoListyRekordow: Zapisuje wyniki w plikach z wynikami.
    /// \param folder
    /// \param imie
    ///
    void ZapiszDoListyRekordow(string imie );
 signals:
    ///
    /// \brief Sygnal klikniecia myszka na scenie
    ///
    void RozwiazanoUkladanke();
    ///
    /// \brief Sygnal zaktualizowania listy graczy
    /// (poprzez dodanie lub usuniecie gracza)
    ///
    void ZaktualizowanoListeGraczy();

    ///
    /// \brief PrzestawionoKlocek: Sygnal informujacy o przestawieniu klocka
    ///
    void PrzestawionoKlocek();
};

#endif // GRA_H
