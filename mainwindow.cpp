#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("translation");
    db.setUserName("root");
    db.setPassword("zhangyy2000");
    if( !db.open() ) //数据库打开失败
    {
        QMessageBox::warning(this, "错误", db.lastError().text());//此时需要，数据库库文件(libmysql.dll)需要放到qt的安装目录里面的bin目录下
        return;
    }
    QSqlTableModel* model = new QSqlTableModel(this);
    model->setTable("user");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    if(model->select()) // 选取整个表的所有行
    {
        ServerUser tmp;
        int rowNum = model->rowCount();
        for(int i = 0; i < rowNum; i++)
        {
            tmp.setPassword(model->record(i).value("password").toString());
            tmp.setNickname(model->record(i).value("nickname").toString());
            tmp.setPhonenumber(model->record(i).value("phonenumber").toString());
            tmp.setQualification(model->record(i).value("qualification").toString());
            tmp.setResidentialid(model->record(i).value("residentialid").toString());
            tmp.setCredits(model->record(i).value("credits").toInt());
            tmp.setSurplus(model->record(i).value("surplus").toDouble());
            userlist.push_back(tmp);
        }
    }
    model->setTable("task");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    if(model->select()) // 选取整个表的所有行
    {
        ReleaseTask tmp;
        int rowNum = model->rowCount();
        for(int i = 0; i < rowNum; i++)
        {
            tmp.setTName(model->record(i).value(0).toString());
            tmp.setBookName(model->record(i).value(1).toString());
            tmp.setNativeLanguage(LANGUAGE(model->record(i).value(2).toInt()));
            tmp.setTargetLanguage(LANGUAGE(model->record(i).value(3).toInt()));
            tmp.setPayment(model->record(i).value(4).toInt());
            tmp.setDescription(model->record(i).value(5).toString());
            tmp.setContent(model->record(i).value(6).toString());
            tmp.setTranslation(model->record(i).value(7).toString());
            tmp.setPeriod(model->record(i).value(8).toInt());
            tmp.setResppersonname(model->record(i).value(10).toString());
            tmp.setReleasername(model->record(i).value(11).toString());
            tmp.setTaskstate(TASKSTATE(model->record(i).value(12).toInt()));
            tasklist.push_back(tmp);
        }
    }
    model->setTable("subtask");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    if(model->select()) // 选取整个表的所有行
    {
        SubTask tmp;
        int rowNum = model->rowCount();
        for(int i = 0; i < rowNum; i++)
        {
            tmp.setTName(model->record(i).value(0).toString());
            tmp.setBookName(model->record(i).value(1).toString());
            tmp.setNativeLanguage(LANGUAGE(model->record(i).value(2).toInt()));
            tmp.setTargetLanguage(LANGUAGE(model->record(i).value(3).toInt()));
            tmp.setPayment(model->record(i).value(4).toInt());
            tmp.setDescription(model->record(i).value(5).toString());
            tmp.setContent(model->record(i).value(6).toString());
            tmp.setTranslation(model->record(i).value(7).toString());
            tmp.setPeriod(model->record(i).value(8).toInt());
            tmp.setResppersonname(model->record(i).value(9).toString());
            tmp.setTranslatorname(model->record(i).value(10).toString());
            tmp.setTaskstate(TASKSTATE(model->record(i).value(11).toInt()));
            subtasklist.push_back(tmp);
        }
        model->setTable("respapplication");
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        if(model->select()) // 选取整个表的所有行
        {
            Application tmp;
            int rowNum = model->rowCount();
            for(int i = 0; i < rowNum; i++)
            {
                tmp.setTask(model->record(i).value(0).toString());
                tmp.setApplicant(model->record(i).value(1).toString());
                tmp.setCheck(model->record(i).value(2).toInt());
                respapplication.push_back(tmp);
            }
        }
        model->setTable("tranapplication");
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        if(model->select()) // 选取整个表的所有行
        {
            Application tmp;
            int rowNum = model->rowCount();
            for(int i = 0; i < rowNum; i++)
            {
                tmp.setTask(model->record(i).value(0).toString());
                tmp.setApplicant(model->record(i).value(1).toString());
                tmp.setCheck(model->record(i).value(2).toInt());
                tranapplication.push_back(tmp);
            }
        }
    }
}

MainWindow::~MainWindow()
{
    QSqlDatabase::removeDatabase("QMYSQL");
    delete ui;
}

void MainWindow::on_pushButton_clicked()    //用户登录
{
    QString phonenum =  ui->lineEdit->text();
    QString password =  ui->lineEdit_2->text();
    bool flag = false;
    QVector<ServerUser>::iterator iter;
    for (iter = userlist.begin(); iter != userlist.end();iter++)
    {
        if(iter->phonenumber() == phonenum)
        {
            if(iter->password() == password)
            {
                flag = true;
                user = *iter;
            }
            break;
        }
    }
    if(flag)
    {
        u.show();
        this->hide();
        connect(&u, SIGNAL(sendsignal_1()), this, SLOT(show()));
        connect(this, SIGNAL(sendsignal_1()), &u, SLOT(initialize()));
        emit sendsignal_1();
    }
    else
    {
        QMessageBox::warning(this, "错误", "用户名或密码错误，请重新输入");
    }
}

void MainWindow::on_pushButton_2_clicked()  //用户注册
{
    s.show();
    this->hide();
    connect(&s, SIGNAL(sendsignal_1()), this, SLOT(show()));
}

void MainWindow::on_pushButton_3_clicked()  //管理员登录
{
    if(ui->lineEdit->text() == "admin" && ui->lineEdit_2->text() == "123456")
    {
        a.show();
        this->hide();
        connect(&a, SIGNAL(sendignal_1()), this, SLOT(show()));
    }
    else
    {
        QMessageBox::warning(this, "错误", "用户名或密码错误，请重新输入！");
    }
}
