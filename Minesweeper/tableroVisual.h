#ifndef TABLEROVISUAL_H
#define TABLEROVISUAL_H

#include "tableroLogico.h"
#include "manejousuario.h"

#include<QWidget>
#include <QTimer>
#include <QPixmap>
#include <QFont>

class tableroVisual: public QWidget{
    Q_OBJECT

public:
    //declarando que sera una ventana independiente
    explicit tableroVisual(ManejoUsuario* manejoPtr, QWidget *parent = nullptr);

    void inicializarTLogico(int numFilas, int numColumnas, int numMinas);
    void colocarMinas();
    void setMedidaConst(int med);

    void setgameModeV(char gameMode);
    void inicializarFondo();

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

    //cosas para cargar imagenes
    QPixmap pixmapBandera;
    QPixmap pixmapMina;
    QPixmap pixmapHiddenTile;
    QFont fuentePersonalizada;

    //cosas para fondos
    QPixmap pixmapFondo;


    //cosas para simulacion de radar
    float anguloRadar=0.0f;

    char gameModeV;




};

#endif // TABLEROVISUAL_H
