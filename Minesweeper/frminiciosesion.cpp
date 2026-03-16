#include "frminiciosesion.h"
#include "ui_frminiciosesion.h"
#include "menuprincipal.h"
#include "frmmenujuego.h"

#include <QString>
#include <QMessageBox>

FrmInicioSesion::FrmInicioSesion(ManejoUsuario* manejoPtr, QWidget *parent)
    : QWidget(parent), ui(new Ui::FrmInicioSesion), mManejo(manejoPtr)
{
    ui->setupUi(this);
}

FrmInicioSesion::~FrmInicioSesion()
{
    delete ui;
}

void FrmInicioSesion::on_btnSalir_clicked()
{
    auto w = new MenuPrincipal(mManejo);
    w->setAttribute(Qt::WA_DeleteOnClose, true);
    w->show();
    close();
}


void FrmInicioSesion::on_btnIniciarSesion_clicked()
{
    QString nombre = ui->txtUsuario->text().trimmed();
    QString contrasena = ui->txtContrasena->text();

    if (nombre.isEmpty() || contrasena.isEmpty()) {
        QMessageBox::warning(this, "Inicio de sesion", "Error: debe completar todos los campos.");
        return;
    }

    bool inicioExitoso = mManejo->iniciarSesion(nombre.toStdString(), contrasena.toStdString());

    if (!inicioExitoso) {
        QMessageBox::warning(this, "Inicio de sesion", "Error: nombre de usuario o contrasena no coinciden.");
        return;
    }

    QMessageBox::information(this, "Inicio de Sesion", "Inicio de sesion exitoso.");

    auto w = new FrmMenuJuego(mManejo);
    w->setAttribute(Qt::WA_DeleteOnClose, true);
    w->show();
    close();
}
