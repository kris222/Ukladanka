#include "myscene.h"
//#include "ukladanka.h"
#include "QtGui"
#include <QGraphicsSceneMouseEvent>
#include <QEvent>

MyScene::MyScene()
{

}
MyScene::~MyScene()
{

}
void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    _x=static_cast<int>(event->scenePos().x());
    _y=static_cast<int>(event->scenePos().y());
    emit mousePressed();
}

int MyScene::get_x()
{
   return _x;
}

int MyScene::get_y()
{
   return _y;
}

