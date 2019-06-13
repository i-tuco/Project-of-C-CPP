#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDialog>
#include <QMessageBox>
#include <QColorDialog>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //点击新建菜单项 弹出对话框
    connect(ui->actionNew, &QAction::triggered, this, [=](){
        //对话框有两种
        //模态对话框（不能对其他窗口进行操作）  非模态对话框（能对其他窗口进行操作）
        //-----模态-----
        //QDialog dlg;
        //dlg.resize(200, 100);
        //dlg.exec();//阻塞

        //-----非模态-----
        //QDialog dlg2;//创建到栈上，一闪而过
        //QDialog * dlg2 = new QDialog(this);
        //dlg2->resize(200, 100);
        //dlg2->show();
            //需要设置属性
        //dlg2->setAttribute(Qt::WA_DeleteOnClose);

        //=======================使用标准对话框 QMessageBox=========================
        //-----错误对话框-----
        //QMessageBox::critical(this, "错误！", "critical");

        //-----信息对话框-----
        //QMessageBox::information(this, "信息", "info");

        //-----询问对话框-----
        //参数1：父亲  参数2：标题 参数3：提示内容 参数4：按键类型 参数5：关联回车按键
        //QMessageBox::question(this, "问题", "question", QMessageBox::Save | QMessageBox::Cancel, QMessageBox::Cancel);
        //if(QMessageBox::Save == QMessageBox::question(this, "问题", "question", QMessageBox::Save | QMessageBox::Cancel, QMessageBox::Cancel))
        //{
        //    qDebug() << "点击的是保存";
        //}
        //else{
        //    qDebug() << "点击的是取消";
        //}

        //-----警告对话框-----
        //QMessageBox::warning(this, "警告", "warning");


        //=========================选择颜色对话框================================
        //QColor color = QColorDialog::getColor(QColor(255,0,0));
        //qDebug() << color.red() <<color.green() << color.blue();


        //=========================选择文件对话框================================
        QString path = QFileDialog::getOpenFileName(this, "打开文件", "C:\\Users\\TC\\Desktop", "(*.txt *.png *.docx)");
        qDebug() << path;
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
