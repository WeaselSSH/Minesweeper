#ifndef FRMMODEHISTORIA_H
#define FRMMODEHISTORIA_H

#include <QDialog>
#include "manejousuario.h"

namespace Ui {
class frmmodehistoria;
}

class frmmodehistoria : public QDialog
{
    Q_OBJECT

public:
    explicit frmmodehistoria(ManejoUsuario *manejoPtr, QWidget *parent = nullptr);
    ~frmmodehistoria();

private slots:
    void on_btnNivel1_clicked();

    void on_btnNivel2_clicked();

    void on_btnNivel3_clicked();

    void on_btnRegresar_clicked();

private:
    Ui::frmmodehistoria *ui;
    ManejoUsuario* mManejo;
};

#endif // FRMMODEHISTORIA_H
