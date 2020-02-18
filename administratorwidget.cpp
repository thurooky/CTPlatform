#include "administratorwidget.h"
#include "ui_administratorwidget.h"

AdministratorWidget::AdministratorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdministratorWidget)
{
    ui->setupUi(this);
}

AdministratorWidget::~AdministratorWidget()
{
    delete ui;
}
