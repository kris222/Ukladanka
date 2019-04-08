#include "mainwindow.h"
#include "graczwindow.h"
#include "ui_mainwindow.h"
#include "ukladanka.h"
#include <QGraphicsScene>
#include <QMessageBox>
#include <QEvent>
#include <string>
#include <QCloseEvent>
#include <QElapsedTimer>
#include <iostream>
#include <fstream>
#include <QFileInfo>
#include <QFileDialog>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _glowneOkno(new Ui::MainWindow)
{
    _scena= new MyScene();
    _glowneOkno->setupUi(this);
    _glowneOkno->graphicsView->fitInView(_scena->sceneRect(), Qt::KeepAspectRatio);
    _ukladanka = new Ukladanka(_glowneOkno->sb_LiczbaWierszy->value(),40,_scena);
    QObject::connect(_scena,SIGNAL(mousePressed()),this,SLOT(KlikniecieMyszaNaScene()));
    QObject::connect(_ukladanka->get_gra(),SIGNAL(RozwiazanoUkladanke()),this,SLOT(RysujWiadomoscORozwiazaniu()));
    QObject::connect(_ukladanka->get_timer(),SIGNAL(timeout()),this,SLOT(WyswietlBiezacyCzas()));
    QObject::connect(_ukladanka->get_gra(),SIGNAL(PrzestawionoKlocek()),this,SLOT(WyswietlLiczbeKrokow()));
    ZacznijNowaGre(_glowneOkno->sb_LiczbaWierszy->value(),40,500);
}

MainWindow::~MainWindow()
{
    delete _glowneOkno;
    delete  _ukladanka;
    delete _scena;
}

void MainWindow::KlikniecieMyszaNaScene()
{
    _ukladanka->get_gra()->KlikniecieNaPlansze();

}
void MainWindow::RysujWiadomoscORozwiazaniu()
{
    _ukladanka->get_gra()->set_dozwoloneKlikanieNaPlansze(false);
    _ukladanka->get_gra()->set_czasRozwiazania(_glowneOkno->lb_Czas->text().toInt());
    _ukladanka->get_gra()->ZapiszDoListyRekordow(_ukladanka->get_wybranyGracz().get_imie());
    WyswietlTabeleWynikow(_glowneOkno->rB_Czas->isChecked());
    _ukladanka->get_timer()->stop();
    QMessageBox oknoDialogowe;
    oknoDialogowe.setWindowTitle("Ukladanka");
    oknoDialogowe.setText("Ukladanka zostala rozwiazana.");
    QFont font;
    font.setPixelSize(20);
    font.setBold(false);
    font.setFamily("Calibri");
    oknoDialogowe.setFont(font);
    oknoDialogowe.exec();
}
void MainWindow::WyswietlBiezacyCzas()
{
    if (_ukladanka->get_gra()->get_dozwoloneKlikanieNaPlansze()==false)
        return;
    int a=static_cast<int>(_ukladanka->get_elTimer()->elapsed()/1000);
    _ukladanka->get_gra()->set_aktualnyCzas((_ukladanka->get_gra()->get_czasStartowy())+a);
    _glowneOkno->lb_Czas->setText(QString::number(_ukladanka->get_gra()->get_aktualnyCzas()));
}

void MainWindow::WyswietlLiczbeKrokow()
{
   _glowneOkno->lb_LiczbaKrokow->setText(QString::number(_ukladanka->get_gra()->get_liczbaKrokow()));
}

void MainWindow::on_bt_NowaUkladanka_clicked()
{
    ZacznijNowaGre(_glowneOkno->sb_LiczbaWierszy->value(),40,500);
    UaktualnijGeometrieKontrolek();
    WyswietlTabeleWynikow();
    _ukladanka->get_gra()->WlaczCzas();
}

