#ifndef FRMRANKING_H
#define FRMRANKING_H

#include "manejousuario.h"
#include <QWidget>

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
    ManejoUsuario mManejo;
};

#endif // FRMRANKING_H
