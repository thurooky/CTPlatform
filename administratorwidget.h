#ifndef ADMINISTRATORWIDGET_H
#define ADMINISTRATORWIDGET_H

#include <QWidget>

namespace Ui {
class AdministratorWidget;
}

class AdministratorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AdministratorWidget(QWidget *parent = nullptr);
    ~AdministratorWidget();

private:
    Ui::AdministratorWidget *ui;
};

#endif // ADMINISTRATORWIDGET_H
