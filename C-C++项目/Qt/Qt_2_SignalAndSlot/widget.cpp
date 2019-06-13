#include "widget.h"
#include <QPushButton>
#include <QDebug>

//需求：创建两个类 Teacher类  Student类
//下课后 老师发出信号 饿了，学生响应信号

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    zt = new Teacher(this);
    st = new Student(this);

    //连接老师和学生
    //connect(zt, &Teacher::hungry, st, &Student::treat);//无参

    //有参数 信号和槽连接
    //函数指针 执行函数地址
    void(Teacher:: *teacherSignal)(QString) = &Teacher::hungry;
    void(Student:: *stSlot)(QString) = &Student::treat;
    connect(zt, teacherSignal, st, stSlot);//有参

    //下课了
    //classIsOver();

    //点击按钮才下课
    QPushButton * btn = new QPushButton("下课",this);
    //触发无参 信号和槽
    //1-信号连接 信号
    void(Teacher:: *noTeacherSignal)(void) = &Teacher::hungry;
    void(Student:: *noStSlot)(void) = &Student::treat;
    connect(btn, &QPushButton::clicked, zt, noTeacherSignal);
    connect(zt, noTeacherSignal, st, noStSlot);

    //2-断开信号和槽
    //disconnect(zt, noTeacherSignal, st, noStSlot);

    //3-一个信号可以触发多个槽函数
    //connect(btn, &QPushButton::clicked, this, &Widget::close);

    //4-多个信号可以连接同一个槽函数

    //5-信号和槽的参数必须一一对应
    //信号的参数个数可以多于槽函数的参数个数，反之不可以，但是必须类型一一对应

    //重置大小
    resize(600, 400);

    //lambda表达式
//    QPushButton * btn2 = new QPushButton("aaaa",this);
//    [=](){
//        btn2->setText("bbbb");
//    }();

//    //mutable 关键字 用于修改值传递的 变量 进行修改
//    QPushButton * myBtn = new QPushButton(this);
//    QPushButton * myBtn2 = new QPushButton(this);
//    myBtn2->move(100, 100);
//    myBtn2->setText("myBtn2");
//    int m =10;
//    connect(myBtn, &QPushButton::clicked, this, [m] () mutable { m = 100 + 10; qDebug() << m; });
//    connect(myBtn2, &QPushButton::clicked, this, [=] () { qDebug() << m; });
//    qDebug() << m;

//    //返回值
//    int ret = []()->int{
//        return 10000;
//    }();
//    qDebug() << "ret = " <<ret;
}
Widget::~Widget()
{

}

void Widget::classIsOver()
{
    //触发老师饿了的信号
    //老师饿了的信号属于自定义信号，触发自定义信号关键字 emit
    emit zt->hungry();
    emit zt->hungry("炒粉");
}
