#-------------------------------------------------
#
# Project created by QtCreator 2019-07-25T16:37:52
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Translation
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        administratorwidget.cpp \
        bookinfowidget.cpp \
        database.cpp \
        descriptionwidget.cpp \
        infowidget.cpp \
        main.cpp \
        mainwindow.cpp \
        messagewidget.cpp \
        releaserwidget.cpp \
        respwidget.cpp \
        selectrespwidget.cpp \
        signupwidget.cpp \
        translatorwidget.cpp \
        userwidget.cpp \
        variable.cpp

HEADERS += \
        administratorwidget.h \
        application.h \
        bookinfowidget.h \
        database.h \
        descriptionwidget.h \
        infowidget.h \
        mainwindow.h \
        messagewidget.h \
        releaserwidget.h \
        respwidget.h \
        selectrespwidget.h \
        signupwidget.h \
        stable.h \
        table.h \
        task.h \
        translatorwidget.h \
        user.h \
        userwidget.h \
        variable.h

FORMS += \
        administratorwidget.ui \
        bookinfowidget.ui \
        descriptionwidget.ui \
        infowidget.ui \
        mainwindow.ui \
        messagewidget.ui \
        releaserwidget.ui \
        respwidget.ui \
        selectrespwidget.ui \
        signupwidget.ui \
        translatorwidget.ui \
        userwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
