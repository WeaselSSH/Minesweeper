#ifndef FRMINICIOSESION_H
#define FRMINICIOSESION_H

#include "manejousuario.h"
#include <QWidget>
#include <QAction>

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
    void mostrarContrasena();

private:
    Ui::FrmInicioSesion *ui;
    ManejoUsuario* mManejo;
    QAction* mAccionMostrarContrasena = nullptr;
};

#endif // FRMINICIOSESION_H
