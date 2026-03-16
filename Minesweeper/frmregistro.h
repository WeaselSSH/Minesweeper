#ifndef FRMREGISTRO_H
#define FRMREGISTRO_H

#include "manejousuario.h"
#include <QWidget>
#include <QAction>

namespace Ui {
class FrmRegistro;
}

class FrmRegistro : public QWidget
{
    Q_OBJECT

public:
    explicit FrmRegistro(ManejoUsuario* manejo, QWidget *parent = nullptr);
    ~FrmRegistro();

private slots:
    void on_btnSalir_clicked();
    void on_btnRegistrarse_clicked();
    void mostrarContrasena();

private:
    Ui::FrmRegistro *ui;
    ManejoUsuario* mManejo;
    QAction* mAccionMostrarContrasena = nullptr;
};

#endif // FRMREGISTRO_H
