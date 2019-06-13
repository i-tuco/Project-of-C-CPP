#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent = 0);

    //捕获事件
    //鼠标进入
    void enterEvent(QEvent *);

    //鼠标离开
    void leaveEvent(QEvent *);

    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);

    //事件分发 Event事件
    bool event(QEvent *e);
};

#endif // MYLABEL_H
