#ifndef FRMMENUJUEGO_H
#define FRMMENUJUEGO_H

#include <QWidget>
#include "manejousuario.h"

namespace Ui {
class FrmMenuJuego;
}

class FrmMenuJuego : public QWidget
{
    Q_OBJECT

public:
    explicit FrmMenuJuego(ManejoUsuario* manejoPtr, QWidget *parent = nullptr);
    ~FrmMenuJuego();

private slots:
    void on_btnRegresar_clicked();

private:
    Ui::FrmMenuJuego *ui;
    ManejoUsuario* mManejo;
};

#endif // FRMMENUJUEGO_H
