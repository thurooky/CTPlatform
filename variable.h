#ifndef VARIABLE_H
#define VARIABLE_H
#include "user.h"
#include "task.h"
#include "application.h"

extern ServerUser user;
extern Administrator admin;
extern QVector<ServerUser> userlist;
extern QVector<ReleaseTask> tasklist;
extern QVector<SubTask> subtasklist;
extern QVector<Application> tranapplication;
extern QVector<Application> respapplication;

#endif // VARIABLE_H
