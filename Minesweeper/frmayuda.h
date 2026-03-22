#ifndef FRMAYUDA_H
#define FRMAYUDA_H

#include <QDialog>

namespace Ui {
class frmayuda;
}

class frmayuda : public QDialog
{
    Q_OBJECT

public:
    explicit frmayuda(QWidget *parent = nullptr);
    ~frmayuda();

private:
    Ui::frmayuda *ui;
};

#endif // FRMAYUDA_H
