#include "tableroVisual.h"
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>





tableroVisual::tableroVisual(QWidget *parent) : QWidget(parent) {
    // tLogico = new tableroLogico(8, 8, 3);
    // tLogico->colocarMinas();
    // tLogico->calcularMinasAdyacentes();
}


//probablemente hacer algun metodo de destruccion de esto, para que no quede memory leak
void tableroVisual:: inicializarTLogico(int numFilas, int numColumnas, int numMinas){
    tLogico= new tableroLogico(numFilas,numColumnas,numMinas);
    tLogico->colocarMinas();
    tLogico->calcularMinasAdyacentes();
}



void tableroVisual::colocarMinas(){
    //creo que esto no sirve ya que se mantiene todo local
   // vector<vector<Celda>> temp = tLogico->getTablero();
    tLogico->colocarMinas();
}



void tableroVisual::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    if (!tLogico) return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);


    //revisar esto por el deslice de las coords
    int margenIzquierdo = 20;
    int margenSuperior  = 20;
    int ladoTablero     = qMin(width() - 40, height() - 40);
    int tCelda          = ladoTablero / medidaConst;

    // Colores de números clásico buscaminas
    QColor coloresNum[] = {
        Qt::blue, Qt::darkGreen, Qt::red, Qt::darkBlue,
        Qt::darkRed, Qt::cyan, Qt::black, Qt::gray
    };

    QFont fuente = painter.font();
    fuente.setBold(true);
    fuente.setPixelSize(tCelda * 0.5);
    painter.setFont(fuente);

    for (int f = 0; f < tLogico->getFilas(); f++) {
        for (int c = 0; c < tLogico->getColumnas(); c++) {
            Celda &celda = tLogico->obtenerCelda(f, c);

            int x = margenIzquierdo + c * tCelda;
            int y = margenSuperior  + f * tCelda;
            QRect rect(x, y, tCelda, tCelda);

            // ── Color de fondo ──
            if (!celda.estaRevelada()) {
                if (celda.tieneBandera())
                    painter.setBrush(QColor(255, 180, 0));   // amarillo = bandera
                else
                    painter.setBrush(QColor(118, 150, 86));  // verde = no revelada
            } else if (celda.checkStatus()) {
                painter.setBrush(QColor(220, 50, 50));       // rojo = mina
            } else {
                painter.setBrush(QColor(210, 180, 140));     // beige = revelada
            }

            // Borde gris entre celdas
            painter.setPen(QPen(QColor(80, 80, 80), 1));
            painter.drawRect(rect);

            // ── Contenido ──
            if (!celda.estaRevelada() && celda.tieneBandera()) {
                painter.setPen(Qt::red);
                painter.drawText(rect, Qt::AlignCenter, "F");  // bandera

            } else if (celda.estaRevelada() && celda.checkStatus()) {
                painter.setPen(Qt::black);
                painter.drawText(rect, Qt::AlignCenter, "X");  // mina

            } else if (celda.estaRevelada()) {
                int minas = celda.getMinasAdyacentes();
                if (minas > 0) {
                    painter.setPen(coloresNum[minas - 1]);
                    painter.drawText(rect, Qt::AlignCenter, QString::number(minas));
                }
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
    int tCelda = ladoTablero/medidaConst;



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


void tableroVisual::setMedidaConst(int med){
    medidaConst=med;
}
