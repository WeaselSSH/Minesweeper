#ifndef FRMSELECCIONJUEGO_H
#define FRMSELECCIONJUEGO_H

#include <QWidget>
#include "manejousuario.h"

namespace Ui {
class FrmSeleccionJuego;
}

class FrmSeleccionJuego : public QWidget
{
    Q_OBJECT

public:
    explicit FrmSeleccionJuego(ManejoUsuario *manejoPtr, QWidget *parent = nullptr);
    ~FrmSeleccionJuego();

private slots:
    void on_btnSalir_clicked();

    void on_btnPartidaRapida_clicked();

private:
    Ui::FrmSeleccionJuego *ui;
    ManejoUsuario* mManejo;
};

#endif // FRMSELECCIONJUEGO_H
