#ifndef GRACZWINDOW_H
#define GRACZWINDOW_H

#include <QMainWindow>
#include <ukladanka.h>

namespace Ui
{
    class graczWindow;
}

class graczWindow : public QMainWindow
{
    Q_OBJECT


public:
    ///
    /// \brief :Konstruktor
    ///
    explicit graczWindow(Ukladanka* u, QWidget *parent = nullptr);
    ///
    /// \brief :Konstruktor
    ///
    explicit graczWindow(QMainWindow* w1,Ukladanka* u,QWidget *parent = nullptr);

    ~graczWindow();
private:

    Ukladanka* _ukladanka;
    ///
    /// \brief dodajgraczaFormatka: Wskaznik na formatke dodania gracza
    ///
    QMainWindow* _dodajgraczaFormatka;

    ///
    /// \brief ui2: Wskaznik na objekt okna Graczy
    ///
    Ui::graczWindow* _oknoGraczy;

    ///
    /// \brief glownaFormatka: Wskaznik na glowna formatke
    ///
    QMainWindow* _glownaFormatka;

public:
    ///
    /// \brief get_ukladanka: Pobiera wskaznik na Ukladanke
    /// \return
    ///
    Ukladanka* get_ukladanka();

    ///
    /// \brief dodajgraczaFormatka: Wskaznik na formatke dodania gracza
    ///
    QMainWindow* get_dodajgraczaFormatka();

    ///
    /// \brief set_dodajgraczaFormatkaUstawia wskaznik na formatke dodania gracza
    /// \param a: wskaznik na formatke
    ///
    void set_dodajgraczaFormatka(QMainWindow* a);

    ///
    /// \brief ui2: Wskaznik na objekt okna Graczy
    ///
    Ui::graczWindow* get_oknoGraczy();

    ///
    /// \brief glownaFormatka: Wskaznik na glowna formatke
    ///
    QMainWindow* get_glownaFormatka();

public slots:

    ///
    /// \brief on_btn_PrzejdzDoGry_clicked: Obsluga  klikniecia przycisku
    ///
    void on_btn_PrzejdzDoGry_clicked();

    ///
    /// \brief on_btn_UsunGracza_clicked: Obsluga  klikniecia przycisku
    ///
    void on_btn_UsunGracza_clicked();

    ///
    /// \brief on_btn_DodajGracza_clicked: Obsluga  klikniecia przycisku
    ///
    void on_btn_DodajGracza_clicked();
    ///
    /// \brief AktualizujListeCB: Aktualizuje liste Combo box z graczami
    ///
    void AktualizujListeCB();


signals:
    void WybranoGracza();

};

#endif // GRACZWINDOW_H
