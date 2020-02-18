#ifndef TRANSLATORWIDGET_H
#define TRANSLATORWIDGET_H

#include <QWidget>
#include <QStandardItemModel>
#include "variable.h"
#include <QSqlTableModel>

namespace Ui {
class TranslatorWidget;
}

class TranslatorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TranslatorWidget(QWidget *parent = nullptr);
    ~TranslatorWidget();
    void initialize();

signals:
    void sendsignal_1();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::TranslatorWidget *ui;
    QStandardItemModel *model;
};

#endif // TRANSLATORWIDGET_H
