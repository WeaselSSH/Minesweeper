#include "frmmenujuego.h"
#include "ui_frmmenujuego.h"

#include "manejousuario.h"
#include "menuprincipal.h"
#include "frmranking.h"
#include "frmperfilusuario.h"
#include "frmseleccionjuego.h"
#include "frmcreditos.h"


//cositas para abrir panel de guardar archivo de ayuda
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QStandardPaths>


#include <QVBoxLayout>


FrmMenuJuego::FrmMenuJuego(ManejoUsuario* manejoPtr, QWidget *parent)
    : QWidget(parent), ui(new Ui::FrmMenuJuego), mManejo(manejoPtr)
{
    ui->setupUi(this);
    this->setFixedSize(1000,800);

    QPixmap fondo(":/icons/menu2Fondo.png");

    // 2. Escalarla al tamaño actual de la ventana
    fondo = fondo.scaled(this->size(), Qt::IgnoreAspectRatio);

    // 3. Crear una paleta y asignarla
    QPalette palette;
    palette.setBrush(QPalette::Window, fondo);
    this->setPalette(palette);



}

FrmMenuJuego::~FrmMenuJuego()
{
    delete ui;
}

void FrmMenuJuego::on_btnRegresar_clicked()
{
    auto w = new MenuPrincipal(mManejo);
    w->setAttribute(Qt::WA_DeleteOnClose, true);
    w->show();
    close();
}

void FrmMenuJuego::on_btnJugar_clicked()
{
    auto w = new FrmSeleccionJuego(mManejo);
    w->setAttribute(Qt::WA_DeleteOnClose, true);
    w->show();
    close();
}


void FrmMenuJuego::on_btnVerPerfil_clicked()
{
    auto w = new FrmPerfilUsuario(mManejo);
    w->setAttribute(Qt::WA_DeleteOnClose, true);
    w->show();
    close();
}


void FrmMenuJuego::on_btnRanking_clicked()
{
    auto w = new FrmRanking(mManejo);
    w->setAttribute(Qt::WA_DeleteOnClose, true);
    w->show();
    close();
}

void FrmMenuJuego::on_pushButton_2_clicked()
{
    auto w = new frmcreditos(mManejo);
    w->setAttribute(Qt::WA_DeleteOnClose, true);
    w->show();
    close();
}

//configuracion para que el boton de ayuda pueda descargar un archivo
void FrmMenuJuego::on_pushButton_clicked()
{
    QString rutaRecurso= ":/icons/manual_usuario.pdf";
    QString rutaSugerida = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+ "/manual_usuario.pdf";

    QString rutaDestino =  QFileDialog::getSaveFileName(this,
                                                       "Guardar Manual de Usuario",
                                                       rutaSugerida,
                                                       "Archivos PDF (*.pdf)");

    //caso que el usuario haya cancelado
    if(!rutaDestino.isEmpty()){

        if(QFile::exists(rutaDestino)){
            QFile::remove(rutaDestino);
        }

        if(QFile::copy(rutaRecurso, rutaDestino)){
            QFile::setPermissions(rutaDestino, QFile::WriteOwner | QFile::ReadOwner);

            QMessageBox::information(this, "Mision Completada",
                                     "El manual ha sido guardado a tu equipo con éxito.");
        }else{
            QMessageBox::critical(this, "Error de Sistema", "No se pudo copiar el archivo. Verifique los permisos.");
        }

    }

}

