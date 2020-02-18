#include "respwidget.h"
#include "ui_respwidget.h"

RespWidget::RespWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RespWidget)
{
    ui->setupUi(this);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
}

RespWidget::~RespWidget()
{
    delete ui;
}

void RespWidget::initialize()
{
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    int row = 0;
    for(int i = 0; i < tasklist.size(); i++)
    {
        if(tasklist[i].resppersonname() == user.nickname())
        {
            row++;
        }
    }
    QStandardItemModel *model = new QStandardItemModel(row, 5, this);
    model->setHeaderData(0, Qt::Horizontal, tr("译文名"));
    model->setHeaderData(1, Qt::Horizontal, tr("原语言"));
    model->setHeaderData(2, Qt::Horizontal, tr("目标语言"));
    model->setHeaderData(3, Qt::Horizontal, tr("当前状态"));
    model->setHeaderData(4, Qt::Horizontal, tr("酬金"));
    int index = 0;
    for(int i = 0; i < tasklist.size(); i++)
    {
        if(tasklist[i].resppersonname() == user.nickname())
        {
            QString native;
            if(tasklist[i].nativelanguage() == CHINESE)
            {native = "中文";}
            else{native = "英文";}
            QString target;
            if(tasklist[i].targetlanguage() == CHINESE)
            {target = "中文";}
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
            model->setItem(index, 0, new QStandardItem(tasklist[i].tname()));
            model->setItem(index, 1, new QStandardItem(native));
            model->setItem(index, 2, new QStandardItem(target));
            model->setItem(index, 3, new QStandardItem(state));
            model->setItem(index, 4, new QStandardItem(QString::number(tasklist[i].payment(), 10)));
            index++;
        }
    }
    ui->tableView->setModel(model);


    ui->tableView_7->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_7->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_7->setSelectionBehavior(QAbstractItemView::SelectRows);
    int row_2 = 0;
    for(int i = 0; i < subtasklist.size(); i++)
    {
        if(subtasklist[i].resppersonname() == user.nickname())
        {
            row_2++;
        }
    }
    QStandardItemModel *model_1 = new QStandardItemModel(row, 5, this);
    model_1->setHeaderData(0, Qt::Horizontal, tr("译文名"));
    model_1->setHeaderData(1, Qt::Horizontal, tr("原语言"));
    model_1->setHeaderData(2, Qt::Horizontal, tr("目标语言"));
    model_1->setHeaderData(3, Qt::Horizontal, tr("当前状态"));
    model_1->setHeaderData(4, Qt::Horizontal, tr("酬金"));
    int index_2 = 0;
    for(int i = 0; i < subtasklist.size(); i++)
    {
        if(subtasklist[i].resppersonname() == user.nickname())
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
            model_1->setItem(index_2, 0, new QStandardItem(subtasklist[i].tname()));
            model_1->setItem(index_2, 1, new QStandardItem(native));
            model_1->setItem(index_2, 2, new QStandardItem(target));
            model_1->setItem(index_2, 3, new QStandardItem(state));
            model_1->setItem(index_2, 4, new QStandardItem(QString::number(subtasklist[i].payment(), 10)));
            index_2++;
        }
    }
    ui->tableView_7->setModel(model_1);
}

void RespWidget::on_pushButton_3_clicked() //返回
{
    emit sendsignal_1();
    this->hide();
}

void RespWidget::on_pushButton_6_clicked() //确认发布
{
    SubTask tmp;
    tmp.setTName(ui->lineEdit->text());
    tmp.setTranslatorname(ui->lineEdit->text());
    tmp.setPayment(ui->lineEdit_6->text().toInt());
    tmp.setContent(ui->plainTextEdit_2->toPlainText());
    tmp.setResppersonname(user.nickname());
    subtasklist.push_back(tmp);
    QSqlTableModel *model = new QSqlTableModel;
    model->setTable("subtask");
    model->select();
    int rownum = model->rowCount();
    model->insertRow(rownum);
    model->setData(model->index(rownum, 0), tmp.tname());
    model->setData(model->index(rownum, 1), tmp.bookname());
    model->setData(model->index(rownum, 2), tmp.nativelanguage());
    model->setData(model->index(rownum, 3), tmp.targetlanguage());
    model->setData(model->index(rownum, 4), tmp.payment());
    model->setData(model->index(rownum, 5), tmp.description());
    model->setData(model->index(rownum, 6), tmp.content());
    model->setData(model->index(rownum, 7), tmp.translation());
    model->setData(model->index(rownum, 8), tmp.period());
    model->setData(model->index(rownum, 9), tmp.resppersonname());
    model->setData(model->index(rownum, 10), tmp.translatorname());
    model->setData(model->index(rownum, 11), tmp.state());
    model->submitAll();
    QMessageBox::information(this, "提示", "发布成功！", QMessageBox::Ok);
}



