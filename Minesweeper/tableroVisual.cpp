#include "tableroVisual.h"
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QMessageBox>
#include <QString>




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


    //----PINTADO DE FONDO---
    //Parte de los stats
    int altoStats= 100;
    int espaciadoVertical=50;
    int margenTablero=20;

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(45,45,48));
    painter.drawRect(0,0, width(), altoStats);


    //fondo atras del tablero
    painter.setBrush(QColor(30,30,30));
    painter.drawRect(0,altoStats, width(), height()-altoStats);


    //calculo de espacio disponible despues de la parte de stats
    int anchoDisponible = width()-(margenTablero*2);
    int altoDisponible = height() -altoStats -espaciadoVertical - (margenTablero);







    //revisar esto por el deslice de las coords
    //int margenIzquierdo = 20;
    //int margenSuperior  = 20;
    int ladoTablero  = qMin(anchoDisponible, altoDisponible);

    //medidas para centrado extra
    int margenX= (width()-ladoTablero)/2;
    int margenY=  altoStats +espaciadoVertical; //altoStats + (height()-ladoTablero)/2 + margenTablero;



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

            int x = margenX + c * tCelda;
            int y = margenY+ f * tCelda;
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
                painter.drawText(rect, Qt::AlignCenter, "🚩");  // bandera

            } else if (celda.estaRevelada() && celda.checkStatus()) {
                painter.setPen(Qt::black);
                painter.drawText(rect, Qt::AlignCenter, "💣");  // mina

            } else if (celda.estaRevelada()) {
                int minas = celda.getMinasAdyacentes();
                if (minas > 0) {
                    painter.setPen(coloresNum[minas - 1]);
                    painter.drawText(rect, Qt::AlignCenter, QString::number(minas));
                }
            }
        }
    }


    //DESARROLLO DE BOTON PARA ABANDONAR PARTIDA
    /*
     * PARA TODO ELEMENTO QUE QUERRAMOS PINTAR EN PANTALLA, EN UN ESPACIO QUE NO ESTE PEGADO A LOS MARGENES
     * SIEMPRE SE TENDRA QUE CALCULAR UN MARGEN X y Y
     *
     *
     * */

    int tamanioBttSalir = 60;
    int margenBttSalir=15;

    int bttX= width()- tamanioBttSalir - margenBttSalir;
    int bttY = (altoStats- tamanioBttSalir)/2;

    painter.setBrush(QColor(200,50,50));
    painter.setPen(QPen(Qt::white, 2));
    QRect bttSalir(bttX, bttY, tamanioBttSalir, tamanioBttSalir);
    painter.drawRoundedRect(bttSalir, 5,5);







    //pintamos texto
    painter.setPen(Qt::white);
    QFont font = painter.font();
    font.setBold(true);
    font.setPointSize(14);
    painter.setFont(font);

    int countBanderas =tLogico->getNumBanderasPuestas();
    QString  strCBanderas = "🚩:"+QString::number(countBanderas);
    //no se pueden usar string basicos con elementos de draw de qt

    painter.drawText(QRect(0,0, width(), altoStats), Qt::AlignCenter, strCBanderas) ;
    //pide un espacio donde dibujarlo, un rect o contenedor, tipo de alineacion, y el texto
    painter.drawText(bttSalir, Qt::AlignCenter, "Salir");


}

