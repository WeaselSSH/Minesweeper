#include "frmperfilusuario.h"
#include "ui_frmperfilusuario.h"
#include "frmmenujuego.h"

FrmPerfilUsuario::FrmPerfilUsuario(ManejoUsuario* manejoPtr, QWidget *parent): QWidget(parent), ui(new Ui::FrmPerfilUsuario), mManejo(manejoPtr)
{
    ui->setupUi(this);
    cargarDatos();
}

FrmPerfilUsuario::~FrmPerfilUsuario()
{
    delete ui;
}

void FrmPerfilUsuario::on_btnSalir_clicked()
{
    auto w = new FrmMenuJuego(mManejo);
    w->setAttribute(Qt::WA_DeleteOnClose, true);
    w->show();
    close();
}

void FrmPerfilUsuario::cargarDatos(){
    Usuario usuarioActual = mManejo->getListaUsuarios().at(mManejo->getIdxUsuarioActual());

    ui->lblNombreUsuario->setText(QString::fromStdString(usuarioActual.getNombreUsuario()));
    ui->lblId->setText(QString::number(usuarioActual.getId()));

    if (usuarioActual.getNivelMaximo() > 0)
        ui->lblNivelMaximo->setText(QString::number(usuarioActual.getNivelMaximo()));

    if(usuarioActual.getMejorFacil() > 0)
        ui->lblFacil->setText(QString::number(usuarioActual.getMejorFacil()));

    if(usuarioActual.getMejorMedio() > 0)
        ui->lblIntermedio->setText(QString::number(usuarioActual.getMejorMedio()));

    if(usuarioActual.getMejorDificil() > 0)
        ui->lblDificil->setText(QString::number(usuarioActual.getMejorDificil()));
}
