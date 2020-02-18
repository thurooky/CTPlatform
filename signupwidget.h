#ifndef SIGNUPWIDGET_H      //用户注册界面
#define SIGNUPWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlRecord>
#include "user.h"
#include "userwidget.h"
#include "variable.h"

namespace Ui {
class SignupWidget;
}

class SignupWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SignupWidget(QWidget *parent = nullptr);

    ~SignupWidget();
    void update();      //更新用户数据
    void checkpassword(QString, QString);        //检查密码输入
    void checkphonenumber(QString);     //检查手机号输入
    void checkresidentialid(QString);   //检查身份证
    void checkvalid();                  //检查输入信息是否有效，有效时方可点击确认

    static bool useDataBase;            //标识当前模式, 是否使用数据库
signals:
    void sendsignal_1();                //信号1关联返回登陆界面槽函数
    void sendsignal_2();                //信号2关联显示完成注册并进入用户界面槽函数
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();



    void on_phoneNumber_textChanged(const QString &arg1);

    void on_password_1_textChanged(const QString &arg1);

    void on_password_2_textChanged(const QString &arg1);

    void on_residentialId_textChanged(const QString &arg1);

private:
    Ui::SignupWidget *ui;   



};

#endif // SIGNUPWIDGET_H
