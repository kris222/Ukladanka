#include "ukladanka.h"
#include "gra.h"
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


string replaceinString(std::string str, std::string tofind, std::string toreplace)
{
        size_t position = 0;
        for ( position = str.find(tofind); position != std::string::npos; position = str.find(tofind,position) )
        {
                str.replace(position ,1, toreplace);
        }
        return(str);
}
Gra::Gra()
{
}
Gra::Gra(int n,  int rozmKlocka, MyScene* s,QTimer* timer, QElapsedTimer* eltimer  )
{
    _elTimer=eltimer;
    _timer=timer;
    _scena=s;
    _liczbaWierszy=n;
    _rozmiarKlocka=rozmKlocka;
    _plansza= Plansza(s,n,rozmKlocka);
}
Gra::~Gra()
{

}

bool Gra::get_dozwoloneKlikanieNaPlansze()
{
    return _dozwoloneKlikanieNaPlansze;
}

void Gra::set_dozwoloneKlikanieNaPlansze(bool dozwoloneKlikanieNaPlansze)
{
    _dozwoloneKlikanieNaPlansze=dozwoloneKlikanieNaPlansze;
}

int Gra::get_czasRozwiazania()
{
    return _czasRozwiazania;
}


void Gra::set_czasRozwiazania(int czasRozwiazania)
{
    _czasRozwiazania=czasRozwiazania;
}

MyScene* Gra::get_scena()
{
    return _scena;
}

void Gra::set_scena(MyScene* scena)
{
   _scena=scena;
}

int Gra::get_liczbaWierszy()
{
  return _liczbaWierszy;
}

Plansza* Gra::get_plansza()
{
  return &_plansza;
}
void Gra::set_plansza(Plansza plansza)
{
   _plansza=plansza;
}

void Gra::set_liczbaWierszy(int liczbaWierszy)
{
  _liczbaWierszy=liczbaWierszy;
}

int Gra::get_rozmiarklocka()
{
  return _rozmiarKlocka;
}

void Gra::set_rozmiarKlocka(int rozmiarKlocka)
{
  _rozmiarKlocka=rozmiarKlocka;
}



int Gra::get_liczbaKrokow()
{
  return _liczbaKrokow;
}
void Gra::set_liczbaKrokow(int liczbaKrokow)
{
  _liczbaKrokow=liczbaKrokow;
}
int Gra::get_aktualnyCzas()
{
  return _aktualnyCzas;
}
void Gra::set_aktualnyCzas(int aktualnyCzas)
{
  _aktualnyCzas=aktualnyCzas;
}

int Gra::get_czasStartowy()
{
  return _czasStartowy;
}
void Gra::set_czasStartowy(int czasStartowy)
{
  _czasStartowy=czasStartowy;
}
int Gra::get_startowaLiczbaKrokow()
{
  return _startowaLiczbaKrokow;
}
void Gra::set_startowaLiczbaKrokow(int startowaLiczbaKrokow)
{
  _startowaLiczbaKrokow=startowaLiczbaKrokow;
}
int ** Gra::get_tablicaRozwiazania()
{
  return _tablicaRozwiazania;
}

int ** Gra::get_tablicaStartowa()
{
  return _tablicaStartowa;
}

const std::vector<int> Gra::get_sentencjaKrokow()
{
  return _sentencjaKrokow;
}
void Gra::set_sentencjaKrokow(std::vector<int> sentencjaKrokow)
{
  _sentencjaKrokow=sentencjaKrokow;
}
QTimer* Gra::get_timer()
{
  return _timer;
}

QElapsedTimer* Gra::get_elTimer()
{
  return _elTimer;
}

void Gra::ZapiszDoListyRekordow(string imie )
{
    string fileNameCzas= string("Dane/")+to_string(_liczbaWierszy)+string("_czas.txt");
    string fileNameKroki= string("Dane/")+to_string(_liczbaWierszy)+string("_kroki.txt");
    ofstream plikCzas ;
    plikCzas.open(fileNameCzas, std::ios_base::app);
    plikCzas << to_string(_czasRozwiazania)+string(";")+ to_string(_liczbaKrokow)+string("k  ") +string("gracz: ")+ imie<< endl ;
    plikCzas.close();
    ofstream plikKroki ;
    plikKroki.open(fileNameKroki, std::ios_base::app);
    plikKroki << to_string(_liczbaKrokow)+string(";")+ to_string(_czasRozwiazania)+string("s  ")+string("gracz: ")+ imie<< endl ;
    plikKroki.close();
}


