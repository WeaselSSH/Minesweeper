#include "frmcreditos.h"
#include "ui_frmcreditos.h"

frmcreditos::frmcreditos(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::frmcreditos)
{
    ui->setupUi(this);
}

frmcreditos::~frmcreditos()
{
    delete ui;
}
