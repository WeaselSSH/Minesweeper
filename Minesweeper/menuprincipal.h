#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include "manejousuario.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MenuPrincipal;
}
QT_END_NAMESPACE

class MenuPrincipal : public QMainWindow
{
    Q_OBJECT

public:
    explicit MenuPrincipal(ManejoUsuario* manejo, QWidget* parent = nullptr);
    ~MenuPrincipal();

private slots:
    void on_btnInicioSesion_clicked();
    void on_btnRegistrarse_clicked();
    void on_btnSalir_clicked();

private:
    Ui::MenuPrincipal *ui;
    ManejoUsuario* mManejo;
};
#endif // MENUPRINCIPAL_H
