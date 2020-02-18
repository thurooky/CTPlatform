#include "selectrespwidget.h"
#include "ui_selectrespwidget.h"

SelectRespWidget::SelectRespWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectRespWidget)
{
    ui->setupUi(this);
}

SelectRespWidget::~SelectRespWidget()
{
    delete ui;
}

void SelectRespWidget::initialize(QString task)
{
    m_task = task;
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    int row = 0;
    for(int i = 0; i < respapplication.size(); i++)
    {
        if(respapplication[i].task() == task)
        {
            row++;
        }
    }
    QStandardItemModel *model = new QStandardItemModel(row, 2, this);
    model->setHeaderData(0, Qt::Horizontal, tr("用户名"));
    model->setHeaderData(1, Qt::Horizontal, tr("当前积分"));
    int index = 0;
    for(int i = 0; i < respapplication.size(); i++)
    {
        if(respapplication[i].task() == task)
        {
            QString credits;
            for(int i = 0 ; i < userlist.size(); i++)
            {
                   if(userlist[i].nickname() == respapplication[i].applicant())
                   {
                       credits = QString::number(userlist[i].credits(), 10);
                       break;
                   }
            }
            model->setItem(index, 0, new QStandardItem(respapplication[i].applicant()));
            model->setItem(index, 1, new QStandardItem(credits));
            index++;
        }
    }
    ui->tableView->setModel(model);
}

void SelectRespWidget::on_pushButton_clicked() //确认负责人
{
    int row = ui->tableView->currentIndex().row();
    QAbstractItemModel *model = ui->tableView->model();
    QModelIndex index = model->index(row,0);    //选中行第一列的内容
    QString data = model->data(index).toString();
    for(int i = 0; i < tasklist.size(); i++)
    {
        if(m_task == tasklist[i].tname())
        {
            tasklist[i].setResppersonname(data);
            tasklist[i].setTaskstate(RECRUITING);
            QSqlTableModel *model = new QSqlTableModel;
            model->setTable("task");
            model->select();
            model->setData(model->index(i, 11), data);
            model->setData(model->index(i, 12), RECRUITING);
            model->submitAll();
            break;
        }
    }
    QMessageBox::information(this, "提示", "确认成功！", QMessageBox::Ok);
}
