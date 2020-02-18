#ifndef USERWIDGET_H
#define USERWIDGET_H

#include <QWidget>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include "variable.h"
#include "database.h"
#include "infowidget.h"
#include "releaserwidget.h"
#include "respwidget.h"
#include "descriptionwidget.h"
#include "translatorwidget.h"

namespace Ui {
class UserWidget;
}

class UserWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserWidget(QWidget *parent = nullptr);
    ~UserWidget();

signals:
    void sendsignal_1();

private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void initialize();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_9_clicked();

private:
    QItemSelection* select;
    Ui::UserWidget *ui;
    InfoWidget i;
    ReleaserWidget rel;
    RespWidget res;
    DescriptionWidget des;
    TranslatorWidget tran;
};

#endif // USERWIDGET_H