std::vector<string> Gra::PodzielonyText(string s,string delimiter)
{
vector<string> list;
    size_t pos = 0;
    string token;
    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        list.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    list.push_back(s);
    return list;
}

std::vector<int> Gra::vectorStringTovectorInt(std::vector<string> vecString)
{
vector<int> list;
if (vecString.size()>0 && vecString[0] !="\n"&& vecString[0]!="" )
   for (unsigned int i=0;i<vecString.size();i++)
   {
       list.push_back(stoi(vecString[i]));
   }
    return list;
}
QString Gra::daneDoTabeliWynikow(string sciezkaPliku,bool sortujCzas)
{
    std::multimap<int,string> listaPar;
    std::multimap<int,string>::iterator it;
    QFile file(QString::fromStdString(sciezkaPliku));
    bool plikExists= QFileInfo::exists(QString::fromStdString(sciezkaPliku));
    if (!plikExists)
    {
        return "";
    }

    if(file.open (QIODevice::ReadOnly | QIODevice::Text))
    {
        while (!file.atEnd())
        {
            string line = file.readLine().toStdString();
            vector<string> podzielonaLinia;
            podzielonaLinia=PodzielonyText(line,";") ;
            listaPar.insert(pair<int,string>(stoi(podzielonaLinia[0]),podzielonaLinia[1]));
        }
        file.close ();
    }
    QString wynik;
    for (it=listaPar.begin();it!=listaPar.end();it++)
    {
        std::pair<int,string> linia=*it;
        string jednostka=sortujCzas?string("s "):string("k ");
        string w=to_string(linia.first)+jednostka+ linia.second;
        wynik.append(QString::fromStdString(w));
    }
    return wynik;
}


 void Gra::ZapiszGreDoPliku(string nazwaPliku)
{
    // Zapisuje w pliku textowym dane w osobnych liniach:
    // 1:liczbaWierszy, 2:aktualna liczba krokow, 3: aktualny czas
    // 4: sentencja numerow kierunkow przesuwu pustego pola, ktora doprowadzila
    // do aktualnego stanu
    QString wynik;
    ofstream plikCzas ;
    plikCzas.open(nazwaPliku,  std::ofstream::trunc);
    plikCzas <<to_string(_liczbaWierszy)<<"\n";
    plikCzas <<to_string(_liczbaKrokow)<<"\n";
    plikCzas <<to_string(_aktualnyCzas)<<"\n";
    string a;

    for (unsigned int i=0;i<_plansza.get_sentencjaKrokowLosowych().size();i++)
    {
        string znak=i==_plansza.get_sentencjaKrokowLosowych().size()-1?"\n":";";
        a=a+to_string(_plansza.get_sentencjaKrokowLosowych()[i])+znak;
    }
    plikCzas <<a;
    string b;
    for (unsigned int i=0;i<_sentencjaKrokow.size();i++)
    {
        string znak=i==_sentencjaKrokow.size()-1?"\n":";";
        b=b+to_string(_sentencjaKrokow[i])+znak;
    }
    plikCzas <<b;
    plikCzas.close();
}


void Gra::WlaczCzas()
{
    _timer->start(1000);
    _elTimer->start();
}

void Gra::UtworzTabliceRozwiazania()
{
    _tablicaRozwiazania = new int*[unsigned(_liczbaWierszy)];
    int k = 0;
    for (int i = 0; i < _liczbaWierszy; i++)
    {
        _tablicaRozwiazania[i] = new int[unsigned(_liczbaWierszy)];
        for (int j = 0; j < _liczbaWierszy; j++)
            _tablicaRozwiazania[i][j] = ++k;
    }
    _tablicaRozwiazania[_liczbaWierszy-1][_liczbaWierszy-1] = 0;
}

bool Gra::graJestRozwiazana()
{
    for (int i = 0; i < _liczbaWierszy; i++)
        for (int j = 0; j < _liczbaWierszy; j++)
        {
            if(_plansza.ukladKlockow[i][j].get_numer()!=_tablicaRozwiazania[i][j])
               return false;
        }
     return true;
}

