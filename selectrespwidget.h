#ifndef SELECTRESPWIDGET_H
#define SELECTRESPWIDGET_H

#include <QWidget>
#include "variable.h"
#include <QStandardItemModel>
#include <QMessageBox>
#include <QSqlTableModel>

namespace Ui {
class SelectRespWidget;
}

class SelectRespWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SelectRespWidget(QWidget *parent = nullptr);
    ~SelectRespWidget();
    void initialize(QString task);

private slots:
    void on_pushButton_clicked();

private:
    Ui::SelectRespWidget *ui;
    QString m_task;
};

#endif // SELECTRESPWIDGET_H
