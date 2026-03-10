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


    miWidget->inicializarTLogico(8,8,5);
    layout->addWidget(miWidget);

    ventana->show();
    this->close(); //se usa this para referenciar a la ventana actual
}

