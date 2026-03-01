#include "menuprincipal.h"
#include "ui_menuprincipal.h"
//#include "frminiciosesion.h"
#include "frmregistro.h"

#include <QApplication>
#include <QDialog>

MenuPrincipal::MenuPrincipal(ManejoUsuario* manejoPtr, QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MenuPrincipal), mManejo(manejoPtr)
{
    ui->setupUi(this);
}

MenuPrincipal::~MenuPrincipal()
{
    delete ui;
}

void MenuPrincipal::on_btnInicioSesion_clicked()
{
}


void MenuPrincipal::on_btnRegistrarse_clicked()
{
    FrmRegistro* frmRegistro = new FrmRegistro(mManejo);
    frmRegistro->show();
    this->close();
}


void MenuPrincipal::on_btnSalir_clicked()
{
    mManejo->guardarDatos();
    QApplication::quit();
}
