#include "userwidget.h"
#include "ui_userwidget.h"

UserWidget::UserWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserWidget)
{
    ui->setupUi(this);
}

UserWidget::~UserWidget()
{
    delete ui;
}

void UserWidget::on_pushButton_5_clicked() //进入修改信息界面
{
    i.initialize();
    i.show();
    connect(&i, SIGNAL(sendsignal_1()), this, SLOT(show()));
    this->hide();
}

void UserWidget::on_pushButton_clicked() //进入发布任务界面
{
    rel.initialize();
    rel.show();
    connect(&rel, SIGNAL(sendsignal_1()), this, SLOT(show()));
    this->hide();
}

void UserWidget::on_pushButton_2_clicked() //进入负责任务界面
{
    res.initialize();
    res.show();
    connect(&rel, SIGNAL(sendsignal_1()), this, SLOT(show()));
}

void UserWidget::on_pushButton_6_clicked() //返回登录界面
{
    emit sendsignal_1();
    this->hide();
}

void UserWidget::on_pushButton_7_clicked() //查看简介
{
    int row= ui->tableView->currentIndex().row();
    QAbstractItemModel *model = ui->tableView->model();
    QModelIndex index = model->index(row,0);    //选中行第一列的内容
    QString data = model->data(index).toString();
    for(int i = 0; i < tasklist.size(); i++)
    {
        if(tasklist[i].tname() == data)
        {
            QString description = tasklist[i].description();
            des.initialize(description);
            des.show();
            break;
        }
    }
}

void UserWidget::on_pushButton_8_clicked() //搜索
{

}

void UserWidget::initialize() //初始化及刷新
{
    //初始化表格
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    QStandardItemModel *model = new QStandardItemModel(tasklist.size(), 5, this);
    model->setHeaderData(0, Qt::Horizontal, tr("译文名"));
    model->setHeaderData(1, Qt::Horizontal, tr("原语言"));
    model->setHeaderData(2, Qt::Horizontal, tr("目标语言"));
    model->setHeaderData(3, Qt::Horizontal, tr("当前状态"));
    model->setHeaderData(4, Qt::Horizontal, tr("酬金"));

    for(int i = 0; i < tasklist.size(); i++)
    {
        QString native;
        if(tasklist[i].nativelanguage() == CHINESE)
        {native = "中文";}
        else{native = "英文";}
        QString target;
        if(tasklist[i].targetlanguage() == CHINESE)
        {target = "中文";}
        else{target = "英文";}
        QString state;
        switch(tasklist[i].state())
        {
        case RELEASING:
            state = "招募负责人";
            break;
        case RECRUITING:
            state = "招募译者";
            break;
        case TRANSLATING:
            state = "翻译进行中";
            break;
        case CHECKING:
            state = "待审核";
            break;
        case FINISHED:
            state = "已完成";
            break;
        }
        model->setItem(i, 0, new QStandardItem(tasklist[i].tname()));
        model->setItem(i, 1, new QStandardItem(native));
        model->setItem(i, 2, new QStandardItem(target));
        model->setItem(i, 3, new QStandardItem(state));
        model->setItem(i, 4, new QStandardItem(QString::number(tasklist[i].payment(), 10)));
    }
    ui->tableView->setModel(model);

    //初始化按钮
    if(user.credits() < 20)
    {
        ui->pushButton_9->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
    }
    else
    {
        ui->pushButton_9->setEnabled(true);
        ui->pushButton_2->setEnabled(true);
    }
}

void UserWidget::on_pushButton_4_clicked() //翻译任务管理
{
    connect(&tran, SIGNAL(sendsignal_1()), this, SLOT(show()));
    tran.initialize();
    tran.show();
    this->hide();
}

void UserWidget::on_pushButton_3_clicked() //报名翻译
{

    int row = ui->tableView->currentIndex().row();
    if(row >= 0)
    {
        QAbstractItemModel *model = ui->tableView->model();
        QModelIndex index = model->index(row,0);    //选中行第一列的内容
        QString data = model->data(index).toString();
        for(int i = 0; i < tasklist.size(); i++)
        {
            if(tasklist[i].tname() == data)
            {
                if(tasklist[i].state() == CHECKING || tasklist[i].state() == FINISHED)
                {
                    QMessageBox::warning(this, "提示", "报名失败！", QMessageBox::Ok);
                    return;
                }
            }
        }
        Application tmp;
        tmp.setTask(data);
        tmp.setApplicant(user.nickname());
        tranapplication.push_back(tmp);
        QSqlTableModel *model_1 = new QSqlTableModel;
        model_1->setTable("tranapplication");
        model_1->select();
        int rownum = model_1->rowCount();
        model_1->insertRow(rownum);
        model_1->setData(model->index(rownum, 0), data);
        model_1->setData(model->index(rownum, 1), user.nickname());
        model_1->setData(model->index(rownum, 2), 0);
        model_1->submitAll();
        QMessageBox::information(this, "提示", "报名成功！", QMessageBox::Ok);
    }
}

void UserWidget::on_pushButton_9_clicked() //报名负责
{
    int row = ui->tableView->currentIndex().row();
    if(row > -1)
    {
        QAbstractItemModel *model = ui->tableView->model();
        QModelIndex index = model->index(row,0);    //选中行第一列的内容
        QString data = model->data(index).toString();
        for(int i = 0; i < tasklist.size(); i++)
        {
            if(tasklist[i].tname() == data)
            {
                if(tasklist[i].state() == CHECKING || tasklist[i].state() == FINISHED
                        || tasklist[i].state() == RECRUITING)
                {
                    QMessageBox::warning(this, "提示", "报名失败！", QMessageBox::Ok);
                    return;
                }
            }
        }
        Application tmp;
        tmp.setTask(data);
        tmp.setApplicant(user.nickname());
        respapplication.push_back(tmp);
        QSqlTableModel *model_1 = new QSqlTableModel;
        model_1->setTable("respapplication");
        model_1->select();
        int rownum = model_1->rowCount();
        model_1->insertRow(rownum);
        model_1->setData(model->index(rownum, 0), data);
        model_1->setData(model->index(rownum, 1), user.nickname());
        model_1->setData(model->index(rownum, 2), 0);
        model_1->submitAll();
        QMessageBox::information(this, "提示", "报名成功！", QMessageBox::Ok);
    }
}
