#include "tableroVisual.h"

#include "manejousuario.h"
#include "frmseleccionnivel.h"
#include "frmmodehistoria.h"

#include <QMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include <QFontDatabase>
#include <QConicalGradient>

tableroVisual::tableroVisual(ManejoUsuario *manejoPtr, QWidget *parent) : QWidget(parent), mManejo(manejoPtr) {
    this->setFixedSize(1000,800);
    //this->inicializarFondo();


    tiempoTranscurrido = 0;
    cronometro = new QTimer(this);




    //cargado de imagenes
    pixmapBandera.load(":/icons/floorflagTile.png");
    pixmapMina.load(":/icons/mineTile.png");
    pixmapHiddenTile.load(":/icons/hiddenTile.png");


    //cargar fuente
    int id = QFontDatabase::addApplicationFont(":/icons/PressStart2P-Regular.ttf");
    if(id!=-1){
        QString nombreFamilia = QFontDatabase::applicationFontFamilies(id).at(0);
        this->fuentePersonalizada= QFont(nombreFamilia);

    }else{
        qDebug() <<"NO SE PUDO CARGAR LA FUENTE";
    }


    //controla para que, cada vez que pase un segundo, se incremente y actualice
    connect(cronometro, &QTimer::timeout, this, [this](){
        tiempoTranscurrido++;


        //cada segundo se va incrementando el angulo
        anguloRadar+=5.0f;
        if(anguloRadar>=360.0f) anguloRadar= 0.0f;


        update();
    });

    cronometro->start(1000);
}

//probablemente hacer algun metodo de destruccion de esto, para que no quede memory leak
void tableroVisual:: inicializarTLogico(int numFilas, int numColumnas, int numMinas){
    delete tLogico; //por ahora (igual es lo mejor creo)
    tLogico = new tableroLogico(numFilas, numColumnas, numMinas);
    tLogico->colocarMinas();
    tLogico->calcularMinasAdyacentes();

    tLogico->setBanderas(numMinas);


}

void tableroVisual::colocarMinas(){
    tLogico->colocarMinas();
}

