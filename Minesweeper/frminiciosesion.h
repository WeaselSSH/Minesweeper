#ifndef FRMINICIOSESION_H
#define FRMINICIOSESION_H

#include <QWidget>

namespace Ui {
class FrmInicioSesion;
}

class FrmInicioSesion : public QWidget
{
    Q_OBJECT

public:
    explicit FrmInicioSesion(QWidget *parent = nullptr);
    ~FrmInicioSesion();

private:
    Ui::FrmInicioSesion *ui;
};

#endif // FRMINICIOSESION_H
