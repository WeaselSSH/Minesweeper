#ifndef FRMINICIOSESION_H
#define FRMINICIOSESION_H

#include "manejousuario.h"
#include <QWidget>

namespace Ui {
class FrmInicioSesion;
}

class FrmInicioSesion : public QWidget
{
    Q_OBJECT

public:
    explicit FrmInicioSesion(ManejoUsuario* manejoPtr, QWidget *parent = nullptr);
    ~FrmInicioSesion();

private slots:
    void on_btnSalir_clicked();

    void on_btnIniciarSesion_clicked();

private:
    Ui::FrmInicioSesion *ui;
    ManejoUsuario* mManejo;
};

#endif // FRMINICIOSESION_H
