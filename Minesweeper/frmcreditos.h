#ifndef FRMCREDITOS_H
#define FRMCREDITOS_H

#include <QDialog>
#include "manejousuario.h"

namespace Ui {
class frmcreditos;
}

class frmcreditos : public QDialog
{
    Q_OBJECT

public:
    explicit frmcreditos(ManejoUsuario *manejoPtr, QWidget *parent = nullptr);
    ~frmcreditos();

private slots:
    void on_pushButton_clicked();

private:
    Ui::frmcreditos *ui;
    ManejoUsuario* mManejo;
};

#endif // FRMCREDITOS_H
