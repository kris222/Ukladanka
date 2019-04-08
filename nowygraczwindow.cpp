#include "nowygraczwindow.h"
#include "ui_nowygraczwindow.h"
#include "graczwindow.h"
#include <QMainWindow>


nowygraczwindow::nowygraczwindow(Ukladanka* u,Ui::graczWindow *t,QWidget *parent ) :
    QMainWindow(parent),
    _oknoNowyGracz(new Ui::nowygraczwindow)
{
    _oknoNowyGracz->setupUi(this);
_ukladanka=u;
}
nowygraczwindow::nowygraczwindow(QMainWindow* w,Ukladanka* u,Ui::graczWindow *t,QWidget *parent ):
    QMainWindow(parent),
    _oknoNowyGracz(new Ui::nowygraczwindow)

{
     _oknoNowyGracz->setupUi(this);
     _ukladanka=u;
     _oknoGracze=t;
}
nowygraczwindow::~nowygraczwindow()
{
    delete _oknoNowyGracz;
}

///
/// \brief Klikniecie na przycisk Dodaj (gracza)
///
void nowygraczwindow::on_pushButton_clicked()
{
    Gracz k= Gracz(_oknoNowyGracz->teNowyGracz->toPlainText().toStdString());
    _ukladanka->DodajGracza(k);
    _oknoNowyGracz->teNowyGracz->setText("");
    this->close();
}

///
/// \brief Klikniecie na przycisk Rezygnuj
///
void nowygraczwindow::on_pushButton_2_clicked()
{
    this->close();
}
