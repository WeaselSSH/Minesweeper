#ifndef FRMSELECCIONNIVEL_H
#define FRMSELECCIONNIVEL_H

#include <QWidget>

namespace Ui {
class FrmSeleccionNivel;
}

class FrmSeleccionNivel : public QWidget
{
    Q_OBJECT

public:
    explicit FrmSeleccionNivel(QWidget *parent = nullptr);
    ~FrmSeleccionNivel();

private:
    Ui::FrmSeleccionNivel *ui;
};

#endif // FRMSELECCIONNIVEL_H