void tableroVisual::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    if (!tLogico) return;



    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if(!pixmapFondo.isNull()){
        painter.drawPixmap(0,100,1000,700, pixmapFondo);
    }

   // QFont fuenteUI= this->fuentePersonalizada;
   // fuenteUI.setPointSize(18);
    //fuenteUI.setBold(true);

    //----PINTADO DE FONDO---
    //Parte de los stats
    int altoStats = 100;
    int espaciadoVertical =50;
    int margenTablero =20;







    QColor colorFondo("#050A05");
    QColor colorBordes("#33FF33");


    //painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#0A1A0A"));
    painter.setPen(QPen(QColor("#33FF33"),2));
    painter.drawRect(0, 0, width(), altoStats);

    // //fondo atras del tablero
    // painter.setBrush(QColor("#050A05"));
    // painter.drawRect(0, altoStats, width(), height()-altoStats);




    //calculo de espacio disponible despues de la parte de stats
    int anchoDisponible = width() - (margenTablero * 2);
    int altoDisponible = height() - altoStats - espaciadoVertical - margenTablero;

    //calculo de medidas basadas en dificultad seleccionada
    int tCeldaMaxAncho = anchoDisponible/tLogico->getColumnas();
    int tCeldaMaxAlto = altoDisponible/tLogico->getFilas();

    int tCelda = qMin(tCeldaMaxAncho, tCeldaMaxAlto);

    int anchoTotalTablero = tCelda*tLogico->getColumnas();
    int altoTotalTablero = tCelda *tLogico->getFilas();

    int margenX = (width() - anchoTotalTablero)/2;
    int margenY =  altoStats + espaciadoVertical +(altoDisponible-altoTotalTablero)/2;



    // Colores de números clásico buscaminas
    QColor coloresNum[] = {
        Qt::blue, Qt::darkGreen, Qt::red, Qt::darkBlue,
        Qt::darkRed, Qt::cyan, Qt::black, Qt::gray
    };

    QFont fuente("Courier New",12, QFont::Bold);
    fuente.setStyleStrategy(QFont::NoAntialias);
    //fuente.setBold(true);
    fuente.setPixelSize(tCelda * 0.45);
    painter.setFont(fuente);

    for (int fila = 0; fila < tLogico->getFilas(); fila++) {
        for (int columna = 0; columna < tLogico->getColumnas(); columna++) {
            Celda &celda = tLogico->obtenerCelda(fila, columna);
            int x = margenX + (columna * tCelda);
            int y = margenY+ (fila * tCelda);

            QRect rect(x, y, tCelda, tCelda);

            // ── Color de fondo ──
            if (!celda.estaRevelada()) {

                if (celda.tieneBandera()){




                    // painter.setBrush(QColor("#FFCC00"));
                    // painter.setPen(QPen(QColor("#1A331A"),2));
                    // painter.drawRect(rect);





                // amarillo = bandera
                }else{
                    painter.drawPixmap(rect, pixmapHiddenTile);
                    /*
                    painter.setBrush("#0A1A0A");  // verde = no revelada
                    painter.setPen(QPen(QColor("#1A331A"),2));
                    painter.drawRect(rect);
*/
                }

            } else if (celda.getTieneMina()) {
                // painter.setBrush(QColor("#FF3333"));       // rojo = mina
                // painter.setPen(QPen(QColor("#33FF33"),2));
                // painter.drawRect(rect);
            } else {
                // painter.setBrush(QColor("##152A15"));     // beige = revelada
                // painter.setPen(QPen(QColor("#33FF33"),2));
                // painter.drawRect(rect);
            }

            // Borde gris entre celdas
            // painter.setPen(QPen(QColor(80, 80, 80), 1));
            // painter.drawRect(rect);



            // ── Contenido ──
            if (!celda.estaRevelada() && celda.tieneBandera()) {
                /*painter.setPen(Qt::red);
                painter.drawText(rect, Qt::AlignCenter, "🚩"); */ // bandera

                //rect.adjusted(4,4,-4,-4)
                painter.drawPixmap(rect, pixmapBandera);

            } else if (celda.estaRevelada() && celda.getTieneMina()) {
                // painter.setPen(Qt::black);
                // painter.drawText(rect, Qt::AlignCenter, "💣");  // mina

                painter.drawPixmap(rect, pixmapMina);

            } else if (celda.estaRevelada()) {
                int minas = celda.getMinasAdyacentes();
                if (minas > 0) {
                    painter.setPen(coloresNum[minas - 1]);
                    painter.drawText(rect, Qt::AlignCenter, QString::number(minas));
                }
            }
        }
    }

    /*
    //elementos de radar
    //se define el centro y el radio en base a dimensiones de pantalla
    QPointF centro(width()/2.0, altoStats + (height()-altoStats)/2.0);
    int radioRadar = qMax(anchoTotalTablero, altoTotalTablero)/1.5;

    QConicalGradient radarGrad(centro, -anguloRadar);

    QColor colorHaz("#34a934");
    radarGrad.setColorAt(0.0, colorHaz);
    radarGrad.setColorAt(0.1, QColor(74,242,74,100));
    radarGrad.setColorAt(0.5, Qt::transparent);

    //simulacion de pintar luz
    painter.setCompositionMode(QPainter::CompositionMode_Plus);
    painter.setBrush(radarGrad);
    painter.setPen(Qt::NoPen);

    //dibujo del haz
    painter.drawEllipse(centro, radioRadar, radioRadar);

    //restaurar modo
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);

*/










    //DESARROLLO DE BOTON PARA ABANDONAR PARTIDA
    /*
     * PARA TODO ELEMENTO QUE QUERRAMOS PINTAR EN PANTALLA, EN UN ESPACIO QUE NO ESTE PEGADO A LOS MARGENES
     * SIEMPRE SE TENDRA QUE CALCULAR UN MARGEN X y Y
     *
     *
     * */

    int tamanioBttSalir = 60;
    int margenBttSalir = 15;

    int bttX = width() - tamanioBttSalir - margenBttSalir;
    int bttY = (altoStats - tamanioBttSalir) / 2;

    painter.setBrush(QColor("#1A331A"));
    painter.setPen(QPen(QColor("#33FF33"), 2));
    QRect bttSalir(bttX, bttY, tamanioBttSalir, tamanioBttSalir);
    painter.drawRoundedRect(bttSalir, 5, 5);

    //pintamos texto
    painter.setPen(QColor("#33FF33"));
    QFont font("Courier New", 12, QFont::Bold);
    font.setStyleStrategy(QFont::NoAntialias);
    //font.setBold(true);
    font.setPixelSize(18);
    painter.setFont(font);

    int countBanderas = tLogico->getNumBanderasPuestas();
    QString  strCBanderas = "🚩:" + QString::number(countBanderas);
    QString strTiempo ="⏰: " + formatTime();
    //no se pueden usar string basicos con elementos de draw de qt

    int centroX = width() / 2;
    int anchoCaja = 100;
    int separacion = 20;

    QRect rectBandera(centroX - anchoCaja - (separacion/2), 0, anchoCaja, altoStats);
    QRect rectCronometro(centroX + (separacion/2), 0, anchoCaja, altoStats);



    //painter.drawText(QRect(0,0, width(), altoStats), Qt::AlignCenter, strCBanderas) ;
    //pide un espacio donde dibujarlo, un rect o contenedor, tipo de alineacion, y el texto
    painter.drawText(rectBandera, Qt::AlignCenter, strCBanderas);
    painter.drawText(rectCronometro, Qt::AlignCenter, strTiempo);
    font.setPixelSize(15);
    painter.setFont(font);
    painter.setPen(QColor("#33FF33"));
    painter.drawText(bttSalir, Qt::AlignCenter, "Salir");






}

