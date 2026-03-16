#include "frmranking.h"
#include "ui_frmranking.h"

#include "manejousuario.h"

FrmRanking::FrmRanking(ManejoUsuario* manejoPtr, QWidget *parent): QWidget(parent), ui(new Ui::FrmRanking), mManejo(manejoPtr)
{
    ui->setupUi(this);
}

FrmRanking::~FrmRanking()
{
    delete ui;
}

void FrmRanking::cargarRanking(Dificultad dificultad) {
    switch (categoria) {
    case 1:

        break;
    case 2:
        break;
    case 3:
        break;
    }
}
