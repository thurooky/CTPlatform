#include "infowidget.h"
#include "ui_infowidget.h"

InfoWidget::InfoWidget(QWidget *parent) :
    QWidget (parent),
    ui(new Ui::InfoWidget)
{
    ui->setupUi(this);
}

InfoWidget::~InfoWidget()
{
    delete ui;
}

void InfoWidget::checkpassword(QString str1, QString str2)
{
    if (str1.count() < 6 || str1.count() > 16)
    {
        ui->checkBox_2->setChecked(false);
    }
    else
    {
        ui->checkBox_2->setChecked(true);
    }
    if (str1 != str2 || str2 == "")
    {
        ui->checkBox_3->setChecked(false);
    }
    else
    {
        ui->checkBox_3->setChecked(true);
    }
    checkvalid();
}

void InfoWidget::checkphonenumber(QString str)
{
    if(str.count() == 11)
    {
        ui->checkBox->setChecked(true);
    }
    else
    {
        ui->checkBox->setChecked(false);
    }
    checkvalid();
}

void InfoWidget::checkresidentialid(QString str)
{
    if(str.count() == 18)
    {
        ui->checkBox_4->setChecked(true);
    }
    else
    {
        ui->checkBox_4->setChecked(false);
    }
    checkvalid();

}

void InfoWidget::checkvalid()
{
    if(ui->checkBox->isChecked() && ui->checkBox_2->isChecked() &&
       ui->checkBox_3->isChecked() && ui->checkBox_4->isChecked())
    {
        ui->pushButton_5->setEnabled(true);
    }
}


void InfoWidget::on_pushButton_4_clicked()  //返回按钮
{
    int index = 0;
    for(int i = 0; i < userlist.size(); i++)
    {
        if(user.nickname() == userlist[i].nickname())
        {
            index = i;
            break;
        }
    }

    QSqlTableModel *model = new QSqlTableModel;
    model->setTable("user");
    model->select();
    model->setData(model->index(index, 0), user.phonenumber());
    model->setData(model->index(index, 1), user.password());
    model->setData(model->index(index, 2), user.nickname());
    model->setData(model->index(index, 3), user.residentialid());
    model->setData(model->index(index, 4), user.credits());
    model->setData(model->index(index, 5), user.surplus());
    model->setData(model->index(index, 6), user.qualification());
    model->submitAll();

    emit sendsignal_1();
    this->hide();
}

void InfoWidget::on_pushButton_2_clicked()  //提交资质证明
{
    QMessageBox::information(this, "提示", "提交成功！", QMessageBox::Ok);
    user.setQualification(ui->lineEdit_9->text());
    int index = 0;
    for(int i = 0; i < userlist.size(); i++)
    {
        if(user.nickname() == userlist[i].nickname())
        {
            index = i;
            break;
        }
    }
    userlist[index].setQualification(ui->lineEdit_9->text());
}

void InfoWidget::on_pushButton_3_clicked()  //修改密码
{
    ui->lineEdit_5->setEnabled(true);
}

void InfoWidget::on_lineEdit_2_textChanged(const QString &arg1)
{
    checkphonenumber(arg1);
}

void InfoWidget::on_lineEdit_3_textChanged(const QString &arg1)
{
    checkpassword(arg1, ui->lineEdit_4->text());

}

void InfoWidget::on_lineEdit_4_textChanged(const QString &arg1)
{
    checkpassword(ui->lineEdit_3->text(), arg1);

}

void InfoWidget::on_lineEdit_5_textChanged(const QString &arg1)
{
    checkresidentialid(arg1);
}

void InfoWidget::on_pushButton_5_clicked() //确认修改
{
    QMessageBox::information(this, "提示", "修改成功！", QMessageBox::Ok);
    int index = 0;
    for(int i = 0; i < userlist.size(); i++)
    {
        if(user.nickname() == userlist[i].nickname())
        {
            index = i;
            break;
        }
    }
    user.setNickname(ui->lineEdit->text());
    user.setPhonenumber(ui->lineEdit_2->text());
    user.setPassword(ui->lineEdit_3->text());
    user.setResidentialid(ui->lineEdit_5->text());
    userlist[index].setNickname(ui->lineEdit->text());
    userlist[index].setPhonenumber(ui->lineEdit_2->text());
    userlist[index].setPassword(ui->lineEdit_3->text());
    userlist[index].setResidentialid(ui->lineEdit_5->text());

}

void InfoWidget::on_pushButton_clicked()
{
    QMessageBox::information(this, "提示", "充值成功", QMessageBox::Ok);
    QString str = ui->lineEdit_8->text();
    double surplus = str.toDouble() + user.surplus();
    user.setSurplus(surplus);
    int index = 0;
    for(int i = 0; i < userlist.size(); i++)
    {
        if(user.nickname() == userlist[i].nickname())
        {
            index = i;
            break;
        }
    }
    userlist[index].setSurplus(surplus);
    ui->lineEdit_6->setText(QString::number(user.surplus(), 'f', 2));
}

void InfoWidget::initialize()
{
    ui->lineEdit->setText(user.nickname());
    ui->lineEdit_2->setText(user.phonenumber());
    ui->lineEdit_3->setText(user.password());
    ui->lineEdit_4->setText(user.password());
    ui->lineEdit_5->setText(user.residentialid());
    ui->lineEdit_6->setText(QString::number(user.surplus(), 'f', 2));
    ui->lineEdit_7->setText(QString::number(user.credits(), 10));
}
