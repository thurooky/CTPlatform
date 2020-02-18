#include "descriptionwidget.h"
#include "ui_descriptionwidget.h"

DescriptionWidget::DescriptionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DescriptionWidget)
{
    ui->setupUi(this);
}

DescriptionWidget::~DescriptionWidget()
{
    delete ui;
}

void DescriptionWidget::initialize(QString str)
{
    ui->textBrowser->setText(str);
}
