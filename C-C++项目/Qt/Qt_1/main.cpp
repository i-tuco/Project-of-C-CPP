#include "mywidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); //应用程序对象，有且只有一个
    MyWidget w; //创建MyWidget对象w MyWidge基类QWidget
    w.show();   //弹出窗口 调用show()

    return a.exec();
}
