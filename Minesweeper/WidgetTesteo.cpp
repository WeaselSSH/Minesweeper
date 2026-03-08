//ESTA CLASE SOLO ES PARA TESTEAR COSAS GRAFICAS Y PAINTEVENT
#include "WidgetTesteo.h"
#include <QPainter>
#include <QLinearGradient>

using namespace std;


WidgetTesteo::WidgetTesteo(QWidget *parent)
    :QWidget(parent),  m_nivel(0)
{
    m_timer= new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, [this](){
        m_nivel = (m_nivel+1)%101;
        update();//equivalente al repaint de java
    });
    m_timer->start(30);

}

void WidgetTesteo::setNivel(int nivel){
    if(m_nivel!=nivel){
        m_nivel= qBound(0, nivel, 100);
        update();
    }
}

void WidgetTesteo::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    //Definicion de areas
    QRect rectCuerpo(5,5, width()-25, height()-10 );
    QRect rectBorne(width()-15, height()/3,10, height()/3);

    //Dibujado de contorno
    int margen =4;
    double porcentaje =m_nivel/100.0;
    int anchoCarga = (rectCuerpo.width()-(margen*2)) * porcentaje;

    //Logica de color
    QColor colorCarga = (m_nivel<20) ? Qt::red : (m_nivel <60 ? Qt::yellow : Qt::green);

    //degradado visual
    QLinearGradient grad(0,rectCuerpo.top(), 0, rectCuerpo.bottom());
    grad.setColorAt(0, colorCarga.lighter(130));
    grad.setColorAt(1, colorCarga.darker(130));

    painter.setBrush(grad);
    painter.setPen(Qt::NoPen);
    painter.drawRect(rectCuerpo.x()+margen, rectCuerpo.y() +margen, anchoCarga, rectCuerpo.height() - (margen*2));


    //dibujado de texto
    painter.setPen(Qt::black);
    painter.drawText(rectCuerpo, Qt::AlignCenter, QString("%1%").arg(m_nivel));

}



