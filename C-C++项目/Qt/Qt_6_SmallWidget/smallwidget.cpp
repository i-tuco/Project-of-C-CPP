#include "smallwidget.h"
#include "ui_smallwidget.h"

SmallWidget::SmallWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SmallWidget)
{
    ui->setupUi(this);
    //QSpinBox移动 Slider跟着移动
    void(QSpinBox:: * signal)(int) = &QSpinBox::valueChanged;
    connect(ui->spinBox, signal, ui->horizontalSlider, &QSlider::setValue);

    //SLider移动，SPinBox跟着移动
    connect(ui->horizontalSlider, &QSlider::valueChanged, ui->spinBox, &QSpinBox::setValue);
}

void SmallWidget::setValue(int v)
{
    ui->spinBox->setValue(v);
}

int SmallWidget::getValue()
{
    return ui->spinBox->value();
}

SmallWidget::~SmallWidget()
{
    delete ui;
}
