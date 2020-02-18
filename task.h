#ifndef TASK_H
#define TASK_H

#include "user.h"
#include <QString>
#include <QFile>
#include <QDate>

//定义语言枚举变量
typedef enum
{
    CHINESE, ENGLISH
}LANGUAGE;

//定义主任务类型枚举变量
typedef enum
{
    RELEASING, RECRUITING, TRANSLATING, CHECKING, FINISHED
}TASKSTATE;

/*任务类定义
 *包含任务的基本信息
 *发布任务、负责任务及翻译任务类均由此派生
 */
class Task
{
public:
   Task():
       m_bookname(""), m_tname(""), m_nativelanguage(CHINESE),
       m_targetlanguage(CHINESE),
       m_description(""), m_content(""), m_period(30), m_payment(0)
    {
       m_initialtime = QDate::currentDate();
    }
    virtual ~Task()
    {
    }
    const QString& bookname() const
    { return m_bookname;}
    const QString& tname() const
    { return m_tname; }
    const LANGUAGE& nativelanguage() const
    { return m_nativelanguage; }
    const LANGUAGE& targetlanguage() const
    { return m_targetlanguage; }
    const QString& description() const
    { return m_description; }
    const QString& content() const
    { return m_description; }
    const QString& translation() const
    { return m_translation; }
    const QDate& initialtime() const
    { return m_initialtime;}
    const int& period() const
    { return m_period;}
    const int& payment() const
    { return m_payment;}
    const TASKSTATE& state() const
    { return m_state;}
    void setBookName(QString bookname)
    { m_bookname = bookname;}
    void setTName(QString tname)
    { m_tname = tname;}
    void setNativeLanguage(LANGUAGE nativelanguage)
    { m_nativelanguage = nativelanguage;}
    void setTargetLanguage(LANGUAGE targetlanguage)
    { m_targetlanguage = targetlanguage;}
    void setDescription(QString description)
    { m_description = description;}
    void setContent(QString content)
    { m_content = content;}
    void setInitialTime(QDate initialtime)
    { m_initialtime = initialtime;}
    void setPeriod(int period)
    { m_period = period;}
    void setPayment(int payment)
    { m_payment = payment;}
    void setTaskstate(TASKSTATE state)
    { m_state = state;}
    void setTranslation(QString translation)
    { m_translation = translation;}

protected:
    QString m_bookname;
    QString m_tname;
    LANGUAGE m_nativelanguage;
    LANGUAGE m_targetlanguage;
    QString m_description;
    QString m_content;
    QDate m_initialtime;
    int m_period;
    int m_payment;
    TASKSTATE m_state;
    QString m_translation;

};


/*
 * 发布任务类
 * 由任务类派生
 */
class ReleaseTask: public Task
{
public:
    ReleaseTask():
               Task(),
               m_recruitperiod(7), m_resppersonname(""), m_releasername("")
    {
        m_state = RELEASING;
        m_initialtime = QDate::currentDate();
    }
    ReleaseTask(Task &task, int recruitperiod = 7, QString resppersonname = ""):
        Task(task), m_recruitperiod(recruitperiod), m_resppersonname(resppersonname)
    {
        m_state = RELEASING;
        m_initialtime = QDate::currentDate();
    }
    const int& recruitperiod() const
    { return m_recruitperiod;}
    const QString& resppersonname() const
    { return m_resppersonname;}
    const QString& releasername() const
    { return m_releasername;}
    void setRecruitperiod(int recruitperiod)
    { m_recruitperiod = recruitperiod;}
    void setResppersonname(QString resppersonname)
    { m_resppersonname = resppersonname;}
    void setReleasername(QString releasername)
    { m_releasername = releasername;}
private:
    int m_recruitperiod;
    QString m_resppersonname;
    QString m_releasername;
};


/*
 * 翻译(子)任务类
 * 由任务类派生
 */
class SubTask: public Task
{
public:
    SubTask():
               Task(), m_translateperiod(7), m_resppersonname(""),
             m_translatorname("")
    {
        m_state = TRANSLATING;
        m_initialtime = QDate::currentDate();

    }
    SubTask(Task &task, int translateperiod = 7):
        Task(task), m_translateperiod(translateperiod), m_resppersonname(""),
        m_translatorname("")
    {
        m_state = TRANSLATING;
        m_initialtime = QDate::currentDate();
    }
    const int& translateperiod() const
    { return m_translateperiod;}
    const QString& resppersonname() const
    { return m_resppersonname;}
    const QString& translatorname() const
    { return m_translatorname;}
    void setTranslatePeriod(int translateperiod)
    { m_translateperiod = translateperiod;}
    void setResppersonname(QString resppersonname)
    { m_resppersonname = resppersonname;}
    void setTranslatorname(QString translatorname)
    { m_translatorname = translatorname;}

private:
    int m_translateperiod;
    QString m_resppersonname;
    QString m_translatorname;

};


#endif // TASK_H
