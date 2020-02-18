#ifndef BOOKINFOWIDGET_H
#define BOOKINFOWIDGET_H

#include <QWidget>

namespace Ui {
class bookinfowidget;
}

class bookinfowidget : public QWidget
{
    Q_OBJECT

public:
    explicit bookinfowidget(QWidget *parent = nullptr);
    ~bookinfowidget();

private:
    Ui::bookinfowidget *ui;
};

#endif // BOOKINFOWIDGET_H
