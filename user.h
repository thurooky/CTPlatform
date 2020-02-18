#ifndef USER_H
#define USER_H
#include "database.h"

/*
 * 用户类
 * 包含用户的基本信息
 * 管理员和客户端用户均由用户类派生
 */
class User
{
public:
    User()
    {

    }
    virtual ~User(){}

    const QString& id() const
    { return m_id; }
    const QString& phonenumber() const
    { return m_phonenumber;}
    const QString& password() const
    { return m_password; }

    void  setPhonenumber(QString phonenumber)
    { m_phonenumber = phonenumber; }
    void  setPassword(QString password)
    { m_password = password; }

    bool operator==(User &user);

protected:
    QString m_id;
    QString m_phonenumber;
    QString m_password;
};

/*
 *管理员类
 * 继承自用户类
 * 新增管理用户信息、审核身份证明权限
 */
class Administrator: public User
{
public:
private:
};

/*
 * 客户端用户类
 * 继承自用户类
 * 新增身份验证信息、支付等权限
 */


class ServerUser: public User
{
public:
    ServerUser()
    {
        m_credits = 0;
        m_surplus = 0;
        m_qualification = "";
    }
    ServerUser(const User&user);
    const int& credits() const
    { return m_credits; }
    const double& surplus() const
    { return m_surplus;}
    const QString& nickname() const
    { return m_nickname;}
    const QString& residentialid() const
    { return m_residentialid;}
    const QString& qualification() const
    { return m_qualification;}
    void setCredits(int credits)
    { m_credits = credits;}
    void setSurplus(double surplus)
    { m_surplus = surplus;}
    void setNickname(QString nickname)
    { m_nickname = nickname;}
    void setResidentialid(QString residentialid)
    { m_residentialid = residentialid;}
    void setQualification(QString qualification)
    { m_qualification = qualification;}

    bool enrollresp() const;
private:
    QString m_residentialid;    //用户的身份证号
    int m_credits;              //用户的积分，用于评估资格
    double m_surplus;           //用户的余额
    QString m_nickname;         //用户的昵称
    QString m_qualification;    //用户的资质凭证
};


#endif // USER_H
