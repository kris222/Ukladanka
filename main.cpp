#include "mainwindow.h"
#include "graczwindow.h"
#include "nowygraczwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //Tworzy 3 formatki, i ustawia jako widoczna formatkeGraczy
    QApplication a(argc, argv);
    MainWindow glownaFormatka;
    QObject::connect(&a, SIGNAL(aboutToQuit()), glownaFormatka.get_ukladanka(), SLOT(ZapiszGraczyDoPliku()));
    graczWindow graczeFormatka(&glownaFormatka,glownaFormatka.get_ukladanka());
    graczeFormatka.show();
    nowygraczwindow dodajGraczaFormatka(&graczeFormatka,glownaFormatka.get_ukladanka(),graczeFormatka.get_oknoGraczy());
    graczeFormatka.set_dodajgraczaFormatka(&dodajGraczaFormatka);
    QObject::connect(&graczeFormatka, SIGNAL(WybranoGracza()), &glownaFormatka, SLOT(StartujNowaGre()));
    QObject::connect(&glownaFormatka, SIGNAL(WywolanoEkranStarowy()), &graczeFormatka, SLOT(show()));
    return a.exec();
}
