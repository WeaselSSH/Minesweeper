#include "frmranking.h"
#include "ui_frmranking.h"

FrmRanking::FrmRanking(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FrmRanking)
{
    ui->setupUi(this);
}

FrmRanking::~FrmRanking()
{
    delete ui;
}
