#ifndef UKLADANKA_H
#define UKLADANKA_H
#include "klocek.h"
#include "plansza.h"
#include "myscene.h"
#include "gracz.h"
#include <QEvent>
#include <QTextStream>
#include <QFile>
#include <QLineEdit>
#include <QElapsedTimer>
#include <QTimer>
#include <vector>
#include "gra.h"

///
/// \brief The Ukladanka class: Reprezentuje gre komputerowa, z wyborem gier (aktualnie oprogramowana dla jednej gry: Przesuwanka)
/// Ukladanka odpowiada rowniez za obsluge Listy graczy (oraz operacji na niej), pozwala na zapisanie i odczyt stanu gry do/z pliku.
/// Mozna ta klase zinterpretowac jako czesc funkcjonalna malego panelu z grami planszowymi
/// Opcja automatycznego ulozenia jest zablokowana jako ze nie jest skonczona
///
class Ukladanka: public QObject
{
     Q_OBJECT

private:

    ///
    /// \brief _scena: Scena graficzna do wyswietlenia planszy
    ///
    MyScene* _scena;

    ///
    /// \brief _gra: Rodzaj gry
    ///
    Gra* _gra;

    ///
    /// \brief _gracze: Vector z imionami graczy
    ///
    std::vector<Gracz>  _gracze;

    ///
    /// \brief _wybranyGracz
    ///Wskaznik do wybranego grcza
    Gracz  _wybranyGracz;

    ///
    /// \brief _timer Timer do wyslania sygnalu o zmianie czasu
    ///
    QTimer  _timer;

    ///
    /// \brief _timer Timer do obliczenia czasu
    ///
    QElapsedTimer  _elTimer;
public:

    ///
    /// \brief Ukladanka: Domyslny konstruktor
    ///
    Ukladanka();

    ///
    /// \brief Destruktor
    ///
    ~Ukladanka();

    ///
    /// \brief Ukladanka: konstruktor dla Gry przesuwanka
    /// ( w przypadku innych gier beda inne konstruktory)
    /// \param _liczbaWierszy: Liczba wierszy planszy
    /// \param _rozmiarKlocka: Rozmiar klocka w pixelach
    /// \param scene: Scena graficzna
    ///
    Ukladanka(int n,  int rozmKlocka, MyScene* s);

    ///
    /// \brief get_scena: Zwraca wskaznik do sceny
    /// \return
    ///
    MyScene* get_scena();

    ///
    /// \brief get_gra: Zwraca gre
    /// \return
    ///
    Gra* get_gra();

    ///
    /// \brief ZacznijNowaGre: Rozpoczyna nowa gre
    /// \param n: liczba wierszy na planszy
    /// \param rozmKlocka: Rozmiar klocka w pixelach
    /// \param liczbaLosowychRuchow: Liczba losowych przesyniec pustego pola
    ///
    void ZacznijNowaGre(int n, int rozmKlocka,int liczbaLosowychRuchow);

    ///
    /// \brief get_gracze: Zwraca vector graczy
    /// \return
    ///
    std::vector<Gracz> get_gracze();

    ///
    /// \brief set_gracze: Ustawia vector graczy
    /// \param gracze:Vector graczy
    ///
    void set_gracze(std::vector<Gracz> gracze);



    ///
    /// \brief get_wybranyGracz: Zwraca wskaznik do wybranego gracza
    /// \return Wskaznik do wybranego gracza
    ///
    Gracz get_wybranyGracz();

    ///
    /// \brief set_wybranyGracz: Ustawia wskaznik do wybranego gracza
    /// \param gracz: Wskaznik do wybranego gracza
    ///
    void set_wybranyGracz(Gracz gracz);

    ///
    /// \brief get_timer Zwraca wskaznik do timera
    /// \return  timer: Wskaznika do timera
    ///
    QTimer* get_timer();

    ///
    /// \brief get_timer Zwraca elapsed timer z biblioteki QT
    /// \return  timer: Elapsed timer z biblioteki QT
    ///
    QElapsedTimer* get_elTimer();


    ///
    /// \brief WczytajGraczyZPliku Wczytuje graczy z pliku
    /// \param plik
    ///
    void WczytajGraczyZPliku();

    ///
    /// \brief WlaczCzas Wlacza odmierzanie czasu
    ///
    //void WlaczCzas();

    ///
    /// \brief DodajGracza: Dodaje nowego gracza do vektora graczy
    /// \param nowyGracz
    ///
    void DodajGracza(Gracz nowyGracz);

    ///
    /// \brief UsunGracza: Usuwa gracza z listy
    /// \param index: Index gracza do usuniecia
    ///
    void UsunGracza(int index);


private slots:
    ///
    /// \brief Zapisuje graczy z wektora do pliku
    ///
    void ZapiszGraczyDoPliku();
    ///
    /// \brief sortuj_gracze
    ///
    void sortuj_Graczy();


 signals:

    ///
    /// \brief Sygnal zaktualizowania listy graczy
    /// (poprzez dodanie lub usuniecie gracza)
    ///
    void ZaktualizowanoListeGraczy();

};

#endif // UKLADANKA_H
