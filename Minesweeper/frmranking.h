#ifndef FRMRANKING_H
#define FRMRANKING_H

#include "manejousuario.h"
#include <QWidget>

enum Dificultad {
    facil,
    medio,
    dificil
};

namespace Ui {
class FrmRanking;
}

class FrmRanking : public QWidget
{
    Q_OBJECT

public:
    explicit FrmRanking(ManejoUsuario* manejoPtr, QWidget *parent = nullptr);
    ~FrmRanking();

private:
    Ui::FrmRanking *ui;
    ManejoUsuario* mManejo;

    void cargarRanking(Dificultad dificultad); //1 = facil, 2 = medio, 3 = dificil
};

#endif // FRMRANKING_H
