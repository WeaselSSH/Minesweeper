#ifndef FRMGAMEMODES_H
#define FRMGAMEMODES_H

#include <QDialog>

namespace Ui {
class frmgamemodes;
}

class frmgamemodes : public QDialog
{
    Q_OBJECT

public:
    explicit frmgamemodes(QWidget *parent = nullptr);
    ~frmgamemodes();

private:
    Ui::frmgamemodes *ui;
};

#endif // FRMGAMEMODES_H
