#include "klocek.h"
#include "pozycja.h"
#include <array>

Klocek::Klocek()
{
    set_numer(-1);
    set_pozycja(-1,-1);
    set_blokujeInneKlocki(false);
}
Klocek::Klocek(int nr,Pozycja poz,int rozmKlocka)
{
    set_numer(nr);
    set_pozycja(poz);
    set_blokujeInneKlocki(false);
    set_rozmiar(rozmKlocka);
}
Klocek::~Klocek()
{

}
int Klocek::get_rozmiar()
{
    return _rozmiar;
};


void Klocek::set_rozmiar(int rozmiar)
{
    _rozmiar=rozmiar;

};

int Klocek::get_numer()
{
    return _numer;
};

void Klocek::set_numer(int numer)
{
    _numer=numer;

};


void Klocek::set_pozycja(int wiersz, int kolumna)
{
   _pozycja=Pozycja (wiersz,kolumna) ;
}


void Klocek::set_pozycja(Pozycja pozycja)
{
    _pozycja=pozycja;
}

Pozycja Klocek::get_pozycja()
{
    return _pozycja;

}

void Klocek::set_blokujeInneKlocki(bool blokuje)
{
    _blokujeInneKlocki=blokuje;
}

int Klocek::get_blokujeInneKlocki()
{
    return _blokujeInneKlocki;
}

void Klocek::Rysuj( QColor kolor,QGraphicsScene *scena)
{
    QPen myPen =  QPen();
    myPen.setWidth(1);
    myPen.setBrush(Qt::black);
    if (_numer!=0)
    {       
        QBrush brush1 = QBrush(kolor, Qt::SolidPattern);
        scena->addRect(_pozycja.get_kolumna()*_rozmiar+2, _pozycja.get_wiersz()*_rozmiar+2,_rozmiar-6, _rozmiar-6,myPen,brush1);
        // Definicja czcionki
        QFont font;
        font.setPixelSize(20);       
        font.setBold(false);
        font.setFamily("Calibri");
        QGraphicsTextItem* text = new QGraphicsTextItem();
        text->setFont(font);
        text->setPos(_pozycja.get_kolumna()*_rozmiar+2, _pozycja.get_wiersz()*_rozmiar+2);
        text->setPlainText(QString::number(_numer));
        scena->addItem(text);
    }
    else// puste pole
    {
        QBrush brush1 = QBrush(Qt::black, Qt::SolidPattern);
        scena->addRect(_pozycja.get_kolumna()*_rozmiar+2, _pozycja.get_wiersz()*_rozmiar+2,_rozmiar-6, _rozmiar-6,myPen,brush1);
    }
}



std::array<int, 2> Klocek::KierunkiDoCelu(Pozycja cel)
{
    std::array<int, 2> res;
     // Wspolrzedne wektora skierowanego od klocka do celu
    int dx=cel.get_kolumna()-_pozycja.get_kolumna();
    int dy=cel.get_wiersz()-_pozycja.get_wiersz();
    if (abs(dx)>abs(dy))
    {
        res[0]=dx>=0?2:0;
        res[1]=dy>=0?3:1;
    }
    else
    {
        res[0]=dy>=0?3:1;
        res[1]=dx>=0?2:0;
    }
   return res;
}

bool Klocek::SasiadujeZPustym()
{
    return sasiedzi[0]->_numer*sasiedzi[1]->_numer*sasiedzi[2]->_numer*sasiedzi[3]->_numer==0;
}

int Klocek::KierunekPrzesuwuWStronePustego()
{
    for (int i=0;i<4;i++)
        if(sasiedzi[i]->_numer==0) return i;
    return-1;
}