void tableroVisual::mousePressEvent(QMouseEvent *event){
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
    int altoStats = 100;
    int tamanioBttSalir = 60;
    int margenBttSalir =15;

    int bttX = width()- tamanioBttSalir - margenBttSalir;
    int bttY = (altoStats - tamanioBttSalir)/2;
    QRect bttSalir(bttX, bttY, tamanioBttSalir, tamanioBttSalir);

    if(bttSalir.contains(event->pos())){


        //salida especial si estamos en modo historia
        if(tLogico->getgameMode()=='h'){
            auto w = new frmmodehistoria(mManejo);
            w->setAttribute(Qt::WA_DeleteOnClose, true);
            w->show();
            window()->close();
            return;

        }


        auto w = new FrmSeleccionNivel(mManejo);
        w->setAttribute(Qt::WA_DeleteOnClose, true);
        w->show();
        window()->close();
        return;
    }

    if(juegoTerminado) return;   // ← bloquea todo si ya terminó //lo pongo aca para que se pueda salir del widget

    //Para calcular las coords reales se tiene que sacar los parametros del paintEvent y restarlos
    //int altoStats= 100;
    int espaciadoVertical = 50;
    int margenTablero = 20;

    //VER SI SE LES PUEDE SACAR FORMULAS MATEMATICA A ESTAS MEDIDAS

    int anchoDisponible = width()-(margenTablero*2);
    int altoDisponible = height() -altoStats -espaciadoVertical - (margenTablero);

    int tCeldaMaxAncho = anchoDisponible/tLogico->getColumnas();
    int tCeldaMaxAlto = altoDisponible/tLogico->getFilas();


    //nuevo tamanio de celda ajustado a medidas ideales
    int tCelda = qMin(tCeldaMaxAncho, tCeldaMaxAlto);

    int anchoTotalTablero = tCelda*tLogico->getColumnas();
    int altoTotalTablero = tCelda *tLogico->getFilas();



    //int ladoTablero  = qMin(anchoDisponible, altoDisponible);

    /*
     * Si se analiza, todo estos calculos simplemente son para obtener los margenes en x y
     * ya que ahora estos dependen de las demas cosas que haya en pantalla
     *
     * */
    int margenX = (width() - anchoTotalTablero)/2;
    int margenY =  altoStats + espaciadoVertical +(altoDisponible-altoTotalTablero)/2;
    //int tCelda = ladoTablero / medidaConst;

    QPoint pointClick;
    if(event->button()==Qt::LeftButton){
        pointClick = event->pos();
    }

    // ── Click derecho: alternar bandera ──
    if(event->button() == Qt::RightButton){
        pointClick = event->pos();
        Celda &celda = tLogico->obtenerCelda(
            ((pointClick.y() - margenY) / tCelda),
            ((pointClick.x() - margenX) / tCelda)
            );

        if(!celda.estaRevelada()){
            celda.alternarBandera();

            tLogico->alterarConteoBanderas(celda);
        }
        this->update();
        return;
    }


    int fila = (pointClick.y() - margenY)/tCelda;
    int columna = (pointClick.x() - margenX)/tCelda;


    if(fila >= 0 && fila < tLogico->getFilas() && columna >= 0 && columna < tLogico->getColumnas()){
        qDebug() << "Fila: " << fila << " Columna: " << columna;
    }else{
        qDebug() << "Estamos fuera de los limites bro";
        return;
    }

    tLogico->revelarCelda(fila, columna);

    // ── Derrota: pisó una mina ──
    if(tLogico->verificarDerrota(fila, columna)){
        juegoTerminado = true;

        // Revela todas las minas
        for(int f = 0; f < tLogico->getFilas(); f++){
            for(int c = 0; c < tLogico->getColumnas(); c++){
                if(tLogico->obtenerCelda(f,c).getTieneMina())
                    tLogico->obtenerCelda(f,c).revelar();
            }
        }

        cronometro->stop();
        //calculo de medida de tiempoobtenerTiempoPartida()
        int tiempoPartida = obtenerTiempoPartida();
        qDebug ()<<"Tiempo de partida: "<<tiempoPartida;


        this->update();
        QMessageBox::critical(this, "💣 Derrota", "¡Pisaste una mina! Game Over.");


        //salida especial si estamos en modo historia
        if(tLogico->getgameMode()=='h'){
            auto w = new frmmodehistoria(mManejo);
            w->setAttribute(Qt::WA_DeleteOnClose, true);
            w->show();
            window()->close();
            return;

        }




        auto w = new FrmSeleccionNivel(mManejo);
        w->setAttribute(Qt::WA_DeleteOnClose, true);
        w->show();
        window()->close();
        return;
    }

    // ── Victoria: todas las celdas sin mina reveladas ──
    if(tLogico->verificarVictoria()){
        juegoTerminado = true;
        cronometro->stop();

        //calculo de medida de tiempoobtenerTiempoPartida()
        int tiempoPartida = obtenerTiempoPartida();
        qDebug ()<<"Tiempo de partida: "<<tiempoPartida;

        Usuario& usuarioActual = mManejo->getUsuarioActual();

        if (tLogico->getFilas() == 8 && tLogico->getColumnas() == 8) {
            if (usuarioActual.getMejorFacil() == 0 || tiempoPartida < usuarioActual.getMejorFacil()) {
                usuarioActual.setMejorFacil(tiempoPartida);
            }

            if (tLogico->getgameMode() == 'h' && usuarioActual.getNivelMaximo() < 1) {
                usuarioActual.setNivelMaximo(1);
            }

        } else if (tLogico->getFilas() == 16 && tLogico->getColumnas() == 16) {
            if (usuarioActual.getMejorMedio() == 0 || tiempoPartida < usuarioActual.getMejorMedio()) {
                usuarioActual.setMejorMedio(tiempoPartida);
            }

            if (tLogico->getgameMode() == 'h' && usuarioActual.getNivelMaximo() < 2) {
                usuarioActual.setNivelMaximo(2);
            }

        } else if (tLogico->getFilas() == 16 && tLogico->getColumnas() == 30) {
            if (usuarioActual.getMejorDificil() == 0 || tiempoPartida < usuarioActual.getMejorDificil()) {
                usuarioActual.setMejorDificil(tiempoPartida);
            }

            if (tLogico->getgameMode() == 'h' && usuarioActual.getNivelMaximo() < 3) {
                usuarioActual.setNivelMaximo(3);
            }
        }

        mManejo->guardarDatos();
        this->update();
        QMessageBox::information(this, "🏆 Victoria", "¡Ganaste! Despejaste el tablero.");



        //salida especial si estamos en modo historia
        if(tLogico->getgameMode()=='h'){
            auto w = new frmmodehistoria(mManejo);
            w->setAttribute(Qt::WA_DeleteOnClose, true);
            w->show();
            window()->close();
            return;

        }



        auto w = new FrmSeleccionNivel(mManejo);
        w->setAttribute(Qt::WA_DeleteOnClose, true);
        w->show();
        window()->close();
        return;
    }

    this->update();
}



void tableroVisual::setMedidaConst(int med){
    medidaConst = med;
}

QString tableroVisual::formatTime() const{
    int minutos = tiempoTranscurrido / 60;
    int segundos = tiempoTranscurrido % 60;

    return QString("%1:%2").arg(minutos, 2, 10, QChar('0')).arg(segundos, 2, 10, QChar('0'));
}


int tableroVisual::obtenerTiempoPartida() const{
    int minutos = tiempoTranscurrido;

    return minutos;
}


void tableroVisual::setgameModeV(char gameMode){
    tLogico->setgameMode(gameMode);
}

void tableroVisual::inicializarFondo(){
    int minas = tLogico->getNumMinas();

    if(minas==40){
        pixmapFondo.load(":/icons/mediumMap.png");
    }else if(minas==99){
        pixmapFondo.load(":/icons/hardMap.png");
    }else{
        //cargado de mapa
        pixmapFondo.load(":/icons/easyMap.png");
    }

}
