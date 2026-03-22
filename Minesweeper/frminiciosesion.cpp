#include "frminiciosesion.h"
#include "ui_frminiciosesion.h"
#include "menuprincipal.h"
#include "frmmenujuego.h"

#include <QString>
#include <QMessageBox>
#include <QAction>
#include <QLineEdit>
#include <QIcon>

FrmInicioSesion::FrmInicioSesion(ManejoUsuario* manejoPtr, QWidget *parent)
    : QWidget(parent), ui(new Ui::FrmInicioSesion), mManejo(manejoPtr)
{
    ui->setupUi(this);
    this->setFixedSize(1000,800);

    QPixmap fondo(":/icons/accesoFondo.png");


    fondo = fondo.scaled(this->size(), Qt::IgnoreAspectRatio);


    QPalette palette;
    palette.setBrush(QPalette::Window, fondo);
    this->setPalette(palette);


    ui->txtContrasena->setEchoMode(QLineEdit::Password);

    mAccionMostrarContrasena = ui->txtContrasena->addAction(QIcon(":/icons/ojo_cerrado.png"),QLineEdit::TrailingPosition);
    connect(mAccionMostrarContrasena, &QAction::triggered, this, &FrmInicioSesion::mostrarContrasena);
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

void FrmInicioSesion::mostrarContrasena()
{
    if (ui->txtContrasena->echoMode() == QLineEdit::Password) {
        ui->txtContrasena->setEchoMode(QLineEdit::Normal);
        mAccionMostrarContrasena->setIcon(QIcon(":/icons/ojo_abierto.png"));
    } else {
        ui->txtContrasena->setEchoMode(QLineEdit::Password);
        mAccionMostrarContrasena->setIcon(QIcon(":/icons/ojo_cerrado.png"));
    }
}
