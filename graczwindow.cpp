#include "graczwindow.h"
#include "nowygraczwindow.h"
#include "ui_graczwindow.h"
#include <QTextStream>
#include <QFile>
#include <QLineEdit>
#include <QListView>
#include <QDir>
#include <QMessageBox>

#include <iostream>
using std::cout;
using std::cin;
#include <fstream>
using std::ifstream;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <iterator>
using std::istream_iterator;
#include <algorithm>
using std::copy;
using namespace std;



graczWindow::graczWindow(Ukladanka* u,QWidget *parent) :
    QMainWindow(parent),
    _oknoGraczy(new Ui::graczWindow)
{
    _oknoGraczy->setupUi(this);
    _ukladanka=u;
}

void graczWindow::AktualizujListeCB()
{
    _oknoGraczy->cb_Gracze->setView(new QListView());
    _oknoGraczy->cb_Gracze->setStyleSheet("QComboBox QAbstractItemView::item { min-height: 30px; min-width: 50px; }QListView::item:selected { color: black; background-color: lightgray}");
    _oknoGraczy->cb_Gracze->clear();
    QFont ft("Courier New", 6);
    _oknoGraczy->cb_Gracze->setFont(ft);
    _oknoGraczy->cb_Gracze->setEditable(true);
    _oknoGraczy->cb_Gracze->lineEdit()->setReadOnly(true);
    _oknoGraczy->cb_Gracze->lineEdit()->setAlignment(Qt::AlignCenter);
    if(!_ukladanka->get_gracze().empty())
    {
        vector<Gracz>::iterator it;
        for (unsigned int i=0; i<_ukladanka->get_gracze().size();i++)
        {
            std::vector<Gracz> d=_ukladanka->get_gracze();
            _oknoGraczy->cb_Gracze->addItem(QString::fromStdString(_ukladanka->get_gracze()[i].get_imie()));
        }
    }
}
graczWindow::graczWindow(QMainWindow* w1,Ukladanka* u,QWidget *parent) :
    QMainWindow(parent),
    _oknoGraczy(new Ui::graczWindow)
{
    _oknoGraczy->setupUi(this);
  //  ui2->cb_Gracze->insertItems(0,{"1","2"});
    _ukladanka=u;
    _glownaFormatka=w1;
    QObject::connect(_ukladanka,SIGNAL(ZaktualizowanoListeGraczy()),_ukladanka,SLOT(sortuj_Graczy()));
    QObject::connect(_ukladanka,SIGNAL(ZaktualizowanoListeGraczy()),this,SLOT(AktualizujListeCB()));

    QFile file("D:/gracze.txt");
    QTextStream stream (&file);
   AktualizujListeCB();

}

graczWindow::~graczWindow()
{
    delete _oknoGraczy;
    delete _ukladanka;
    delete _dodajgraczaFormatka;
    delete _glownaFormatka;
}

void graczWindow::on_btn_PrzejdzDoGry_clicked()
{
    if(_ukladanka->get_gracze().empty())
    {
        //Wyswietla okno dialogowe z informacja, gdy nie zostal wybrany zaden gracz (brak listy graczy)
        QMessageBox oknoDialogowe1;
        oknoDialogowe1.setWindowTitle("Ukladanka");
        oknoDialogowe1.setText("Nie zostal wybrany gracz. Wybierz gracza z listy i sprobuj ponownie.");
        QFont font;
        font.setPixelSize(20);
        font.setBold(false);
        font.setFamily("Calibri");
        oknoDialogowe1.setFont(font);
        oknoDialogowe1.exec();
    }
    else
    {
        //Ustawia wybranego gracza, przechodzi do glownej formatki i emituje sygnal o wybraniu gracza
        this->close();
        this->_glownaFormatka->show();
        unsigned long j = static_cast<unsigned long>(_oknoGraczy->cb_Gracze->currentIndex());
        _ukladanka->set_wybranyGracz(_ukladanka->get_gracze()[j]);
        Gracz fff=_ukladanka->get_gracze()[j];
        _ukladanka->get_gra()->WlaczCzas();
        emit WybranoGracza();
        // Tworzy folder Dane jesli taki nie istnieje
        if(!QDir("Dane").exists())
        {
            QDir().mkdir("Dane");
        }
    }
}

void graczWindow::on_btn_UsunGracza_clicked()
{
    if(!_ukladanka->get_gracze().empty())
    {
        _ukladanka->UsunGracza(_oknoGraczy->cb_Gracze->currentIndex());
    }
}

void graczWindow::on_btn_DodajGracza_clicked()
{
   _dodajgraczaFormatka->show();
}


Ukladanka* graczWindow::get_ukladanka()
{
    return _ukladanka;
}

QMainWindow* graczWindow::get_dodajgraczaFormatka()
{
    return _dodajgraczaFormatka;
}

void graczWindow::set_dodajgraczaFormatka(QMainWindow* a)
{
   _dodajgraczaFormatka= a ;
}

Ui::graczWindow* graczWindow::get_oknoGraczy()
{
   return _oknoGraczy;
}


QMainWindow* graczWindow::get_glownaFormatka()
{
    return _glownaFormatka;
}

