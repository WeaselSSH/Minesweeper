#include "frmranking.h"
#include "ui_frmranking.h"

#include "manejousuario.h"
#include "frmmenujuego.h"

#include <algorithm>
#include <vector>

using namespace std;

FrmRanking::FrmRanking(ManejoUsuario* manejoPtr, QWidget *parent): QWidget(parent), ui(new Ui::FrmRanking), mManejo(manejoPtr)
{
    ui->setupUi(this);
    ui->tblRanking->setColumnCount(3);
    ui->tblRanking->setHorizontalHeaderLabels({"ID", "NOMBRE", "PUNTUACION"});
    this->setFixedSize(1000,800);

    //INTENTO DE SOLUCIONAR EDICION DE TABLA
    ui->tblRanking->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // 2. Impedir que el usuario seleccione celdas individuales (selecciona la fila completa)
    ui->tblRanking->setSelectionBehavior(QAbstractItemView::SelectRows);

    // 3. no permitir seleccionar nada
    ui->tblRanking->setSelectionMode(QAbstractItemView::NoSelection);




    QPixmap fondo(":/icons/rankingFondo.png");

    // 2. Escalarla al tamaño actual de la ventana
    fondo = fondo.scaled(this->size(), Qt::IgnoreAspectRatio);

    // 3. Crear una paleta y asignarla
    QPalette palette;
    palette.setBrush(QPalette::Window, fondo);
    this->setPalette(palette);

    ui->rbFacil->setChecked(true);
    cargarRanking();
}

FrmRanking::~FrmRanking()
{
    delete ui;
}

void FrmRanking::cargarRanking() {
    if (!ui->rbFacil->isChecked() && !ui->rbMedio->isChecked() && !ui->rbDificil->isChecked()) {
        return;
    }

    vector<Usuario> listaOriginal = mManejo->getListaUsuarios();
    vector<Usuario> listaRanking;


    for (const Usuario& u : listaOriginal) {
        if (ui->rbFacil->isChecked() && u.getMejorFacil() > 0) {
            listaRanking.push_back(u);
        } else if (ui->rbMedio->isChecked() && u.getMejorMedio() > 0) {
            listaRanking.push_back(u);
        } else if (ui->rbDificil->isChecked() && u.getMejorDificil() > 0) {
            listaRanking.push_back(u);
        }
    }

    ui->tblRanking->clearContents();
    ui->tblRanking->setRowCount(listaRanking.size());

    ordenarListaPorPuntaje(listaRanking);

    for (int i = 0; i < listaRanking.size(); i++) {
        int puntaje = 0;

        if (ui->rbFacil->isChecked()) {
            puntaje = listaRanking[i].getMejorFacil();
        } else if (ui->rbMedio->isChecked()) {
            puntaje = listaRanking[i].getMejorMedio();
        } else if (ui->rbDificil->isChecked()) {
            puntaje = listaRanking[i].getMejorDificil();
        }

        ui->tblRanking->setItem(i, 0, new QTableWidgetItem(QString::number(listaRanking[i].getId())));
        ui->tblRanking->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(listaRanking[i].getNombreUsuario())));
        ui->tblRanking->setItem(i, 2, new QTableWidgetItem(QString::number(puntaje)));
    }

    ui->tblRanking->resizeColumnsToContents();
    ui->tblRanking->resizeRowsToContents();
}

void FrmRanking::ordenarListaPorPuntaje(std::vector<Usuario> &listaRanking) {
    if (ui->rbFacil->isChecked()) {
        sort(listaRanking.begin(), listaRanking.end(), [](const Usuario& a, const Usuario& b) {
            return a.getMejorFacil() < b.getMejorFacil();
        });
    } else if (ui->rbMedio->isChecked()) {
        sort(listaRanking.begin(), listaRanking.end(), [](const Usuario& a, const Usuario& b) {
            return a.getMejorMedio() < b.getMejorMedio();
        });
    } else if (ui->rbDificil->isChecked()) {
        sort(listaRanking.begin(), listaRanking.end(), [](const Usuario& a, const Usuario& b) {
            return a.getMejorDificil() < b.getMejorDificil();
        });
    } else {
        return;
    }
}

void FrmRanking::on_rbFacil_clicked()
{
    cargarRanking();
}


void FrmRanking::on_rbMedio_clicked()
{
    cargarRanking();
}


void FrmRanking::on_rbDificil_clicked()
{
    cargarRanking();
}

void FrmRanking::on_btnSalir_clicked()
{
    auto w = new FrmMenuJuego(mManejo);
    w->setAttribute(Qt::WA_DeleteOnClose, true);
    w->show();
    close();
}
