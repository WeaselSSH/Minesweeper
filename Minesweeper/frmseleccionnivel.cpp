#include "frmseleccionnivel.h"
#include "ui_frmseleccionnivel.h"
#include "manejousuario.h"
#include "tableroVisual.h"
#include <qboxlayout.h>

FrmSeleccionNivel::FrmSeleccionNivel(ManejoUsuario* manejoPtr, QWidget *parent)
    : QWidget(parent), ui(new Ui::FrmSeleccionNivel), mManejo(manejoPtr)
{
    ui->setupUi(this);
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
    ventana->resize(500,600);

    //organizando widget
    QVBoxLayout *layout = new QVBoxLayout(ventana);
    tableroVisual *miWidget= new tableroVisual ();

    miWidget->setMedidaConst(8);
    miWidget->inicializarTLogico(8,8,10);
    layout->addWidget(miWidget);

    ventana->show();
    this->close(); //se usa this para referenciar a la ventana actual
}


void FrmSeleccionNivel::on_btnNivel2_clicked()
{
    //se crea la ventana en el heap para que perdure despues de terminar la funcion de clickear
    QWidget *ventana = new QWidget();
    ventana->setAttribute(Qt::WA_DeleteOnClose); //para que se libere memoria al cerrarla
    ventana->setWindowTitle("Tablero Juego");
    ventana->resize(800,700);

    //organizando widget
    QVBoxLayout *layout = new QVBoxLayout(ventana);
    tableroVisual *miWidget= new tableroVisual ();

     miWidget->setMedidaConst(16);
    miWidget->inicializarTLogico(16,16,40);
    layout->addWidget(miWidget);

    ventana->show();
    this->close(); //se usa this para referenciar a la ventana actual
}


void FrmSeleccionNivel::on_btnNivel3_clicked()
{
    //se crea la ventana en el heap para que perdure despues de terminar la funcion de clickear
    QWidget *ventana = new QWidget();
    ventana->setAttribute(Qt::WA_DeleteOnClose); //para que se libere memoria al cerrarla
    ventana->setWindowTitle("Tablero Juego");
    ventana->resize(1000,800);

    //organizando widget
    QVBoxLayout *layout = new QVBoxLayout(ventana);
    tableroVisual *miWidget= new tableroVisual ();

     miWidget->setMedidaConst(30);
    miWidget->inicializarTLogico(16,30,99);
    layout->addWidget(miWidget);

    ventana->show();
    this->close(); //se usa this para referenciar a la ventana actual
}