void Gra::UtworzLosowaPlansze(int n)
{
    UtworzTabliceRozwiazania();
    _plansza.PrzemieszajKlocki(n,_tablicaRozwiazania);
    _liczbaKrokow=0;
    _startowaLiczbaKrokow=0;
    if (n>0)
    emit PrzestawionoKlocek();
}
int Gra::KierunekPrzeciwny(int kierunek)
{
    switch (kierunek)
    {
    case 0:
        return 2;
    case 1:
        return 3;
    case 2:
        return 0;
    case 3:
        return 1;
    }
    return-1;
}
void Gra::KlikniecieNaPlansze()
{
    if(!_dozwoloneKlikanieNaPlansze) return;
    int x=_scena->get_x();
    int y=_scena->get_y();
    bool kliknietoNaPlansze=x>0 && x<_liczbaWierszy*_rozmiarKlocka&&y>0 && x<_liczbaWierszy*_rozmiarKlocka;
    int i=static_cast<int>(x/_rozmiarKlocka);
    int j=static_cast<int>(y/_rozmiarKlocka);
    Klocek* kliknietyKlocek=&_plansza.ukladKlockow[j][i];
    if (kliknietoNaPlansze && kliknietyKlocek->SasiadujeZPustym())
    {
        int kierPrzesuwu=_plansza.ukladKlockow[j][i].KierunekPrzesuwuWStronePustego();
        int m=-1;
        int n=-1;
        _liczbaKrokow++;
        emit PrzestawionoKlocek();
    _sentencjaKrokow.push_back(KierunekPrzeciwny(kierPrzesuwu));
        switch (kierPrzesuwu)
        {
        case 0:
            m=i-1;
            n=j;
            break;
        case 1:
            m=i;
            n=j-1;
                break;
        case 2:
            m=i+1;
            n=j;
                break;
        case 3:
            m=i;
            n=j+1;
                break;

        }
        _plansza.ukladKlockow[n][m].set_numer(_plansza.ukladKlockow[j][i].get_numer());
        _plansza.ukladKlockow[j][i].set_numer(0);

        _plansza.ukladKlockow[j][i].Rysuj(Qt::green,_scena);
        _plansza.ukladKlockow[n][m].Rysuj(Qt::green,_scena);
        if (graJestRozwiazana())
        {
           _plansza.RysujUkladKlockow(Qt::red);
           emit RozwiazanoUkladanke();
        }
    }

}
void Gra::WczytajGreZPliku(string nazwaPliku)
{
    QFile file(QString::fromStdString(nazwaPliku));
    bool plikExists= QFileInfo::exists(QString::fromStdString(nazwaPliku));
    if (!plikExists)
    {

    }
    if(file.open (QIODevice::ReadOnly | QIODevice::Text))
    {
        string line0 = file.readLine().toStdString();
         int lwierszy=stoi(line0);
         string line2 = file.readLine().toStdString();
        int kroki=stoi(line2); string line1 = file.readLine().toStdString();
        int czas=stoi(line1);
        string line4 = file.readLine().toStdString();
        vector<int>los=vectorStringTovectorInt(PodzielonyText(line4,";")) ;
        string line5 = file.readLine().toStdString();
        vector<int>krokiUsera=vectorStringTovectorInt(PodzielonyText(line5,";")) ;
        file.close ();
        vector<int> ruchy;
        ruchy.insert( ruchy.end(), los.begin(), los.end() );
        ruchy.insert( ruchy.end(), krokiUsera.begin(), krokiUsera.end() );
        set_dozwoloneKlikanieNaPlansze(true);
        set_czasStartowy(czas);
        set_startowaLiczbaKrokow(kroki);
        set_liczbaKrokow(kroki);
        set_liczbaWierszy(lwierszy);
        set_plansza(Plansza(_scena,lwierszy,40));
        UtworzTabliceRozwiazania();
        _plansza.RysujPlanszeBezKlockow();
        _plansza.WczytajZTablicy(get_tablicaRozwiazania());
        _plansza.RysujUkladKlockow(Qt::green);
        _plansza.ZnajdzSasiadowKlockow();
        for (unsigned int i=0;i< ruchy.size();i++)
        {
            _plansza.przesunPusty(ruchy[i]);
        }
    }
}

