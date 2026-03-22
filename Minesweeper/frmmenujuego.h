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

    void on_btnJugar_clicked();

    void on_btnVerPerfil_clicked();

    void on_btnRanking_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::FrmMenuJuego *ui;
    ManejoUsuario* mManejo;
};

#endif // FRMMENUJUEGO_H
