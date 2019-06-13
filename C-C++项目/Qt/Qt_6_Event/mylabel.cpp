#include "mylabel.h"
#include <QDebug>
#include <QMouseEvent>

MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
{
    //设置鼠标追踪
    this->setMouseTracking(true);
}

//鼠标进入
void MyLabel::enterEvent(QEvent *)
{
    qDebug() << "鼠标进入了";
}

//鼠标离开
void MyLabel::leaveEvent(QEvent *)
{
    qDebug() << "鼠标离开了";
}

void MyLabel::mousePressEvent(QMouseEvent *ev)
{
    //如果鼠标按下的是左键   然后提示内容
    //找按下的位置
//    if(ev->button() == Qt::LeftButton)
//    {
        QString str = QString("鼠标按下了！！！x = %1 y = %2 ").arg(ev->x()).arg(ev->y());
        qDebug() << str;
//    }
}

void MyLabel::mouseReleaseEvent(QMouseEvent *ev)
{
//    if(ev->button() == Qt::LeftButton)
//    {
        QString str = QString("鼠标释放了！！！x = %1 y = %2").arg(ev->x()).arg(ev->y());
        qDebug() << str;
//    }
}

void MyLabel::mouseMoveEvent(QMouseEvent *ev)
{
    //持续状态 需要buttons 用与操作符进行判断
//    if(ev->buttons() & Qt::LeftButton)
//    {
        QString str = QString("鼠标移动了！！！x = %1 y = %2").arg(ev->x()).arg(ev->y());
        qDebug() << str;
//    }
}

//事件分发 Event事件
bool MyLabel::event(QEvent *e)
{
    //通常不会做拦截， event只要分发事件就可以了
    if(e->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *ev = static_cast<QMouseEvent *>(e);
        QString str = QString("Event: 鼠标按下了！！！x = %1 y = %2 ").arg(ev->x()).arg(ev->y());
        qDebug() << str;

        return true;
    }
    //其他事件 让父亲做默认处理
    return QLabel::event(e);
}
