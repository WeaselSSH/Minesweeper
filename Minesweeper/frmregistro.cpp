#include "frmregistro.h"
#include "ui_frmregistro.h"
#include "manejousuario.h"

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
        QMessageBox::warning(this, "Registro", "Error: uno de los campos se encuentra vacio.");
        return;
    }

    bool registroExitoso = mManejo->registrarse(nombre.toStdString(), contrasena.toStdString());

    if (!registroExitoso) {
        QMessageBox::warning(this, "Registro", "Error: nombre de usuario ya existente.");
        return;
    }

    mManejo->guardarDatos();

    QMessageBox::information(this, "Registro", "Cuenta creada exitosamente.");
}

