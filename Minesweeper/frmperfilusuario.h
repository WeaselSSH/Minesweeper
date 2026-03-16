#ifndef FRMPERFILUSUARIO_H
#define FRMPERFILUSUARIO_H

#include "manejousuario.h"
#include <QWidget>

namespace Ui {
class FrmPerfilUsuario;
}

class FrmPerfilUsuario : public QWidget
{
    Q_OBJECT

public:
    explicit FrmPerfilUsuario(ManejoUsuario* manejoPtr, QWidget *parent = nullptr);
    ~FrmPerfilUsuario();

private slots:
    void on_btnSalir_clicked();

private:
    ManejoUsuario* mManejo;
    Ui::FrmPerfilUsuario *ui;

    void cargarDatos();
};

#endif // FRMPERFILUSUARIO_H
