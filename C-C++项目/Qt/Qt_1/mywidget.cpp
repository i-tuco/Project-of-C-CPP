#include "mywidget.h"
#include <QPushButton>
#include "mybutton.h"
#include <QDebug>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
{
    //添加按钮
    QPushButton *btn = new QPushButton;
//    btn->show();//show用顶层方式弹出，如果想在MyWidget窗口显示，就需要依赖MyWidget窗口

    //设置父亲
    btn->setParent(this);
    //设置文字
    btn->setText("按钮1");//将char *隐式类型转换为QString

    //创建按钮的第二种方式  chuang口会按照btn2大小进行显示
    QPushButton *btn2 = new QPushButton("按钮2", this);
    //重置窗口大小
    this->resize(600, 400);
    //移动第二个按钮
    btn2->move(100, 100);
    //重置按钮大小
    btn2->resize(50, 50);
    //重置窗口标题
    setWindowTitle("Qt的第一个窗口");
    //设置窗口固定大小，不可缩放
    setFixedSize(600, 400);


    //创建自己的按钮
    MyButton *myBtn = new MyButton;
    myBtn->setText("我的按钮");
    myBtn->move(200, 200);
    myBtn->setParent(this);

    //点击myBtn关闭窗口
    //connect 参数1 信号的发送者 参数2 发送的信号（信号的地址） 参数3 信号的接收者 参数4 处理槽函数
    connect(myBtn, &MyButton::clicked, this, &MyWidget::close);
}

MyWidget::~MyWidget()
{
    qDebug() << "MyWidget析构了";
}
