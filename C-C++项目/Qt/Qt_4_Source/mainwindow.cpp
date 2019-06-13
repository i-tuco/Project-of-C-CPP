#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //通过ui寻找控件
//    ui->actionNew->setIcon(QIcon("E:/imgs/icon-phone.png"));//本地文件
    //添加资源文件到 项目中
    //使用资源文件“:+前缀名+文件名”
    ui->actionNew->setIcon(QIcon(":/imgs/images/i1.png"));
    ui->actionOpen->setIcon(QIcon(":/imgs/images/i2.jpg"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
