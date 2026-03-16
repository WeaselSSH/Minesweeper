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

//tengo que ver como arreglar esto