void tableroVisual::mousePressEvent(QMouseEvent *event){

    if(juegoTerminado) return;   // ← bloquea todo si ya terminó


    //---HACER QUE EL CLICK SE DETECTE DENTRO DEL BOTON---
    /*
     * -DATO DE CODIGO HASTA QUE ME INSTALE LINUX-
     *
     * ¿Sabias que el QRect no solo sirve como un contenedor que sirve para pintar rectangulos?
     * aparentemente, el qrect, si bien es cierto que forma un objeto de tipo rectangulo o parecido,
     * tambien puede utilizarse para definir ciertas acciones que ocurran dentro de su area cubierta.
     *
     * Este concepto es el que se utiliza para hacer que, al darle click el usuario al boton,
     * se ejecute una accion, como si fuera un boton de qwidgets
     *
     *
     *
     * */

    //mismos stats
    int altoStats= 100;
    int tamanioBttSalir = 60;
    int margenBttSalir=15;

    int bttX= width()- tamanioBttSalir - margenBttSalir;
    int bttY = (altoStats- tamanioBttSalir)/2;

    QRect bttSalir(bttX, bttY, tamanioBttSalir, tamanioBttSalir);

    //revisa si la posicion clickeada fue dentro del boton de salir
    if(bttSalir.contains(event->pos())){
        qDebug() <<"Se haria la accion de salir";

        /*
         * AQUI SE HARIA LA LOGICA DE QUIZA AGREGAR UN PANEL DE CONFIRMACION ANTES DE SALIR
         * Y LUEGO SE CIERRA LA PESTAÑA PARA VOLVER AL MENU
         *
         * NOTA PARA EDWIN: Creo que las ventanas de forms ocupan referencia del usuario.
         * Si es asi, deberias modificar los parametros de esta clase para que tambien contenga una
         * referencia del usuario actual, a manera de tener todo sincronizado.
         *
         *
         * */




        return;
    }



    //Para calcular las coords reales se tiene que sacar los parametros del paintEvent y restarlos
    //int altoStats= 100;
    int espaciadoVertical=50;
    int margenTablero=20;

    //VER SI SE LES PUEDE SACAR FORMULAS MATEMATICA A ESTAS MEDIDAS

    int anchoDisponible = width()-(margenTablero*2);
    int altoDisponible = height() -altoStats -espaciadoVertical - (margenTablero);

    int ladoTablero  = qMin(anchoDisponible, altoDisponible);


    /*
     * Si se analiza, todo estos calculos simplemente son para obtener los margenes en x y
     * ya que ahora estos dependen de las demas cosas que haya en pantalla
     *
     * */
    int margenX= (width()-ladoTablero)/2;
    int margenY=  altoStats +espaciadoVertical +(altoDisponible-ladoTablero)/2;
    int tCelda          = ladoTablero / medidaConst;






    QPoint pointClick;
    if(event->button()==Qt::LeftButton){
        pointClick= event->pos();
    }

    // ── Click derecho: alternar bandera ──
    if(event->button() == Qt::RightButton){
        pointClick = event->pos();
        Celda &celda = tLogico->obtenerCelda(
            ((pointClick.y()-margenY)/tCelda),
            ((pointClick.x()-margenX)/tCelda)
            );
        if(!celda.estaRevelada()){
            celda.alternarBandera();

            //vemos el estado en el que quedo despues de alternar bandera
            tLogico->alterarConteoBanderas(celda);
        }
        this->update();
        return;
    }


    //ahora el calculo de las filas y columnas se hace en base a los nuevos margenes de x y
    int fila= (pointClick.y() -margenY)/tCelda;
    int columna = (pointClick.x()-margenX)/tCelda;

    //posiblemente esto despues tire errores en los otros tableros
    if(fila>=0 && fila<8 && columna>= 0 && columna<8){
        qDebug() <<"Fila: "<<fila<<" Columna: "<<columna;
    }else{
        qDebug() <<"Estamos fuera de los limites bro";
        return; //hacemos un return para que no haga nada en caso de clickear afuera
    }




    tLogico->revelarCelda(fila, columna);

    // ── Derrota: pisó una mina ──
    if(tLogico->obtenerCelda(fila, columna).checkStatus()){
        juegoTerminado = true;
        // Revela todas las minas
        for(int f = 0; f < tLogico->getFilas(); f++){
            for(int c = 0; c < tLogico->getColumnas(); c++){
                if(tLogico->obtenerCelda(f,c).checkStatus())
                    tLogico->obtenerCelda(f,c).revelar();
            }
        }
        this->update();
        QMessageBox::critical(this, "💣 Derrota", "¡Pisaste una mina! Game Over.");
        return;
    }

    // ── Victoria: todas las celdas sin mina reveladas ──
    if(tLogico->verificarVictoria()){
        juegoTerminado = true;
        this->update();
        QMessageBox::information(this, "🏆 Victoria", "¡Ganaste! Despejaste el tablero.");
        return;
    }



    this->update();


}

void tableroVisual::setMedidaConst(int med){
    medidaConst=med;
}
