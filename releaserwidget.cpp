#include "releaserwidget.h"
#include "ui_releaserwidget.h"

ReleaserWidget::ReleaserWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReleaserWidget)
{
    ui->setupUi(this);

}

ReleaserWidget::~ReleaserWidget()
{
    delete ui;
}

void ReleaserWidget::initialize()
{
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    int row = 0;
    for(int i = 0; i < tasklist.size(); i++)
    {
        if(tasklist[i].releasername() == user.nickname())
        {
            row++;
        }
    }
    model = new QStandardItemModel(row, 6, this);
    model->setHeaderData(0, Qt::Horizontal, tr("译文名"));
    model->setHeaderData(1, Qt::Horizontal, tr("负责人"));
    model->setHeaderData(2, Qt::Horizontal, tr("原语言"));
    model->setHeaderData(3, Qt::Horizontal, tr("目标语言"));
    model->setHeaderData(4, Qt::Horizontal, tr("当前状态"));
    model->setHeaderData(5, Qt::Horizontal, tr("酬金"));
    int index = 0;
    for(int i = 0; i < tasklist.size(); i++)
    {
        if(tasklist[i].releasername() == user.nickname())
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

            model->setItem(index, 0, new QStandardItem(tasklist[i].tname()));
            model->setItem(index, 1, new QStandardItem(tasklist[i].resppersonname()));
            model->setItem(index, 2, new QStandardItem(native));
            model->setItem(index, 3, new QStandardItem(target));
            model->setItem(index, 4, new QStandardItem(state));
            model->setItem(index, 5, new QStandardItem(QString::number(tasklist[i].payment(), 10)));
            index++;
        }
    }
    ui->tableView->setModel(model);
}

void ReleaserWidget::on_pushButton_4_clicked() //返回
{
    emit sendsignal_1();
}

void ReleaserWidget::on_pushButton_6_clicked() //发布任务
{
    double surplus = user.surplus() - ui->lineEdit_6->text().toInt();
    if(surplus >= 0)
    {
        user.setSurplus(surplus);
        for(int i = 0; i < userlist.size(); i++)
        {
            if(userlist[i].nickname() == user.nickname())
            {
                userlist[i].setSurplus(surplus);
                QSqlTableModel *model = new QSqlTableModel;
                model->setTable("user");
                model->select();
                model->setData(model->index(i, 5), surplus);
                model->submitAll();
                break;
            }
        }

        QSqlTableModel *model = new QSqlTableModel;
        model->setTable("task");
        model->select();

        ReleaseTask tmp;
        tmp.setTName(ui->lineEdit->text());
        tmp.setBookName(ui->lineEdit_2->text());
        tmp.setPeriod(ui->lineEdit_3->text().toInt());
        tmp.setPayment(ui->lineEdit_6->text().toInt());
        tmp.setDescription(ui->plainTextEdit->toPlainText());
        tmp.setContent(ui->plainTextEdit_2->toPlainText());
        tmp.setNativeLanguage(LANGUAGE(ui->comboBox->currentIndex()));
        tmp.setTargetLanguage(LANGUAGE(ui->comboBox_2->currentIndex()));
        tmp.setRecruitperiod(ui->lineEdit_4->text().toInt());
        tmp.setReleasername(user.nickname());
        tasklist.push_back(tmp);
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
        model->setData(model->index(rownum, 10), tmp.resppersonname());
        model->setData(model->index(rownum, 11), tmp.releasername());
        model->setData(model->index(rownum, 12), tmp.state());
        model->submitAll();
        QMessageBox::information(this, "提示", "发布成功！", QMessageBox::Ok);
    }
    else
    {
        QMessageBox::warning(this, "提示", "余额不足！", QMessageBox::Ok);
    }
}

void ReleaserWidget::on_pushButton_clicked() //负责人确认
{
    int row = ui->tableView->currentIndex().row();
    if(row >= 0)
    {
        QAbstractItemModel *model = ui->tableView->model();
        QModelIndex index = model->index(row,0);    //选中行第一列的内容
        QString data = model->data(index).toString();
        QString data_2 = model->data(index).toString();
        if(data_2.toInt() == RELEASING)
        {
            sel.initialize(data);
            sel.show();
        }
        else
        {
            QMessageBox::warning(this, "提示", "负责人已确定！", QMessageBox::Ok);
        }
    }
}

void ReleaserWidget::on_pushButton_2_clicked() //确认完成
{
    int row = ui->tableView->currentIndex().row();
    if(row >= 0)
    {
        QAbstractItemModel *model = ui->tableView->model();
        QModelIndex index = model->index(row,0);    //选中行第一列的内容
        QModelIndex index_2 = model->index(row,3);    //选中行第四列的内容
        QString data = model->data(index).toString();
        QString data_2 = model->data(index_2).toString();
        if(data_2.toInt() == CHECKING)
        {
           for(int i = 0; i < tasklist.size(); i++)
           {
               if(tasklist[i].tname() == data)
               {
                   tasklist[i].setTaskstate(FINISHED);
                   QSqlTableModel *model = new QSqlTableModel;
                   model->setTable("task");
                   model->select();
                   model->setData(model->index(i, 12), FINISHED);
                   model->submitAll();
                   break;
               }
           }
           QMessageBox::information(this, "提示", "确认成功！", QMessageBox::Ok);
        }
        else
        {
           QMessageBox::warning(this, "提示", "任务未完成！", QMessageBox::Ok);
        }
    }

}




void ReleaserWidget::on_tableView_clicked(const QModelIndex &index) //选择译文任务
{
    int row = ui->tableView->currentIndex().row();
    QAbstractItemModel *model = ui->tableView->model();
    QModelIndex index_2 = model->index(row,0);    //选中译文名
    QString data = model->data(index_2).toString();
    QString content = "" ;
    QString translation = "" ;
    for(int i = 0; i < tasklist.size(); i++)
    {
        if(tasklist[i].tname() == data)
        {
            content = tasklist[i].content();
            translation = tasklist[i].translation();
            break;
        }
    }
    ui->textBrowser->setText(content);
    ui->textBrowser_2->setText(translation);

}
