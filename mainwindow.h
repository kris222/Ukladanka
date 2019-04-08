#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ukladanka.h"
#include "graczwindow.h"
#include <QGraphicsScene>
#include "qobject.h"
#include <QEvent>
namespace Ui
{
    class MainWindow;
}

///
/// \brief The MainWindow class: Glowna formatka na ktorej odbywa sie gra
///
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
 private:
    ///
    /// \brief _glowneOkno: Wskaznik do Glownego okna
    ///
    Ui::MainWindow* _glowneOkno;

    ///
    /// \brief _ukladanka: Wskaznik do Glownego objektu ukladanka
    ///
    Ukladanka*  _ukladanka;

    ///
    /// \brief _scena:Wskaznik do sceny graficznej
    ///
    MyScene* _scena;

    ///
    /// \brief _xPrawyDolnyRogSceny: Wspolrzedna X konca sceny graficznej
    ///
    int _xPrawyDolnyRogSceny;

    ///
    /// \brief _yPrawyDolnyRogSceny: Wspolrzedna Y konca sceny graficznej
    ///
    int _yPrawyDolnyRogScen;

private:

    ///
    /// \brief ZacznijNowaGre: Rozpoczyna nowa gre
    /// \param n
    /// \param rozmKlocka
    /// \param liczbaLosowychRuchow
    ///
    void ZacznijNowaGre(int n, int rozmKlocka,int liczbaLosowychRuchow);

    ///
    /// \brief ZacznijNowaGre: Rozpoczyna nowa gre
    /// \param n: liczba wierszy na planszy
    /// \param rozmKlocka: Rozmiar klocka w pixelach
    /// \param liczbaLosowychRuchow: Liczba losowych przesyniec pustego pola
    ///
    void UaktualnijGeometrieKontrolek();

public:

    ///
    /// \brief get_ukladanka: Pobiera wskaznik na Ukladanke
    /// \return
    ///
    Ukladanka* get_ukladanka();

signals:
    ///
    /// \brief WywolanoEkranStarowy: Sygnal wywolania ekranu startowego (ekranu z obsluga graczy)
    ///
    void WywolanoEkranStarowy();

private slots:
    ///
    /// \brief StartujNowaGre: Metoda startujaca nowa gre z plansza 2x2
    ///
    void StartujNowaGre();

    ///
    /// \brief WyswietlTabeleWynikow: Wyswietla tabbele wynikow dla aktualnie wybranej liczby wierszy
    /// \param sortujCzas: true jesli ma bys posortowane ze wzgledu na czas, false, jesli sortujemy ze wzgledu na ilosc krokow
    ///
    void WyswietlTabeleWynikow(bool sortujCzas=true);

    ///
    /// \brief RysujWiadomoscORozwiazaniu: Rysuj krotka wiadomosc o rozwiazaniu ukladanki
    /// oraz dopisuje aktualny wynik do plku z wynikami
    ///
    void RysujWiadomoscORozwiazaniu();

    ///
    /// \brief KlikniecieMyszaNaScene: Aktualizuje stan planszy po kliknieciu na nia
    ///
    void KlikniecieMyszaNaScene();

    ///
    /// \brief WyswietlBiezacyCzas: Wyswietla biezacy czas gry (w labelu)
    ///
    void WyswietlBiezacyCzas();

    ///
    /// \brief WyswietlBiezacyCzas: Wyswietla biezaca liczbe krokow (w labelu)
    ///
    void WyswietlLiczbeKrokow();

    ///
    /// \brief on_bt_NowaUkladanka_clicked: Obsluga  klikniecia przycisku
    ///
    void on_bt_NowaUkladanka_clicked();

    ///
    /// \brief on_rB_Czas_clicked: Obsluga  klikniecia kontrolki radioButton
    ///
    void on_rB_Czas_clicked();

    ///
    /// \brief on_rB_Kroki_clicked: Obsluga  klikniecia kontrolki radioButton
    ///
    void on_rB_Kroki_clicked();

    ///
    /// \brief on_bt_EkranStartowy_clicked: Obsluga  klikniecia przycisku
    ///
    void on_bt_EkranStartowy_clicked();

    ///
    /// \brief on_bt_ZapiszGre_clicked: Obsluga  klikniecia przycisku
    ///
    void on_bt_ZapiszGre_clicked();

    ///
    /// \brief on_bt_WczytajGre_clicked: Obsluga  klikniecia przycisku
    ///
    void on_bt_WczytajGre_clicked();

private:

};

#endif // MAINWINDOW_H
