#ifndef FRMREGISTRO_H
#define FRMREGISTRO_H

#include <QWidget>

namespace Ui {
class FrmRegistro;
}

class FrmRegistro : public QWidget
{
    Q_OBJECT

public:
    explicit FrmRegistro(QWidget *parent = nullptr);
    ~FrmRegistro();

private:
    Ui::FrmRegistro *ui;
};

#endif // FRMREGISTRO_H
