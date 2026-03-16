#include "frmregistro.h"
#include "ui_frmregistro.h"

#include "frmmenujuego.h"
#include "menuprincipal.h"

#include <QString>
#include <QMessageBox>

FrmRegistro::FrmRegistro(ManejoUsuario *manejoPtr, QWidget *parent)
    : QWidget(parent), ui(new Ui::FrmRegistro), mManejo(manejoPtr)
{
    ui->setupUi(this);
}

FrmRegistro::~FrmRegistro()
{
    delete ui;
}

void FrmRegistro::on_btnSalir_clicked()
{
    auto w = new MenuPrincipal(mManejo);
    w->setAttribute(Qt::WA_DeleteOnClose, true);
    w->show();
    close();
}

void FrmRegistro::on_btnRegistrarse_clicked()
{
    QString nombre = ui->txtUsuario->text().trimmed();
    QString contrasena = ui->txtContrasena->text();

    if (nombre.isEmpty() || contrasena.isEmpty()) {
        QMessageBox::warning(this, "Registro", "Error: debe completar todos los campos.");
        return;
    }

    bool registroExitoso = mManejo->registrarse(nombre.toStdString(), contrasena.toStdString());

    if (!registroExitoso) {
        QMessageBox::warning(this, "Registro", "Error: el nombre de usuario ya existe.");
        return;
    }

    QMessageBox::information(this, "Registro", "Cuenta creada exitosamente.");

    auto w = new FrmMenuJuego(mManejo);
    w->setAttribute(Qt::WA_DeleteOnClose, true);
    w->show();
    close();
}

