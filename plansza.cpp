#include "plansza.h"
#include "mojeszablony.h"
#include <chrono>
#include <ctime>
#include <array>
Plansza::Plansza()
{

}

Plansza::Plansza(MyScene* s,int n,int r)
{
    _scena = s;
    _liczbaWierszy = n;
    _rozmiarKlocka=r;

}

Plansza::~Plansza()
{

}
void Plansza::WczytajZTablicy(int** tablica)
{
    ukladKlockow=  new Klocek*[unsigned (_liczbaWierszy)];
     for (int i = 0; i < _liczbaWierszy; i++)
     {
         ukladKlockow[i] = new Klocek [unsigned (_liczbaWierszy)];
         for (int j = 0; j < _liczbaWierszy; j++)
         {
             ukladKlockow[i][j].set_numer(tablica[i][j]);
             ukladKlockow[i][j].set_pozycja( Pozycja(i,j));
             ukladKlockow[i][j].set_rozmiar(_rozmiarKlocka);
             if(tablica[i][j]==0)
             _pustePole=&ukladKlockow[i][j];
         }
     }
}


MyScene* Plansza::get_scena()
{
    return _scena;
}

void Plansza::set_scena(MyScene* scena)
{
   _scena=scena;
}

int Plansza::get_liczbaWierszy()
{
  return _liczbaWierszy;
}


void Plansza::set_sentencjaKrokowLosowych(std::vector<int> sentencjaKrokowLosowych)
{
   _sentencjaKrokowLosowych=sentencjaKrokowLosowych;
}

std::vector<int> Plansza::get_sentencjaKrokowLosowych()
{
  return _sentencjaKrokowLosowych;
}

void Plansza::set_liczbaWierszy(int liczbaWierszy)
{
  _liczbaWierszy=liczbaWierszy;
}

Klocek* Plansza::get_pustePole()
{
  return _pustePole;
}

void Plansza::set_PustePole(Klocek* pusty)
{
  _pustePole=pusty;
}

int Plansza::get_rozmiarklocka()
{
  return _rozmiarKlocka;
}

void Plansza::set_rozmiarKlocka(int rozmiarKlocka)
{
  _rozmiarKlocka=rozmiarKlocka;
}


void Plansza::ZapiszDoTablicy(int** tablica)
{
    tablica = new int*[unsigned(_liczbaWierszy)];
    for (int i = 0; i < _liczbaWierszy; i++)
    {
        tablica[i] = new int[unsigned(_liczbaWierszy)];
        for (int j = 0; j < _liczbaWierszy; j++)
        {
            tablica[i][j] = ukladKlockow[i][j].get_numer();
        }
    }
}

void Plansza::RysujPlanszeBezKlockow()
{
    QPen myPen =  QPen();
    myPen.setWidth(2);
    myPen.setBrush(Qt::black);
    QBrush brush1 = QBrush(QColor(255,170,255), Qt::SolidPattern);
    QBrush background_brush = QBrush( QColor(255,170,255), Qt::SolidPattern);
    _scena->addRect(0,0,_liczbaWierszy*40,_liczbaWierszy*40, myPen,brush1);
    for (int i = 0; i < _liczbaWierszy+1; i++)
    {
        _scena->addLine( 0, i * _rozmiarKlocka, (_liczbaWierszy+0) * _rozmiarKlocka, (i+0) * _rozmiarKlocka,myPen);
        _scena->addLine( i * _rozmiarKlocka, 0, (i+0)*_rozmiarKlocka, (_liczbaWierszy+0) * _rozmiarKlocka,myPen);
    }
}



void Plansza::UtworzUkladKlockowRozwiazania()

{
    ukladKlockow= new Klocek*[unsigned (_liczbaWierszy)];
     for (int i = 0; i < _liczbaWierszy; i++)
     {
         ukladKlockow[i] = new Klocek [unsigned (_liczbaWierszy)];
     }
}


void Plansza::RysujUkladKlockow(QColor kolor)
{
    for (int i = 0; i < _liczbaWierszy; i++)
        for (int j = 0; j < _liczbaWierszy; j++)
            ukladKlockow[j][i].Rysuj(kolor,_scena);
}

void Plansza::ZnajdzSasiadowKlockow()
{
    for (int i = 0; i < _liczbaWierszy; i++)
        for (int j = 0; j < _liczbaWierszy; j++)
        {

            Klocek *klocek=&ukladKlockow[i][j];         
            int xLewy=klocek->get_pozycja().get_kolumna()-1<0?-1:klocek->get_pozycja().get_kolumna()-1;
            int yLewy=klocek->get_pozycja().get_wiersz();
            int xPrawy=klocek->get_pozycja().get_kolumna()+1>_liczbaWierszy?-1:klocek->get_pozycja().get_kolumna()+1;
            int yPrawy=klocek->get_pozycja().get_wiersz();
            int xGora=klocek->get_pozycja().get_kolumna();
            int yGora=klocek->get_pozycja().get_wiersz()-1<0?-1:klocek->get_pozycja().get_wiersz()-1;
            int xDol=klocek->get_pozycja().get_kolumna();
            int yDol=klocek->get_pozycja().get_wiersz()+1>_liczbaWierszy?-1:klocek->get_pozycja().get_wiersz()+1;
            klocek->sasiedzi[0]=xLewy>=0?&ukladKlockow[yLewy][xLewy]:new Klocek();
            klocek->sasiedzi[1]=yGora>=0?&ukladKlockow[yGora][xGora]:new Klocek();
            klocek->sasiedzi[2]=xPrawy<=_liczbaWierszy-1?&ukladKlockow[yPrawy][xPrawy]:new Klocek();
            klocek->sasiedzi[3]=yDol<=_liczbaWierszy-1?&ukladKlockow[yDol][xDol]:new Klocek();
        }
}

