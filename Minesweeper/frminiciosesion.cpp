#include "frminiciosesion.h"
#include "ui_frminiciosesion.h"

FrmInicioSesion::FrmInicioSesion(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FrmInicioSesion)
{
    ui->setupUi(this);
}

FrmInicioSesion::~FrmInicioSesion()
{
    delete ui;
}
