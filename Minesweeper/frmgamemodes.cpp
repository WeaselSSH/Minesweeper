#include "frmgamemodes.h"
#include "ui_frmgamemodes.h"

frmgamemodes::frmgamemodes(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::frmgamemodes)
{
    ui->setupUi(this);
}

frmgamemodes::~frmgamemodes()
{
    delete ui;
}
