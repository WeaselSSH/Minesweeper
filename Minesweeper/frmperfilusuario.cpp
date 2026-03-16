#include "frmperfilusuario.h"
#include "ui_frmperfilusuario.h"

FrmPerfilUsuario::FrmPerfilUsuario(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FrmPerfilUsuario)
{
    ui->setupUi(this);
}

FrmPerfilUsuario::~FrmPerfilUsuario()
{
    delete ui;
}
