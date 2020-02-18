#include "translatorwidget.h"
#include "ui_translatorwidget.h"

TranslatorWidget::TranslatorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TranslatorWidget)
{
    ui->setupUi(this);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
}


TranslatorWidget::~TranslatorWidget()
{
    delete ui;
}

void TranslatorWidget::initialize()
{
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    int row = 0;
    for(int i = 0; i < subtasklist.size(); i++)
    {
        if(subtasklist[i].translatorname() == user.nickname())
        {
            row++;
        }
    }
    model = new QStandardItemModel(row, 5, this);
    model->setHeaderData(0, Qt::Horizontal, tr("译文名"));
    model->setHeaderData(1, Qt::Horizontal, tr("原语言"));
    model->setHeaderData(2, Qt::Horizontal, tr("目标语言"));
    model->setHeaderData(3, Qt::Horizontal, tr("当前状态"));
    model->setHeaderData(4, Qt::Horizontal, tr("酬金"));
    int index = 0;
    for(int i = 0; i < subtasklist.size(); i++)
    {

        if(subtasklist[i].translatorname() == user.nickname())
        {
            QString native;
            if(subtasklist[i].nativelanguage() == CHINESE)
            {native = "中文";}
            else{native = "英文";}
            QString target;
            if(subtasklist[i].targetlanguage() == CHINESE)
            {target = "中文";}
            else{target = "英文";}

            model->setItem(index, 0, new QStandardItem(subtasklist[i].tname()));
            model->setItem(index, 1, new QStandardItem(native));
            model->setItem(index, 2, new QStandardItem(target));
            model->setItem(index, 3, new QStandardItem(subtasklist[i].initialtime().addDays(subtasklist[index].period()).toString()));//时间待补充
            model->setItem(index, 4, new QStandardItem(QString::number(subtasklist[i].payment(), 10)));
            subtasklist[index].initialtime();
        }
    }
    ui->tableView->setModel(model);
}

void TranslatorWidget::on_pushButton_2_clicked() //返回
{
    emit sendsignal_1();
}

void TranslatorWidget::on_pushButton_clicked()  //提交译文
{
    int row = ui->tableView->currentIndex().row();
    if(row >= 0)
    {
        QAbstractItemModel *model = ui->tableView->model();
        QModelIndex index = model->index(row,0);    //选中行第一列的内容
        QString data = model->data(index).toString();
        QString text = ui->plainTextEdit->toPlainText();
        for(int i = 0; i < subtasklist.size(); i++)
        {
            if(data == subtasklist[i].tname())
            {
                subtasklist[i].setTranslation(text);
                subtasklist[i].setTaskstate(CHECKING);
                QSqlTableModel *model = new QSqlTableModel;
                model->setTable("subtask");
                model->select();
                model->setData(model->index(i, 7), text);
                model->setData(model->index(i, 11), CHECKING);
                model->submitAll();
                break;
            }
        }
    }
}