void MainWindow::UaktualnijGeometrieKontrolek()
{
    //Wspolrzedne dolnego prawego rogu planszy
    _xPrawyDolnyRogSceny=std::max(40+_ukladanka->get_gra()->get_liczbaWierszy()*_ukladanka->get_gra()->get_rozmiarklocka()+2,210);
    _yPrawyDolnyRogScen=10+_ukladanka->get_gra()->get_liczbaWierszy()*_ukladanka->get_gra()->get_rozmiarklocka()+2;
    //Ustawienie pozycji przyciskow i eteykiet (w group boxach)
    string text= string("Gracz: ")+_ukladanka->get_wybranyGracz().get_imie();
    _glowneOkno->lb_WybranyGracz->setText(QString::fromStdString(text));
    _glowneOkno->gB_Przyciski->move(_xPrawyDolnyRogSceny+10,10);
    _glowneOkno->gB_ListaWynikow->move(_xPrawyDolnyRogSceny+240,10);
    _glowneOkno->gB_Info->move(10,_yPrawyDolnyRogScen+5);
   //Wielkosc formatki
    int height=_xPrawyDolnyRogSceny+10+70<400?400:_xPrawyDolnyRogSceny+10+70;
    setFixedSize(_xPrawyDolnyRogSceny+10+220+70+200,height);
}
void MainWindow::StartujNowaGre()
{
    ZacznijNowaGre(2, 40,0);
    UaktualnijGeometrieKontrolek();
    _glowneOkno->lb_WybranyGracz->setText("GRACZ: "+QString::fromStdString(_ukladanka->get_wybranyGracz().get_imie()));
    _glowneOkno->sb_LiczbaWierszy->setValue(2);
    WyswietlTabeleWynikow();
}

 void MainWindow::ZacznijNowaGre(int n, int rozmKlocka,int liczbaLosowychRuchow)
{
     _glowneOkno->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
     _glowneOkno->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
     _glowneOkno->graphicsView->setAlignment(Qt::AlignTop|Qt::AlignLeft);
     _glowneOkno->graphicsView->setScene(_scena);
      _glowneOkno->lb_Czas->setText("0");
      _glowneOkno->graphicsView->setFixedSize(n*rozmKlocka+2,n*rozmKlocka+2);
      _ukladanka->ZacznijNowaGre( n,  rozmKlocka, liczbaLosowychRuchow);
}

void MainWindow::WyswietlTabeleWynikow(bool sortujCzas)
{
    string nazwaPlikuCzas= string("Dane/")+to_string(_ukladanka->get_gra()->get_liczbaWierszy())+string("_czas.txt");
    string nazwaPlikuKroki= string("Dane/")+to_string(_ukladanka->get_gra()->get_liczbaWierszy())+string("_kroki.txt");
    string nazwaPliku=_glowneOkno->rB_Czas->isChecked()?nazwaPlikuCzas:nazwaPlikuKroki;
    QString dane=_ukladanka->get_gra()->daneDoTabeliWynikow(nazwaPliku,sortujCzas);
    this->_glowneOkno->pt_ListaWynikow->setPlainText(dane);
}

void MainWindow::on_rB_Czas_clicked()
{
   WyswietlTabeleWynikow();
}

void MainWindow::on_rB_Kroki_clicked()
{
   WyswietlTabeleWynikow(false);
}

void MainWindow::on_bt_EkranStartowy_clicked()
{
    this->close();
    emit WywolanoEkranStarowy();

}

void MainWindow::on_bt_ZapiszGre_clicked()
{
    QString defaultPath ="D:/";
    QString fileName = QFileDialog::getSaveFileName(this,
           tr("Zapisz gre"), "",
           tr("Gra (*.gra);;"));

    _ukladanka->get_gra()->ZapiszGreDoPliku(fileName.toStdString());
}

void MainWindow::on_bt_WczytajGre_clicked()
{
    QString defaultPath ="D:/";
    QString fileName = QFileDialog::getOpenFileName(this,"Wczytaj gre",defaultPath,
           tr("Gra (*.gra);;"));

    _ukladanka->get_gra()->WczytajGreZPliku( fileName.toStdString());
    UaktualnijGeometrieKontrolek();
    _glowneOkno->lb_LiczbaKrokow->setText(QString::number(_ukladanka->get_gra()->get_liczbaKrokow()));
    _glowneOkno->graphicsView->setFixedSize(_ukladanka->get_gra()->get_liczbaWierszy()*_ukladanka->get_gra()->get_rozmiarklocka()+2,
                                _ukladanka->get_gra()->get_liczbaWierszy()*_ukladanka->get_gra()->get_rozmiarklocka()+2);
    _glowneOkno->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _glowneOkno->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _glowneOkno->graphicsView->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    _glowneOkno->graphicsView->setScene(_scena);
    _ukladanka->get_gra()->WlaczCzas();

}

Ukladanka* MainWindow::get_ukladanka()
{
    return _ukladanka;
}
