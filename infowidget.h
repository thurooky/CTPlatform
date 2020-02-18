#ifndef INFOWIDGET_H
#define INFOWIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <QString>
#include <QSqlTableModel>
#include "variable.h"

namespace Ui {
class InfoWidget;
}

class InfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InfoWidget(QWidget *parent = nullptr);
    ~InfoWidget();
    void checkpassword(QString, QString);        //检查密码输入
    void checkphonenumber(QString);     //检查手机号输入
    void checkresidentialid(QString);   //检查身份证
    void checkvalid();                  //检查输入信息是否有效，有效时方可点击确认
    void initialize();
private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_lineEdit_3_textChanged(const QString &arg1);

    void on_lineEdit_4_textChanged(const QString &arg1);

    void on_lineEdit_5_textChanged(const QString &arg1);

    void on_pushButton_5_clicked();

    void on_pushButton_clicked();

signals:
    void sendsignal_1();
private:
    Ui::InfoWidget *ui;

};

#endif // INFOWIDGET_H
