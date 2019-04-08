#ifndef NOWYGRACZWINDOW_H
#define NOWYGRACZWINDOW_H

#include <QMainWindow>
#include <ukladanka.h>
#include <graczwindow.h>

namespace Ui
{
    class nowygraczwindow;
}

class nowygraczwindow : public QMainWindow
{
    Q_OBJECT

public:
    ///
    /// \brief :Konstruktor
    ///
    explicit nowygraczwindow(Ukladanka* u,Ui::graczWindow *t,QWidget *parent = nullptr);
    ///
    /// \brief :Konstruktor
    ///
    explicit nowygraczwindow(QMainWindow* _glownaFormatka,Ukladanka* u,Ui::graczWindow *t,QWidget *parent = nullptr) ;
    ~nowygraczwindow();


private slots:
    ///
    /// \brief on_pushButton_clicked: Obsluga  klikniecia przycisku
    ///
    void on_pushButton_clicked();
    ///
    /// \brief on_pushButton_2_clicked: Obsluga  klikniecia przycisku
    ///

    void on_pushButton_2_clicked();

private:

    ///
    /// \brief _oknoGracze: Wskaznik na okno z Graczami
    ///
    Ui::graczWindow *_oknoGracze;

    ///
    /// \brief _oknoNowyGracz: Wskaznik na okno nowego gracza
    ///
    Ui::nowygraczwindow *_oknoNowyGracz;
    ///
    /// \brief _ukladanka: Wskaznik do ukladanki
    ///
    Ukladanka* _ukladanka;

    ///
    /// \brief _glownaFormatka: Wskaznik na glowna formatke
    ///
    QMainWindow* _glownaFormatka;

signals:

    ///
    /// \brief Sygnal zdarzenia emitowany przy obsludze zdarzenia klikniecia myszy
    ///
    void dodanyGracz();
};

#endif // NOWYGRACZWINDOW_H
