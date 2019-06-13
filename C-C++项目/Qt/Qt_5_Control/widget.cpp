#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>
#include <QMovie>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //单选按钮 默认选中 男
    ui->rBtnMan->setChecked(true);

    //点击女 就打印选中了
    connect(ui->rBtnWoman, &QRadioButton::clicked, [=](){
        qDebug() <<"选中 女 选项";
    });

    //多选框选中后打印
    //选中 2 未选中 0 tristate(半选) 1
    connect(ui->checkBox, &QCheckBox::stateChanged, [=](int state){
        qDebug() << state;
    });


    //======================利用listWidget 写诗=========================
    //QListWidgetItem * item = new QListWidgetItem("爱情本无法，真爱如昙花");
    //设置对齐方式
    //item->setTextAlignment(Qt::AlignHCenter);
    //ui->listWidget->addItem(item);

    QStringList list;
    list << "爱情本无法" << "真爱如昙花" << "是罚不是罚" <<"一生时间差";
    ui->listWidget->addItems(list);


    //======================treeWidget控件使用===========================
    //添加头
    ui->treeWidget->setHeaderLabels(QStringList() << "英雄姓名"<<"英雄介绍");
    //添加项目
    QTreeWidgetItem * liItem = new QTreeWidgetItem(QStringList() << "力量");
    QTreeWidgetItem * minItem = new QTreeWidgetItem(QStringList() << "敏捷");
    QTreeWidgetItem * zhiItem = new QTreeWidgetItem(QStringList() << "智力");
    //添加顶层项目
    ui->treeWidget->addTopLevelItem(liItem);
    ui->treeWidget->addTopLevelItem(minItem);
    ui->treeWidget->addTopLevelItem(zhiItem);
    //追加子项目 子项目也是QTreeWidgetItem

    QStringList heroL1;
    QStringList heroL2;
    QStringList heroM1;
    QStringList heroM2;
    QStringList heroZ1;
    QStringList heroZ2;
    heroL1 << "刚被猪" << "前排坦克，能在吸收伤害的同时造成可观的范围输出";
    heroL2 << "船长" << "前排坦克，能肉能输出能控场的全能英雄";

    heroM1 << "月骑" << "中排物理输出，可以使用分裂利刃攻击多个目标";
    heroM2 << "小鱼人" << "前排战士，擅长偷取敌人的属性来增强自身战力";

    heroZ1 << "死灵法师" << "前排法师坦克，魔法抗性较高，拥有治疗技能";
    heroZ2 << "巫医" << "后排辅助法师，可以使用奇特的巫术诅咒敌人与治疗队友";

    QTreeWidgetItem * li1 = new QTreeWidgetItem(heroL1);
    liItem->addChild(li1);
    QTreeWidgetItem * li2 = new QTreeWidgetItem(heroL2);
    liItem->addChild(li2);
    QTreeWidgetItem * min1 = new QTreeWidgetItem(heroM1);
    minItem->addChild(min1);
    QTreeWidgetItem * min2 = new QTreeWidgetItem(heroM2);
    minItem->addChild(min2);
    QTreeWidgetItem * zhi1 = new QTreeWidgetItem(heroZ1);
    zhiItem->addChild(zhi1);
    QTreeWidgetItem * zhi2 = new QTreeWidgetItem(heroZ2);
    zhiItem->addChild(zhi2);


    //======================tableWidget控件==================
    //先告诉控件一共有多少列
    QStringList tablelist;
    tablelist<<"姓名"<<"性别"<<"年龄";
    ui->tableWidget->setColumnCount(tablelist.size());
    //设置水平头
    ui->tableWidget->setHorizontalHeaderLabels(tablelist);
    //设置行数
    ui->tableWidget->setRowCount(5);
    //设置正文
    //ui->tableWidget->setItem(0,0,new QTableWidgetItem("亚瑟"));
    //准备数据
    QStringList nameList;
    QStringList sexList;
    nameList<<"亚瑟"<<"妲己"<<"安琪拉"<<"东皇太一"<<"李白";
    sexList<<"男"<<"女"<<"女"<<"男"<<"男";
    for(int i = 0; i < 5; i++)
    {
        int col = 0;
        ui->tableWidget->setItem(i, col++, new QTableWidgetItem(nameList[i]));
        //添加性别
        ui->tableWidget->setItem(i, col++, new QTableWidgetItem(sexList.at(i)));
        //添加年龄
        //int 转 QString
        ui->tableWidget->setItem(i, col++, new QTableWidgetItem(QString::number(i+18)));
    }

    //点击按钮 添加赵云
    connect(ui->addBtn, &QPushButton::clicked,[=](){
        //先判断有没有赵云
        bool isEmpty = ui->tableWidget->findItems("赵云", Qt::MatchExactly).empty();

        if(isEmpty)
        {
            ui->tableWidget->insertRow(0);
            ui->tableWidget->setItem(0, 0, new QTableWidgetItem("赵云"));
            ui->tableWidget->setItem(0, 1, new QTableWidgetItem("男"));
            ui->tableWidget->setItem(0, 2, new QTableWidgetItem(QString::number(20)));
        }
        else{
            QMessageBox::warning(this, "警告", "赵云已存在！");
        }
    });

    //点击按钮删除赵云
    connect(ui->delBtn, &QPushButton::clicked,[=](){
        bool isEmpty = ui->tableWidget->findItems("赵云", Qt::MatchExactly).empty();

        if(isEmpty)
        {
            QMessageBox::warning(this, "警告", "赵云不存在！");
        }
        else{
            //找到赵云所在的行
            int row = ui->tableWidget->findItems("赵云", Qt::MatchExactly).first()->row();
            //找到行数 删除
            ui->tableWidget->removeRow(row);
        }
    });


    //============================stackWidget===========================
    //设置默认选中第0项
    ui->stackedWidget->setCurrentIndex(0);
    connect(ui->btnScroll, &QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(ui->btnTool, &QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(1);
    });
    connect(ui->btnTab, &QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(2);
    });


    //=================comboBox下拉框=======================
    ui->comboBox->addItem("奔驰");
    ui->comboBox->addItem("宝马");
    ui->comboBox->addItem("拖拉机");
    //点击拖拉机按钮
    connect(ui->btnChoose, &QPushButton::clicked, [=](){
        ui->comboBox->setCurrentText("拖拉机");
    });

    //================利用QLabel 显示图片==========================
    ui->imgLable->setPixmap(QPixmap(":/images/i4.png"));

    //=======利用QLabel 显示gif图片==========
    QMovie * movie = new QMovie(":/images/i5.gif");
    ui->movieLable->setMovie(movie);
    //播放GIF图片
    movie->start();
}

Widget::~Widget()
{
    delete ui;
}
