#include "frmseleccionnivel.h"
#include "ui_frmseleccionnivel.h"

FrmSeleccionNivel::FrmSeleccionNivel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FrmSeleccionNivel)
{
    ui->setupUi(this);
}

FrmSeleccionNivel::~FrmSeleccionNivel()
{
    delete ui;
}
