#ifndef TABLE_H     //内存存储数据库数据
#define TABLE_H
#include <QVector>
#include <QString>

//定义用户表格


class UserTable
{
public:
    UserTable();
    static void SetNickname(int id, QString str);
    static void SetPhonenumber(int id, QString str);
    static void SetPassword(int id, QString str);
    static void SetResidentialid(int id, QString str);
    static void SetSurplus(int id, int num);
    static void SetCredits(int id, int num);
    static const QString ShowNickname(int id)
    {return nickname[id];}
    static const QString ShowPhonenumber(int id);
private:
    static QVector<QString> nickname;
    static QVector<QString> phonenumber;
    static QVector<QString> password;
    static QVector<QString> residentialid;
    static QVector<int> surplus;
    static QVector<QString> credits;
};

#endif // TABLE_H
