#include "bookinfowidget.h"
#include "ui_bookinfowidget.h"

bookinfowidget::bookinfowidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bookinfowidget)
{
    ui->setupUi(this);
}

bookinfowidget::~bookinfowidget()
{
    delete ui;
}
