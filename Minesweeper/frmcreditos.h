#ifndef FRMCREDITOS_H
#define FRMCREDITOS_H

#include <QDialog>

namespace Ui {
class frmcreditos;
}

class frmcreditos : public QDialog
{
    Q_OBJECT

public:
    explicit frmcreditos(QWidget *parent = nullptr);
    ~frmcreditos();

private:
    Ui::frmcreditos *ui;
};

#endif // FRMCREDITOS_H
