#ifndef MYSCENE_H
#define MYSCENE_H
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
//#include "ukladanka.h"
#include <QEvent>



///
/// \brief Scena dziedziczaca z QGraphicsScene,
/// z obsluga zdarzenia klikniecia mysza
///
class MyScene : public QGraphicsScene
{
    Q_OBJECT
public:
    ///
    /// \brief Domyslny konstruktor
    ///
    MyScene();

    ///
    /// \brief Destruktor
    ///
    ~MyScene();
private:

    ///
    /// \brief Wspolrzedna x polozenia myszy w czasie klikniecia na scene
    ///
    int _x;

    ///
    /// \brief Wspolrzedna y polozenia myszy w czasie klikniecia na scene
    ///
    int _y;

public:
    ///
    /// \brief metoda wywolana na zdarzenie klikniecia mysza na scene
    /// \param event
    ///
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    ///
    /// \brief get_x: Pobiera wspolrzedna polozenia myszy podczas klikniecia na scene
    /// \return Wspolrzedna polozenia myszy podczas klikniecia na scene
    ///
    int get_x();

    ///
    /// \brief get_x: Pobiera wspolrzedna polozenia myszy podczas klikniecia na scene
    /// \return Wspolrzedna polozenia myszy podczas klikniecia na scene
    ///
    int get_y();
signals:

    ///
    /// \brief Sygnal zdarzenia emitowany przy obsludze zdarzenia klikniecia myszy
    ///
    void mousePressed();


};

#endif // MYSCENE_H
