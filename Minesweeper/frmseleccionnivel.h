#ifndef FRMSELECCIONNIVEL_H
#define FRMSELECCIONNIVEL_H

#include <QWidget>
#include "manejousuario.h"

namespace Ui {
class FrmSeleccionNivel;
}

class FrmSeleccionNivel : public QWidget
{
    Q_OBJECT

public:
    explicit FrmSeleccionNivel(ManejoUsuario *manejoPtr, QWidget *parent = nullptr);
    ~FrmSeleccionNivel();

private:
    Ui::FrmSeleccionNivel *ui;
    ManejoUsuario* mManejo;
};

#endif // FRMSELECCIONNIVEL_H
