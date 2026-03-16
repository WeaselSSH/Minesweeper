#ifndef TABLEROVISUAL_H
#define TABLEROVISUAL_H

#include "tableroLogico.h"
#include "manejousuario.h"

#include<QWidget>
#include <QTimer>

class tableroVisual: public QWidget{
    Q_OBJECT

public:
    //declarando que sera una ventana independiente
    explicit tableroVisual(ManejoUsuario* manejoPtr, QWidget *parent = nullptr);

    void inicializarTLogico(int numFilas, int numColumnas, int numMinas);
    void colocarMinas();
    void setMedidaConst(int med);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

    QSize sizeHint() const override{
        return QSize(500,600);
    }

private:
    ManejoUsuario* mManejo;

    //almacenamos una referencia del tablero logico
    tableroLogico* tLogico = nullptr;
    int medidaConst;
    bool juegoTerminado = false;

    //agregar espaciado segun dificultad
    QTimer* cronometro;
    int tiempoTranscurrido;//esto nos ayudara a llevar control del tiempo

    QString formatTime() const;

    int obtenerTiempoPartida() const;
};

#endif // TABLEROVISUAL_H