void RespWidget::on_pushButton_5_clicked() //联系译者
{
    m.show();
    this->hide();
}

void RespWidget::on_pushButton_4_clicked() //选择译者
{
    //s1.show();
    //this->hide();
}

void RespWidget::on_pushButton_clicked()  //查看原文
{

}

void RespWidget::on_tableView_clicked(const QModelIndex &index) //选择主任务
{
    int row = ui->tableView->currentIndex().row();
    QAbstractItemModel *model_1 = ui->tableView->model();
    QModelIndex index_2 = model_1->index(row,0);
    QString data = model_1->data(index_2).toString();
    ui->tableView_4->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_4->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_4->setSelectionBehavior(QAbstractItemView::SelectRows);

    int rownum = 0;
    for(int i = 0; i < tranapplication.size(); i++)
    {
        if(data == tranapplication[i].task())
        {
            rownum++;
        }
    }
    QStandardItemModel *model = new QStandardItemModel(rownum, 2, this);
    model->setHeaderData(0, Qt::Horizontal, tr("用户名"));
    model->setHeaderData(1, Qt::Horizontal, tr("积分"));
    int index_1 = 0;
    for(int i = 0; i < tranapplication.size(); i++)
    {
        if(data == tranapplication[i].task())
        {
            QString name = tranapplication[i].applicant();
            int credits = 0;
            model->setItem(index_1, 0, new QStandardItem(name));
            for(int i = 0 ; i < userlist.size() ; i++)
            {
                if(userlist[i].nickname() == name)
                {
                    credits = userlist[i].credits();
                    break;
                }
            }
            model->setItem(index_1, 1, new QStandardItem(credits));
            index_1++;
        }
    }
    ui->tableView_4->setModel(model);
    QString content = "";
    QString translation = "";
    for(int i = 0; i < tasklist.size(); i++)
    {
        if(tasklist[i].tname() == data)
        {
            content = tasklist[i].content();
            translation = tasklist[i].translation();
        }
    }
    ui->textBrowser_3->setText(content);
    ui->plainTextEdit->setPlainText(translation);
}


void RespWidget::on_pushButton_10_clicked() //确定译者
{
    int row_1 = ui->tableView_4->currentIndex().row();
    QAbstractItemModel *model = ui->tableView->model();
    QModelIndex index = model->index(row_1,0);    //选中行第一列的内容
    QString uname = model->data(index).toString();
    int row_2 = ui->tableView->currentIndex().row();
    QAbstractItemModel *model_1 = ui->tableView->model();
    QModelIndex index_2 = model_1->index(row_2,0);
    QString tname = model_1->data(index_2).toString();
    if(row_1 >= 0 && row_2 >= 0)
    {
        for(int i = 0; i < tranapplication.size(); i++)
        {
            if(tname == tranapplication[i].task() && uname == tranapplication[i].applicant())
            {
                tranapplication[i].setCheck(1);
                QSqlTableModel *model = new QSqlTableModel;
                model->setTable("tranapplication");
                model->select();
                model->setData(model->index(i, 2), 1);
                model->submitAll();
                break;
            }
        }
        QMessageBox::information(this, "提示", "确认成功！", QMessageBox::Ok);
    }
}

void RespWidget::on_pushButton_8_clicked() //确认完成
{
    int row_1 = ui->tableView_7->currentIndex().row();
    QAbstractItemModel *model = ui->tableView->model();
    QModelIndex index_1 = model->index(row_1,0);    //选中行第一列的内容
    QModelIndex index_2 = model->index(row_1,3);
    QString tname = model->data(index_1).toString();
    QString state = model->data(index_2).toString();
    if(state == "待审核")
    {
        QMessageBox::information(this, "提示", "确认成功！", QMessageBox::Ok);
        for(int i = 0; i < subtasklist.size(); i++)
        {
            if( tname == subtasklist[i].tname())
            {
                subtasklist[i].setTaskstate(FINISHED);
                QSqlTableModel *model = new QSqlTableModel;
                model->setTable("subtask");
                model->select();
                model->setData(model->index(i, 12), FINISHED);
                model->submitAll();
                break;
            }
        }
    }
    else
    {
        QMessageBox::warning(this, "警告", "该任务尚未提交", QMessageBox::Ok);
    }
}



