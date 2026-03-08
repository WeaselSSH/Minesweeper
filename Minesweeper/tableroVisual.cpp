#include "tableroVisual.h"
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>





tableroVisual::tableroVisual(QWidget *parent) : QWidget(parent){ }



//probablemente hacer algun metodo de destruccion de esto, para que no quede memory leak
void tableroVisual:: inicializarTLogico(){
    tLogico= new tableroLogico(8,8,1);

}



void tableroVisual::colocarMinas(){
    //creo que esto no sirve ya que se mantiene todo local
   // vector<vector<Celda>> temp = tLogico->getTablero();
    tLogico->colocarMinas(tLogico->getTablero(),0,0,0);
}



void tableroVisual::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); //bordes suaves

    //calculo de medidas
    int margenIzquierdo=20;
    int margenSuperior=20;
    int ladoTablero =qMin(width()-40, height()-40); //calculamos el tamao optimo
    int tCelda = ladoTablero/8;


    //pintado de celdas en base a tablero Logico

    for(int f=0; f<tLogico->getFilas(); f++){
        for(int c=0; c<tLogico->getColumnas(); c++){


            //si la celda no esta reveldada
            if(!tLogico->obtenerCelda(f,c).estaRevelada()){
                QColor colorCelda = QColor(118,150,86);

                //calculamos las coordenas de donde se dibujara la casilla
                int x=margenIzquierdo+ (c*tCelda);
                int y= margenSuperior + (f*tCelda);

                //dibujado de cuadricula
                painter.setBrush(colorCelda);
                painter.setPen(Qt::NoPen);
                painter.drawRect(x,y, tCelda, tCelda);
            }else{
                QColor colorCelda = QColor(255,255,255);
                int x=margenIzquierdo+ (c*tCelda);
                int y= margenSuperior + (f*tCelda);

                //dibujado de cuadricula
                painter.setBrush(colorCelda);
                painter.setPen(Qt::NoPen);
                painter.drawRect(x,y, tCelda, tCelda);
            }

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


    tLogico->revelarCelda(fila, columna);

    //delimitamos a que estemos dentro de los limites validos del tablero
    if(fila>=0 && fila<8 && columna>= 0 && columna<8){
        qDebug() <<"Fila: "<<fila<<" Columna: "<<columna;
    }else{
        qDebug() <<"Estamos fuera de los limites bro";
    }

    this->update();

    /*
     * ----NOTA PARA CAMBIOS-----
     * Ahora que ya se detectan los clicks y se pasa a filas y columnas, aqui dentro deberia ir la logica
     * para que, al darle click, esa accion pase al tablero Logico
     *
     * Cosas que se podrian hacer:
     * -Linkear tablero logico con tablero visual....[X]
     * -Crear funcion para que tablero visual lea tablero logico y haga repaint en base a eso.....[]
     *
     * */
}

