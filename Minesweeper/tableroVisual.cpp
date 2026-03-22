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
    pixmapAliveCam.load(":/icons/aliveCam.png");
    pixmapDeadCam.load(":/icons/deadCam.png");

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

}


void tableroVisual:: inicializarTLogico(int numFilas, int numColumnas, int numMinas){
    delete tLogico;
    tLogico = new tableroLogico(numFilas, numColumnas, numMinas);
    tLogico->colocarMinas();
    tLogico->calcularMinasAdyacentes();

    tLogico->setBanderas(numMinas);

    tiempoTranscurrido = 0;
    partidaIniciada = false;
    juegoTerminado = false;
    partidaPerdida = false;
    cronometro->stop();
    update();
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

    //----PINTADO DE FONDO---
    //Parte de los stats
    int altoStats = 100;
    int espaciadoVertical =50;
    int margenTablero =20;


    int tercioAncho= width()/3;




    QColor colorFondo("#050A05");
    QColor colorBordes("#33FF33");


    painter.setBrush(QColor("#112F12"));
    painter.setPen(QPen(QColor("#33FF33"),2));
    painter.drawRect(0, 0, width(), altoStats);




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
        Qt::darkRed, Qt::cyan, Qt::magenta, Qt::gray
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
                    //nada aqui
                }else{
                    painter.drawPixmap(rect, pixmapHiddenTile);
                }

            } else if (celda.getTieneMina()) {
                //nada aqui
            } else {
                painter.setBrush(Qt::NoBrush);
                painter.setPen(QPen(QColor("#E6C98A"),2));
                painter.drawRect(rect);
            }


            // ── Contenido ──
            if (!celda.estaRevelada() && celda.tieneBandera()) {

                painter.drawPixmap(rect, pixmapBandera);

            } else if (celda.estaRevelada() && celda.getTieneMina()) {

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
    int separacion = 250;
    int sizeLogo= 95;

    QPixmap logoAMostrar;

    if(!partidaPerdida){
        logoAMostrar=pixmapAliveCam;

    }else{
        logoAMostrar=pixmapDeadCam;

    }

    QRect rectLogo(centroX-(sizeLogo/2), (altoStats-sizeLogo)/2, sizeLogo, sizeLogo);


    QRect rectBandera(centroX - anchoCaja - (separacion/2), 0, anchoCaja, altoStats);
    QRect rectCronometro(centroX + (separacion/2), 0, anchoCaja, altoStats);




    painter.drawText(rectBandera, Qt::AlignCenter, strCBanderas);
    painter.drawText(rectCronometro, Qt::AlignCenter, strTiempo);
    font.setPixelSize(15);
    painter.setFont(font);
    painter.setPen(QColor("#33FF33"));
    painter.drawText(bttSalir, Qt::AlignCenter, "Salir");


    if(!logoAMostrar.isNull()){
        // Escalamos el logo para que quepa en el cuadrado sin deformarse
        QPixmap logoEscalado = logoAMostrar.scaled(rectLogo.size(),
                                                   Qt::KeepAspectRatio
                                                   );

        // Calculamos la posición interna para que esté centrado si no es cuadrado
        int xOff = rectLogo.x() + (rectLogo.width() - logoEscalado.width()) / 2;
        int yOff = rectLogo.y() + (rectLogo.height() - logoEscalado.height()) / 2;

        painter.drawPixmap(xOff, yOff, logoEscalado);
    }






}

void tableroVisual::mousePressEvent(QMouseEvent *event){
    //---HACER QUE EL CLICK SE DETECTE DENTRO DEL BOTON---
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


    int anchoDisponible = width()-(margenTablero*2);
    int altoDisponible = height() -altoStats -espaciadoVertical - (margenTablero);

    int tCeldaMaxAncho = anchoDisponible/tLogico->getColumnas();
    int tCeldaMaxAlto = altoDisponible/tLogico->getFilas();


    //nuevo tamanio de celda ajustado a medidas ideales
    int tCelda = qMin(tCeldaMaxAncho, tCeldaMaxAlto);

    int anchoTotalTablero = tCelda*tLogico->getColumnas();
    int altoTotalTablero = tCelda *tLogico->getFilas();

    /*
     * Si se analiza, todo estos calculos simplemente son para obtener los margenes en x y
     * ya que ahora estos dependen de las demas cosas que haya en pantalla
     *
     * */
    int margenX = (width() - anchoTotalTablero)/2;
    int margenY =  altoStats + espaciadoVertical +(altoDisponible-altoTotalTablero)/2;


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

    if (event->button() == Qt::LeftButton && !partidaIniciada) {
        partidaIniciada = true;
        cronometro->start(1000);
    }

    tLogico->revelarCelda(fila, columna);

    // ── Derrota: pisó una mina ──
    if(tLogico->verificarDerrota(fila, columna)){
        juegoTerminado = true;
        this->partidaPerdida=true;
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
