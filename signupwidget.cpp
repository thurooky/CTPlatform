#include "signupwidget.h"
#include "ui_signupwidget.h"

SignupWidget::SignupWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignupWidget)
{
    ui->setupUi(this);
}

SignupWidget::~SignupWidget()
{
    delete ui;
}

void SignupWidget::on_pushButton_clicked()
{
    emit sendsignal_1();
    this->hide();
}

void SignupWidget::on_pushButton_2_clicked()
{
    QMessageBox::information(this, "提示", "注册成功！", QMessageBox::Ok);
    emit sendsignal_1();
    ServerUser tmp;
    tmp.setNickname(ui->lineEdit->text());
    tmp.setPhonenumber(ui->phoneNumber->text());
    tmp.setPassword(ui->password_1->text());
    tmp.setResidentialid(ui->residentialId->text());
    userlist.push_back(tmp);
    QSqlTableModel *model = new QSqlTableModel;
    model->setTable("user");
    model->select();
    int rownum = model->rowCount();
    model->insertRow(rownum);
    model->setData(model->index(rownum, 0), tmp.phonenumber());
    model->setData(model->index(rownum, 1), tmp.password());
    model->setData(model->index(rownum, 2), tmp.nickname());
    model->setData(model->index(rownum, 3), tmp.residentialid());
    model->setData(model->index(rownum, 4), tmp.credits());
    model->setData(model->index(rownum, 5), tmp.surplus());
    model->setData(model->index(rownum, 6), tmp.qualification());
    model->submitAll();
    this->hide();
}

void SignupWidget::checkpassword(QString str1, QString str2)
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

void SignupWidget::checkphonenumber(QString str)
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

void SignupWidget::checkresidentialid(QString str)
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

void SignupWidget::checkvalid()
{
    if(ui->checkBox->isChecked() && ui->checkBox_2->isChecked() &&
       ui->checkBox_3->isChecked() && ui->checkBox_4->isChecked())
    {
        ui->pushButton_2->setEnabled(true);
    }
}




void SignupWidget::on_phoneNumber_textChanged(const QString &arg1)
{
    checkphonenumber(arg1);
}

void SignupWidget::on_password_1_textChanged(const QString &arg1)
{
    checkpassword(arg1, ui->password_2->text());
}

void SignupWidget::on_password_2_textChanged(const QString &arg1)
{
    checkpassword(ui->password_1->text(), arg1);
}

void SignupWidget::on_residentialId_textChanged(const QString &arg1)
{
    checkresidentialid(arg1);
}
