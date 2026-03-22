#include "frmcreditos.h"
#include "ui_frmcreditos.h"
#include "manejousuario.h"
#include "frmmenujuego.h"

frmcreditos::frmcreditos(ManejoUsuario *manejoPtr, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::frmcreditos), mManejo(manejoPtr)
{
    ui->setupUi(this);
    this->setFixedSize(1000,800);
    QPixmap fondo(":/icons/creditosFondo.png");

    // 2. Escalarla al tamaño actual de la ventana
    fondo = fondo.scaled(this->size(), Qt::IgnoreAspectRatio);

    // 3. Crear una paleta y asignarla
    QPalette palette;
    palette.setBrush(QPalette::Window, fondo);
    this->setPalette(palette);

}

frmcreditos::~frmcreditos()
{
    delete ui;
}

void frmcreditos::on_pushButton_clicked()
{
    auto w = new FrmMenuJuego(mManejo);
    w->setAttribute(Qt::WA_DeleteOnClose, true);
    w->show();
    window()->close();
}

