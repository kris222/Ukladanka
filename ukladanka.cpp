#include "ukladanka.h"
#include "mojeszablony.h"
#include "plansza.h"
#include <QTextStream>
#include <QFile>
#include <QLineEdit>
#include <iostream>
#include <fstream>
#include <QElapsedTimer>
#include <QDebug>
#include <QFileInfo>
#include <set>
using namespace std;

Ukladanka::Ukladanka()
{
}
Ukladanka::Ukladanka(int n,  int rozmKlocka, MyScene* s )
{
    _scena=s;
    _gra=new Gra( n,  rozmKlocka, s, &_timer, &_elTimer);
    _gracze= std::vector<Gracz>();
    WczytajGraczyZPliku();
}
Ukladanka::~Ukladanka()
{

}
Gra* Ukladanka::get_gra()
{
  return _gra;
}

void Ukladanka::ZacznijNowaGre(int n, int rozmKlocka,int liczbaLosowychRuchow)
{
    _gra->set_czasStartowy(0);
    _gra->set_sentencjaKrokow( std::vector<int>());
    _gra->get_plansza()->set_sentencjaKrokowLosowych( std::vector<int>());
    _gra->set_dozwoloneKlikanieNaPlansze(liczbaLosowychRuchow>0);
    _gra->set_liczbaWierszy(n);
    _gra->set_liczbaKrokow(0);
    _gra->set_plansza( Plansza(_scena,n,rozmKlocka));
    _gra->UtworzLosowaPlansze(liczbaLosowychRuchow);
}

void Ukladanka::set_wybranyGracz(Gracz gracz)
{
    _wybranyGracz=gracz;
}
Gracz Ukladanka::get_wybranyGracz()
{
    return _wybranyGracz;
}

std::vector<Gracz> Ukladanka::get_gracze()
{
    return _gracze;
}
void Ukladanka::sortuj_Graczy()
{
    Sortuj(_gracze,static_cast<int>(_gracze.size()));
}

MyScene* Ukladanka::get_scena()
{
    return _scena;
}

void Ukladanka::WczytajGraczyZPliku()
{

    QFile file("Dane/gracze.txt");
    if(file.open (QIODevice::ReadOnly | QIODevice::Text))
    {

        while (!file.atEnd())
        {
           string line = file.readLine().toStdString();

           line.erase( std::remove(line.begin(), line.end(), '\n'), line.end() );
           Gracz k=Gracz(line);
          _gracze.push_back(k);
        }
        file.close ();
    }
    Sortuj(_gracze,static_cast<int>(_gracze.size()));
}

QTimer* Ukladanka::get_timer()
{
    return &_timer;
}


QElapsedTimer* Ukladanka::get_elTimer()
{
   return &_elTimer;
}


void Ukladanka::ZapiszGraczyDoPliku()
{
    ofstream myfile ("Dane/gracze.txt");
    myfile.clear();
    for (unsigned int i=0;i<_gracze.size();i++)
    {
        myfile<<_gracze[i].get_imie()<<endl;
    }
    myfile.close();
}

void Ukladanka::DodajGracza(Gracz nowyGracz)
{

    _gracze.push_back(nowyGracz);
    emit ZaktualizowanoListeGraczy();
}

void Ukladanka::UsunGracza(int index)
{
    std::vector<Gracz>::iterator it;
    _gracze.erase(_gracze.begin()+index);
    emit ZaktualizowanoListeGraczy();
}



