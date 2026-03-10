#include "frmseleccionnivel.h"
#include "ui_frmseleccionnivel.h"
#include "manejousuario.h"

FrmSeleccionNivel::FrmSeleccionNivel(ManejoUsuario* manejoPtr, QWidget *parent)
    : QWidget(parent), ui(new Ui::FrmSeleccionNivel), mManejo(manejoPtr)
{
    ui->setupUi(this);
}

FrmSeleccionNivel::~FrmSeleccionNivel()
{
    delete ui;
}
