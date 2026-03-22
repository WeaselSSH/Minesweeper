#include "frmseleccionnivel.h"
#include "ui_frmseleccionnivel.h"
#include "frmmenujuego.h"
#include "manejousuario.h"
#include "tableroVisual.h"
#include "frmseleccionjuego.h"
#include <qboxlayout.h>

FrmSeleccionNivel::FrmSeleccionNivel(ManejoUsuario* manejoPtr, QWidget *parent)
    : QWidget(parent), ui(new Ui::FrmSeleccionNivel), mManejo(manejoPtr)
{
    ui->setupUi(this);
    QPixmap fondo(":/icons/nivelesFondo.png");

    // 2. Escalarla al tamaño actual de la ventana
    fondo = fondo.scaled(this->size(), Qt::IgnoreAspectRatio);

    // 3. Crear una paleta y asignarla
    QPalette palette;
    palette.setBrush(QPalette::Window, fondo);
    this->setPalette(palette);


    this->setFixedSize(1000,800);
}

FrmSeleccionNivel::~FrmSeleccionNivel()
{
    delete ui;
}

void FrmSeleccionNivel::on_btnNivel1_clicked()
{
    //se crea la ventana en el heap para que perdure despues de terminar la funcion de clickear
    QWidget *ventana = new QWidget();
    ventana->setAttribute(Qt::WA_DeleteOnClose); //para que se libere memoria al cerrarla
    ventana->setWindowTitle("Tablero Juego");
    ventana->setFixedSize(1000,800);

    //organizando widget
    QVBoxLayout *layout = new QVBoxLayout(ventana);
    tableroVisual *miWidget= new tableroVisual(mManejo);

    miWidget->setMedidaConst(8);
    miWidget->inicializarTLogico(8,8,10);
    miWidget->inicializarFondo();
    layout->addWidget(miWidget);

    //r representando PARTIDA RAPIDA
    miWidget->setgameModeV('r');


    ventana->show();
    this->close(); //se usa this para referenciar a la ventana actual
}


void FrmSeleccionNivel::on_btnNivel2_clicked()
{
    //se crea la ventana en el heap para que perdure despues de terminar la funcion de clickear
    QWidget *ventana = new QWidget();
    ventana->setAttribute(Qt::WA_DeleteOnClose); //para que se libere memoria al cerrarla
    ventana->setWindowTitle("Tablero Juego");
    ventana->setFixedSize(1000,800);

    //organizando widget
    QVBoxLayout *layout = new QVBoxLayout(ventana);
    tableroVisual *miWidget= new tableroVisual(mManejo);

    miWidget->setMedidaConst(16);
    miWidget->inicializarTLogico(16,16,40);
    miWidget->inicializarFondo();
    layout->addWidget(miWidget);


    //r representando PARTIDA RAPIDA
    miWidget->setgameModeV('r');

    ventana->show();
    this->close(); //se usa this para referenciar a la ventana actual
}


void FrmSeleccionNivel::on_btnNivel3_clicked()
{
    //se crea la ventana en el heap para que perdure despues de terminar la funcion de clickear
    QWidget *ventana = new QWidget();
    ventana->setAttribute(Qt::WA_DeleteOnClose); //para que se libere memoria al cerrarla
    ventana->setWindowTitle("Tablero Juego");
    ventana->setFixedSize(1000,800);

    //organizando widget
    QVBoxLayout *layout = new QVBoxLayout(ventana);
    tableroVisual *miWidget= new tableroVisual(mManejo);

    miWidget->setMedidaConst(30);
    miWidget->inicializarTLogico(16,30,99);
    miWidget->inicializarFondo();
    layout->addWidget(miWidget);

    //r representando PARTIDA RAPIDA
    miWidget->setgameModeV('r');

    ventana->show();
    this->close(); //se usa this para referenciar a la ventana actual
}


void FrmSeleccionNivel::on_btnRegresar_clicked()
{
    auto w = new FrmSeleccionJuego(mManejo);
    w->setAttribute(Qt::WA_DeleteOnClose, true);
    w->show();
    window()->close();
}

