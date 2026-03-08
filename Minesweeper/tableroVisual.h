#ifndef TABLEROVISUAL_H
#define TABLEROVISUAL_H

//#include "tableroLogico.h"
#include<QWidget>


class tableroVisual: public QWidget{
    Q_OBJECT


public:
    //declarando que sera una ventana independiente
    explicit tableroVisual(QWidget *parent= nullptr);
    //, tableroLogico m_tablero



protected:
    void paintEvent(QPaintEvent *event) override;


    void mousePressEvent(QMouseEvent *event) override;


    QSize sizeHint() const override{
        return QSize(500,600);

    }

private:
    //almacenamos una referencia del tablero logico
    //tableroLogico tablero;
};




#endif // TABLEROVISUAL_H
