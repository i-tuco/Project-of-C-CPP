#include "student.h"
#include <QDebug>

Student::Student(QObject *parent) : QObject(parent)
{

}

void Student::treat()
{
    qDebug() << "请老师吃饭";
}

void Student::treat(QString foodName)
{
    qDebug() << "请老师吃饭, 老师要吃" << foodName;

    //QString 转char *
    //先转成QByteArray类型 再转char *
    qDebug() << "请老师吃饭, 老师要吃" << foodName.toUtf8().data();
}
