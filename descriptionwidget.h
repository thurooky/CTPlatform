#ifndef DESCRIPTIONWIDGET_H
#define DESCRIPTIONWIDGET_H

#include <QWidget>

namespace Ui {
class DescriptionWidget;
}

class DescriptionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DescriptionWidget(QWidget *parent = nullptr);
    ~DescriptionWidget();
    void initialize(QString str);

private:
    Ui::DescriptionWidget *ui;
};

#endif // DESCRIPTIONWIDGET_H
