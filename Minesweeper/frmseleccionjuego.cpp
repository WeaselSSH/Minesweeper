#include "frmseleccionjuego.h"
#include "ui_frmseleccionjuego.h"
#include "manejousuario.h"
#include "menuprincipal.h"
#include "frmseleccionnivel.h"
#include "frmmenujuego.h"
#include "frmmodehistoria.h"

FrmSeleccionJuego::FrmSeleccionJuego(ManejoUsuario *manejoPtr, QWidget *parent)
    : QWidget(parent), ui(new Ui::FrmSeleccionJuego), mManejo(manejoPtr)
{
    ui->setupUi(this);
    this->setFixedSize(1000,800);
    QPixmap fondo(":/icons/menu2Fondo.png");

    // 2. Escalarla al tamaño actual de la ventana
    fondo = fondo.scaled(this->size(), Qt::IgnoreAspectRatio);

    // 3. Crear una paleta y asignarla
    QPalette palette;
    palette.setBrush(QPalette::Window, fondo);
    this->setPalette(palette);
}

FrmSeleccionJuego::~FrmSeleccionJuego()
{
    delete ui;
}

void FrmSeleccionJuego::on_btnPartidaRapida_clicked()
{
    auto w = new FrmSeleccionNivel(mManejo);
    w->setAttribute(Qt::WA_DeleteOnClose, true);
    w->show();
    close();
}

void FrmSeleccionJuego::on_btnRegresar_clicked()
{
    auto w = new FrmMenuJuego(mManejo);
    w->setAttribute(Qt::WA_DeleteOnClose, true);
    w->show();
    close();
}


void FrmSeleccionJuego::on_btnModoHistoria_clicked()
{
    auto w = new frmmodehistoria(mManejo);
    w->setAttribute(Qt::WA_DeleteOnClose, true);
    w->show();
    close();
}

