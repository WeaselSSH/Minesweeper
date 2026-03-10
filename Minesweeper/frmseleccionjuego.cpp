#include "frmseleccionjuego.h"
#include "ui_frmseleccionjuego.h"
#include "manejousuario.h"
#include "menuprincipal.h"

FrmSeleccionJuego::FrmSeleccionJuego(ManejoUsuario *manejoPtr, QWidget *parent)
    : QWidget(parent), ui(new Ui::FrmSeleccionJuego), mManejo(manejoPtr)
{
    ui->setupUi(this);
}

FrmSeleccionJuego::~FrmSeleccionJuego()
{
    delete ui;
}

void FrmSeleccionJuego::on_btnSalir_clicked()
{
    auto w = new MenuPrincipal(mManejo);
    w->setAttribute(Qt::WA_DeleteOnClose, true);
    w->show();
    close();
}


void FrmSeleccionJuego::on_btnPartidaRapida_clicked()
{

}

