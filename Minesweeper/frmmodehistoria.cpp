#include "frmmodehistoria.h"
#include "ui_frmmodehistoria.h"
#include <qboxlayout.h>
#include "frmmenujuego.h"
#include "manejousuario.h"
#include "tableroVisual.h"
#include "frmseleccionjuego.h"
#include <qboxlayout.h>

frmmodehistoria::frmmodehistoria(ManejoUsuario *manejoPtr, QWidget *parent)
    : QDialog(parent), ui(new Ui::frmmodehistoria), mManejo(manejoPtr)
{
    ui->setupUi(this);
    this->setFixedSize(1000,800);

    QPixmap fondo(":/icons/nivelesFondo.png");


    fondo = fondo.scaled(this->size(), Qt::IgnoreAspectRatio);


    QPalette palette;
    palette.setBrush(QPalette::Window, fondo);
    this->setPalette(palette);



    //revisar niveles de jugador
    Usuario usuarioActual = mManejo->getListaUsuarios().at(mManejo->getIdxUsuarioActual());
    int nivelMaximo = usuarioActual.getNivelMaximo();

    //realizar acciones en base a esas verificaciones

    //el nivel 1 siempre se mantiene desbloqueado
    ui->btnNivel2->setEnabled(false);
    ui->btnNivel3->setEnabled(false);

    if(nivelMaximo >= 1){
        ui->btnNivel2->setEnabled(true);

    }
    if(nivelMaximo >= 2){
        ui->btnNivel3->setEnabled(true);
    }

}

frmmodehistoria::~frmmodehistoria()
{
    delete ui;
}

void frmmodehistoria::on_btnNivel1_clicked()
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

    //h representando MODO HISTORIA
    miWidget->setgameModeV('h');

    ventana->show();
    this->close(); //se usa this para referenciar a la ventana actual
}


void frmmodehistoria::on_btnNivel2_clicked()
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

    //h representando MODO HISTORIA
    miWidget->setgameModeV('h');


    ventana->show();
    this->close(); //se usa this para referenciar a la ventana actual
}


void frmmodehistoria::on_btnNivel3_clicked()
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

    //h representando MODO HISTORIA
    miWidget->setgameModeV('h');



    ventana->show();
    this->close(); //se usa this para referenciar a la ventana actual
}


void frmmodehistoria::on_btnRegresar_clicked()
{
    auto w = new FrmSeleccionJuego(mManejo);
    w->setAttribute(Qt::WA_DeleteOnClose, true);
    w->show();
    window()->close();
}

