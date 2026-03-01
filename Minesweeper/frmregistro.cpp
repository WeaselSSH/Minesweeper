#include "frmregistro.h"
#include "ui_frmregistro.h"

FrmRegistro::FrmRegistro(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FrmRegistro)
{
    ui->setupUi(this);
}

FrmRegistro::~FrmRegistro()
{
    delete ui;
}
