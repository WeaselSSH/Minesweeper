//ESTA CLASE SOLO ES PARA TESTEAR COSAS GRAFICAS Y PAINTEVENT

#ifndef WIDGETTESTEO_H
#define WIDGETTESTEO_H

#include <QWidget>
#include <QTimer>

//herencia de QWidget
class WidgetTesteo: public QWidget{
    Q_OBJECT

public:
    explicit WidgetTesteo(QWidget *parent = nullptr);


    void setNivel(int nivel);
    int nivel() const{
        return m_nivel;
    }



protected:
    void paintEvent(QPaintEvent *event) override;

    QSize sizeHint() const override{return QSize(200,100);}

private:
    int m_nivel;
    QTimer *m_timer;

};


#endif // WIDGETTESTEO_H
