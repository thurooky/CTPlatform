#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QString>
#include <QSqlError>
#include <QVector>

class Database
{
public:
    Database(QString dbname, QString tbname, QString parameters, QString primaryKey = "id");
    Database(int type, QString primaryKey="id");//专门用来打开用户数据库, type标识用户类别
    Database(){}
    ~Database();
    void insert(QString values);                                        //插入
    void update(QString parameter, QString par_value, QString expression);//更新
    QStringList select(QString parameter);                              //提取所有的条目中的parameter项
    QVector<int> selectInt(QString parameter);                          //提取所有条目中的parameter项并转为整值
    int selectMax(QString parameter);                                   //返回parameter的最大值
    void deleteline(QString parameter,QString value);
    void clear();                                                       //清空数据表
    int count();
    
private:
    QSqlDatabase openDatabase(QString name);
    QString m_dbname;           //数据库名称
    QString m_tbname;           //表格名称
    QString m_parameters;       //创建表格所需参数
    QString m_primaryKey;       //主键
    QSqlDatabase m_database;
};


#endif // DATABASE_H
