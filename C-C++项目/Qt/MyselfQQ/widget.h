#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QUdpSocket>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

    enum MsgType {Msg,UsrEnter,UsrLeft};
public:
    explicit Widget(QWidget *parent, QString name);
    ~Widget();

    //关闭事件
    void closeEvent(QCloseEvent *);

    //广播UDP消息
    void sndMsg(MsgType type);

    //处理新用户加入
    void usrEnter(QString username);

    //处理用户离开
    void usrLeft(QString usrname,QString time);

    //获取用户名
    QString getUsr();

    //获取聊天信息
    QString getMsg();

private:
    Ui::Widget *ui;
    QUdpSocket * udpSocket; //udp套接字
    qint16 port; //端口
    QString uName; //用户名

    void ReceiveMessage();   //接受UDP消息

signals:

    //关闭窗口发送关闭信号
    void closeWidget();

};

#endif // WIDGET_H
