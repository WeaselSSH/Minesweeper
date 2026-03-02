#include "frmmenujuego.h"
#include "ui_frmmenujuego.h"
#include "manejousuario.h"
#include "menuprincipal.h"

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
