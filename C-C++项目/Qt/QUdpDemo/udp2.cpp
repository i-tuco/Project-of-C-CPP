#include "udp2.h"
#include "ui_udp2.h"

Udp2::Udp2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Udp2)
{
    ui->setupUi(this);

    //初始化属性
    ui->myPort->setText("9999");
    ui->toPort->setText("8888");
    ui->toIp->setText("127.0.0.1");
    //创建套接字
    udp = new QUdpSocket(this);

    //绑定自身端口号
    udp->bind(ui->myPort->text().toInt());

    //点击了发送按钮 发送报文
    connect(ui->sentBtn,&QPushButton::clicked,[=](){
        //书写报文 参数1：内容 参数2：对方IP 参数3：对方端口
        udp->writeDatagram(ui->input->toPlainText().toUtf8(),QHostAddress(ui->toIp->text()),ui->toPort->text().toInt());

        ui->record->append("my Say : "+ ui->input->toPlainText());

        //清空输入框
        ui->input->clear();

    });

    //接收数据框
    connect(udp,&QUdpSocket::readyRead,[=](){
        //获取到报文的长度
        qint64 size = udp->pendingDatagramSize();

        QByteArray array = QByteArray(size,0);
        //读取报文
        udp->readDatagram(array.data(),size);

        //将数据同步到聊天记录中
        ui->record->append(array);
    });
}

Udp2::~Udp2()
{
    delete ui;
}