int Plansza::LosowyKierunek()
{
   // srand((int)time(NULL));
   int y=rand() %4;
   return y;
}

void Plansza::PomieszajKlockiLosowo(int n)
    {
    if (n<=0 )return;
    int prev=3;
    int zabronionyKierunek=0;// kierunek zabroniony- aby sie nie cofnac do poprzedniej pozycji   
    int liczbaLosowychRuchow=_liczbaWierszy>7?1500:n;
    if(_liczbaWierszy>1)
        for (int i = 0; i < liczbaLosowychRuchow; i++)
        {
            if(prev==0) zabronionyKierunek=2;
            if(prev==1) zabronionyKierunek=3;
            if(prev==2) zabronionyKierunek=0;
            if(prev==3) zabronionyKierunek=1;
            int k=LosowyKierunek();
            if (k!=zabronionyKierunek)
            {
             przesunPusty(k);
             int w=k+1==4?0:k+1;
             przesunPusty(w);
             _sentencjaKrokowLosowych.push_back(k);
             _sentencjaKrokowLosowych.push_back(w);
          }
        prev=k;
        }
}
void Plansza::przesunPusty(int kierunek)
{
    int i=_pustePole->get_pozycja().get_wiersz();
    int j=_pustePole->get_pozycja().get_kolumna();
    if(ukladKlockow[i][j].sasiedzi[kierunek]->get_blokujeInneKlocki()||ukladKlockow[i][j].sasiedzi[kierunek]->get_numer()==-1)
        return;
    int kierPrzesuwu=kierunek;
    int m=-1;
    int n=-1;

    if(kierPrzesuwu==0)
        {
            n=j-1;
            m=i;
        }
        if(kierPrzesuwu==1)
        {
            n=j;
            m=i-1;
        }

        if(kierPrzesuwu==2)
        {
            n=j+1;
            m=i;
        }

        if(kierPrzesuwu==3)
        {
            n=j;
            m=i+1;
        }

        //ZamienDwaObjekty(ukladKlockow[i][j],ukladKlockow[m][n]);
        ukladKlockow[i][j].set_numer(ukladKlockow[m][n].get_numer());
        ukladKlockow[m][n].set_numer(0);
        _pustePole=&ukladKlockow[m][n];
        ukladKlockow[i][j].Rysuj(Qt::green,_scena);
        ukladKlockow[m][n].Rysuj(Qt::green,_scena);
}

bool Plansza::kierunekPustegoKlockaJestMozliwy(int kier)
{
    return !_pustePole->sasiedzi[kier]->get_blokujeInneKlocki() ;
}

bool Plansza::PustyJestSasiademCelu(Pozycja cel)
{
    int a0 =ukladKlockow[cel.get_kolumna()][cel.get_wiersz()].sasiedzi[0]->get_numer();
    int a1 =ukladKlockow[cel.get_kolumna()][cel.get_wiersz()].sasiedzi[1]->get_numer();
    int a2 =ukladKlockow[cel.get_kolumna()][cel.get_wiersz()].sasiedzi[2]->get_numer();
    int a3 =ukladKlockow[cel.get_kolumna()][cel.get_wiersz()].sasiedzi[3]->get_numer();
    if(a0*a1*a2*a3==0) return true;
    return false;

}
void Plansza::PrzesunPustyKlocekWSasiedztwoCelu(Pozycja cel)
{
     _krokiRozwiazania= std::vector<int>();
    do
    {
        Klocek* pustyKlocek=&ukladKlockow[_pustePole->get_pozycja().get_wiersz()][_pustePole->get_pozycja().get_kolumna()];
        std::array<int, 2> kierunki;
        kierunki= pustyKlocek->KierunkiDoCelu(cel);
        if(kierunekPustegoKlockaJestMozliwy(kierunki[0]))
        {
            przesunPusty(kierunki[0]);
            _krokiRozwiazania.push_back(kierunki[0]);
        }
        else {
            if(kierunekPustegoKlockaJestMozliwy(kierunki[1]))
            {
               przesunPusty(kierunki[1]);
               _krokiRozwiazania.push_back(kierunki[1]);
            }
        }
    }
        while (!PustyJestSasiademCelu( cel));
}

void Plansza::PrzemieszajKlocki(int n,int** tablica)
{
    RysujPlanszeBezKlockow();
    WczytajZTablicy(tablica);
    RysujUkladKlockow(Qt::green);
    ZnajdzSasiadowKlockow();
    PomieszajKlockiLosowo(n);

}

