#ifndef APPLICATION_H
#define APPLICATION_H
#include "user.h"

class Application
{
public:
    Application()
    {
        m_check = 0;
    }

    const QString& task()
    { return m_task;}
    const QString& applicant()
    { return m_applicant;}
    const int& check()
    { return m_check;}
    void setTask(QString task)
    { m_task = task;}
    void setApplicant(QString applicant)
    { m_applicant = applicant;}
    void setCheck(int check)
    { m_check = check;}

private:
    QString m_task;
    QString m_applicant;
    int m_check;

};

#endif // APPLICATION_H
