#ifndef RESPWIDGET_H
#define RESPWIDGET_H
#include <QWidget>
#include <QStandardItemModel>
#include <QSqlTableModel>
#include <QMessageBox>
#include "messagewidget.h"


namespace Ui {
class RespWidget;
}

class RespWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RespWidget(QWidget *parent = nullptr);
    ~RespWidget();
    void initialize();

signals:
    void sendsignal_1();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_10_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::RespWidget *ui;
    MessageWidget m;
    SubTask* sub;
    ReleaseTask* rel;
};

#endif // RESPWIDGET_H
