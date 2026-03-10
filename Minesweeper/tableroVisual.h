#ifndef TABLEROVISUAL_H
#define TABLEROVISUAL_H

#include "tableroLogico.h"
#include<QWidget>


class tableroVisual: public QWidget{
    Q_OBJECT


public:
    //declarando que sera una ventana independiente
    explicit tableroVisual(QWidget *parent= nullptr);


    void inicializarTLogico(int numFilas, int numColumnas, int numMinas);
    void colocarMinas();


protected:
    void paintEvent(QPaintEvent *event) override;


    void mousePressEvent(QMouseEvent *event) override;


    QSize sizeHint() const override{
        return QSize(500,600);

    }

private:
    //almacenamos una referencia del tablero logico

    tableroLogico* tLogico=nullptr;


};




#endif // TABLEROVISUAL_H
