#ifndef FRMRANKING_H
#define FRMRANKING_H

#include <QWidget>

namespace Ui {
class FrmRanking;
}

class FrmRanking : public QWidget
{
    Q_OBJECT

public:
    explicit FrmRanking(QWidget *parent = nullptr);
    ~FrmRanking();

private:
    Ui::FrmRanking *ui;
};

#endif // FRMRANKING_H
