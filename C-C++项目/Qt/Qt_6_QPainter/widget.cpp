#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QPicture>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //============2-1点击移动按钮，移动图片=============
        //    posX = 10;
        //    connect(ui->moveBtn,&QPushButton::clicked,[=](){
        //        posX += 10;

        //        //手动调用paintEvent
        //        update();
        //    });

    //================3-1QPixmap做绘图设备(对不同平台显示做优化)===================
        //    QPixmap pix(300,300);
        //    //设置默认填充色
        //    pix.fill(Qt::white);
        //    QPainter painter(&pix);

        //    painter.setPen(QPen(Qt::green));
        //    painter.drawEllipse(QPoint(150,150),100,100);
        //    //保存
        //    pix.save("E:\\Workspace\\Qt\\Qt_6_QPainter\\pix.png");

    //================3-2QImage做绘图设备(对像素级访问进行优化)===================
        //    QImage img(300,300,QImage::Format_RGB32);
        //    img.fill(Qt::white);
        //    QPainter painter(&img);
        //    painter.setPen(QPen(Qt::blue));
        //    painter.drawEllipse(QPoint(150,150),100,100);
        //    //保存
        //    img.save("E:\\Workspace\\Qt\\Qt_6_QPainter\\img.png");

    //=====================3-4QPicture 绘图设备======================
    QPicture pic;//用于重现 记录绘图指令
    QPainter painter;
    painter.begin(&pic);//开始画图

    painter.setPen(QPen(Qt::cyan));
    painter.drawEllipse(QPoint(150,150),100,100);

    painter.end();//结束画图//保存
    pic.save("E:\\Workspace\\Qt\\Qt_6_QPainter\\pic.mx");



}

void Widget::paintEvent(QPaintEvent *)
{
    //==================1-创建画家====================
        //QPainter painter(this);

        //    //设置画笔颜色
        //    QPen pen(QColor(255,0,0));
        //    //设置笔的宽度
        //    pen.setWidth(3);
        //    //设置笔的风格
        //    pen.setStyle(Qt::DotLine);
        //    //画家用这支笔
        //    painter.setPen(pen);

        //    //画刷填充颜色
        //    QBrush brush(Qt::green);
        //    //让画家使用画刷
        //    brush.setStyle(Qt::Dense4Pattern);//设置画刷风格
        //    painter.setBrush(brush);

        //    //利用画家画画
        //    //画线
        //    painter.drawLine(QPoint(0,0), QPoint(100,100));
        //    //画圆(椭圆)
        //    painter.drawEllipse(QPoint(100,100), 100, 100);
        //    //画矩形
        //    painter.drawRect(QRect(10,10,50,50));
        //    //画字体
        //    painter.drawText(QRect(10,200,150,50),"好好学习，天天向上");

            //============1-1高级设置================
        //    painter.drawEllipse(QPoint(100,100),50,50);
        //    //1-设置抗锯齿-->效率会降低
        //    painter.setRenderHint(QPainter::Antialiasing);
        //    painter.drawEllipse(QPoint(200,100),50,50);

        //    painter.drawRect(QRect(20,20,50,50));
        //    //2-移动画家
        //    painter.translate(QPoint(100,0));
        //    //3-保存状态
        //    painter.save();
        //    painter.drawRect(QRect(20,20,50,50));

        //    painter.translate(QPoint(100,0));
        //    //3-取出状态
        //    painter.restore();
        //    painter.drawRect(QRect(20,20,50,50));

    //=====================2-画图片====================
        //如果出屏幕 强制变为10
            //    if(posX > this->width())
            //    {
            //        posX = 10;
            //    }
            //    painter.drawPixmap(posX,100,QPixmap(":/imgs/icon-home-active.png"));

    //====================3-QImage画图片==================
        //    //3-3QImage可以修改像素
        //    QImage img;
        //    img.load(":/imgs/icon-home-active.png");

        //    for(int i = 50; i < 100; i++)
        //    {
        //        for(int j = 50; j < 100; j++)
        //        {
        //            QRgb value = qRgb(255,0,0);
        //            //设置像素点
        //            img.setPixel(QPoint(i,j),value);
        //        }
        //    }

        //    QPainter painter(this);
        //    painter.drawImage(QPoint(0,0),img);

    //3-4重现绘图指令
    QPicture pic;
    pic.load("E:\\Workspace\\Qt\\Qt_6_QPainter\\pic.mx");
    QPainter painter(this);
    painter.drawPicture(0,0,pic);
}

Widget::~Widget()
{
    delete ui;
}
