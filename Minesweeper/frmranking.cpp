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
    switch (dificultad) {
    case facil:
        break;
    case medio:
        break;
    case dificil:
        break;
    }
}
