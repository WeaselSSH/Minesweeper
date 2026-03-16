#ifndef FRMPERFILUSUARIO_H
#define FRMPERFILUSUARIO_H

#include <QWidget>

namespace Ui {
class FrmPerfilUsuario;
}

class FrmPerfilUsuario : public QWidget
{
    Q_OBJECT

public:
    explicit FrmPerfilUsuario(QWidget *parent = nullptr);
    ~FrmPerfilUsuario();

private:
    Ui::FrmPerfilUsuario *ui;
};

#endif // FRMPERFILUSUARIO_H
