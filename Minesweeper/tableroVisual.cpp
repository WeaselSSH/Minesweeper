#include "tableroVisual.h"
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>





tableroVisual::tableroVisual(QWidget *parent) : QWidget(parent){}



void tableroVisual::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); //bordes suaves

    //calculo de medidas
    int margenIzquierdo=20;
    int margenSuperior=20;
    int ladoTablero =qMin(width()-40, height()-40); //calculamos el tamao optimo
    int tCelda = ladoTablero/8;


    //AVISO> EVENTUALMENTE SE TENDRA QUE INCLUIR COMO PARAMETRO O ALGO EL TABLERO LOGICO, A MANERA QUE EL VISUAL DEPENDA DEL LOGICO

    for(int f=0; f<8; f++){
        for(int c=0; c<8; c++){

            bool esOscuro= (f+c) %2 !=0;

            QColor colorCelda = esOscuro ? QColor(118,150,86) : QColor(238,238,210);

            //calculamos las coordenas de donde se dibujara la casilla
            int x=margenIzquierdo+ (c*tCelda);
            int y= margenSuperior + (f*tCelda);

            //dibujado de cuadricula
            painter.setBrush(colorCelda);
            painter.setPen(Qt::NoPen);
            painter.drawRect(x,y, tCelda, tCelda);

        }
    }
}


void tableroVisual::mousePressEvent(QMouseEvent *event){
    QPoint pointClick;
    if(event->button()==Qt::LeftButton){
        pointClick= event->pos();
    }

    //Mismas medidas de settings usadas en la creacion del tablero, pues hay que tenerlas en consideracion
    //para sacar las medidas reales de filas y columnas

    int margenIzquierdo=20;
    int margenSuperior=20;
    int ladoTablero =qMin(width()-40, height()-40); //calculamos el tamao optimo
    int tCelda = ladoTablero/8;



    //obtencion de medidas reales de filas y columnas
    int fila= (pointClick.y() -margenSuperior)/tCelda;
    int columna = (pointClick.x()-margenIzquierdo)/tCelda;

    //delimitamos a que estemos dentro de los limites validos del tablero
    if(fila>=0 && fila<8 && columna>= 0 && columna<8){
        qDebug() <<"Fila: "<<fila<<" Columna: "<<columna;
    }else{
        qDebug() <<"Estamos fuera de los limites bro";
    }

}

