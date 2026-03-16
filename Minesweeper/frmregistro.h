#ifndef FRMREGISTRO_H
#define FRMREGISTRO_H

#include "manejousuario.h"
#include <QWidget>

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

private:
    Ui::FrmRegistro *ui;
    ManejoUsuario* mManejo;
};

#endif // FRMREGISTRO_H
