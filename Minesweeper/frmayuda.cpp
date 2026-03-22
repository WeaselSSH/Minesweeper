#include "frmayuda.h"
#include "ui_frmayuda.h"

frmayuda::frmayuda(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::frmayuda)
{
    ui->setupUi(this);
}

frmayuda::~frmayuda()
{
    delete ui;
}
