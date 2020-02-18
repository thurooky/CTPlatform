#ifndef RELEASERWIDGET_H
#define RELEASERWIDGET_H

#include <QWidget>
#include "variable.h"
#include <QSqlTableModel>
#include <QStandardItemModel>
#include <QMessageBox>
#include "selectrespwidget.h"

namespace Ui {
class ReleaserWidget;
}

class ReleaserWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ReleaserWidget(QWidget *parent = nullptr);
    ~ReleaserWidget();
    void initialize();
signals:
    void sendsignal_1();

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();


    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::ReleaserWidget *ui;
    QStandardItemModel *model;
    SelectRespWidget sel;
};

#endif // RELEASERWIDGET_H
