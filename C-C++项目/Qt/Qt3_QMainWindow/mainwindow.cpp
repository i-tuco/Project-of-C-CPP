#include "mainwindow.h"
#include <QMenuBar>
#include <QToolBar>
#include <QLabel>
#include <QStatusBar>
#include <QDockWidget>
#include <QTextEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(600, 400);
    //----------菜单栏--只能有一个----------
    QMenuBar * bar = menuBar();
    //将菜单栏放入到窗口中
    this->setMenuBar(bar);
    //创建文件的菜单
    QMenu * fileMenu = bar->addMenu("文件");
    QMenu * editMenu = bar->addMenu("编辑");

    //添加菜单项
    QAction * newAction = fileMenu->addAction("新建");
    //添加分割线
    fileMenu->addSeparator();
    QAction * openAction = fileMenu->addAction("打开");


    //----------工具栏  可以有多个-----------
    QToolBar * toolBar = new QToolBar(this);
    addToolBar(Qt::LeftToolBarArea, toolBar);//停靠范围
    //只允许左右侧停靠
    toolBar->setAllowedAreas(Qt::LeftToolBarArea | Qt::RightToolBarArea);
    //设置浮动
    toolBar->setFloatable(false);
    //设置移动(总开关)
    toolBar->setMovable(false);
    //工具栏添加菜单项
    toolBar->addAction(newAction);
    toolBar->addSeparator();
    toolBar->addAction(openAction);


    //---------------状态栏--只能有一个-------------
    QStatusBar * stBar = statusBar();
    setStatusBar(stBar);
    QLabel * label = new QLabel("提示信息", this);
    stBar->addWidget(label);//添加提示信息到左侧

    QLabel * label2 = new QLabel("右侧提示信息", this);
    stBar->addPermanentWidget(label2);


    //---------------铆接部件-浮动窗口--可以有多个-------------------
    QDockWidget * dock = new QDockWidget;
    //添加铆接部件到 窗口中
    addDockWidget(Qt::BottomDockWidgetArea, dock);
    //设置停靠范围
    dock->setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);


    //--------------核心部件------------------
    QTextEdit * edit = new QTextEdit;
    setCentralWidget(edit);
}

MainWindow::~MainWindow()
{

}
