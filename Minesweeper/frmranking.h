#ifndef FRMRANKING_H
#define FRMRANKING_H

#include "manejousuario.h"
#include <QWidget>
#include <vector>

namespace Ui {
class FrmRanking;
}

class FrmRanking : public QWidget
{
    Q_OBJECT

public:
    explicit FrmRanking(ManejoUsuario* manejoPtr, QWidget *parent = nullptr);
    ~FrmRanking();

private slots:
    void on_rbFacil_clicked();

    void on_rbMedio_clicked();

    void on_rbDificil_clicked();

    void on_btnSalir_clicked();

private:
    Ui::FrmRanking *ui;
    ManejoUsuario* mManejo;

    void cargarRanking();
    void ordenarListaPorPuntaje(std::vector<Usuario> &listaRanking);
};

#endif // FRMRANKING_H
