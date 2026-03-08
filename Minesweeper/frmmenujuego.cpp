#include "frmmenujuego.h"
#include "ui_frmmenujuego.h"
#include "manejousuario.h"
#include "menuprincipal.h"
#include "tableroVisual.h"
#include <QVBoxLayout>


FrmMenuJuego::FrmMenuJuego(ManejoUsuario* manejoPtr, QWidget *parent)
    : QWidget(parent), ui(new Ui::FrmMenuJuego), mManejo(manejoPtr)
{
    ui->setupUi(this);
}

FrmMenuJuego::~FrmMenuJuego()
{
    delete ui;
}

void FrmMenuJuego::on_btnRegresar_clicked()
{
    auto w = new MenuPrincipal(mManejo);
    w->setAttribute(Qt::WA_DeleteOnClose, true);
    w->show();
    close();
}

void FrmMenuJuego::on_btnJugar_clicked()
{






    //se crea la ventana en el heap para que perdure despues de terminar la funcion de clickear
    QWidget *ventana = new QWidget();
    ventana->setAttribute(Qt::WA_DeleteOnClose); //para que se libere memoria al cerrarla
    ventana->setWindowTitle("Tablero Juego");
    ventana->resize(500,600);

    //organizando widget
    QVBoxLayout *layout = new QVBoxLayout(ventana);
    tableroVisual *miWidget= new tableroVisual ();

    //linkeamos tablero visual con tablero logico
    miWidget->inicializarTLogico();

    layout->addWidget(miWidget);

    ventana->show();
    this->close(); //se usa this para referenciar a la ventana actual
}

