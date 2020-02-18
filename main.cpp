#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QPixmap>
#include <QtGui>
#include "user.h"



//设置QSS
void setStyle(const QString &style)
{
    QFile qss(style);
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    setStyle("C:/Users/HP/Documents/Translation/white.qss");
    //启动程序加载画面
    QPixmap pixmap("C:/Users/HP/Documents/Translation/images/splash.png");
    QSplashScreen splash(pixmap);
    splash.show();          //显示图片
    a.processEvents();
    Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
    splash.showMessage(QObject::tr("Setting up the main window...\nLoading database..."),
                      topRight, Qt::white);    //显示启动信息
    MainWindow w;
    splash.finish(&w);    //图片一直显示到mainWin加载完成

    w.show();

    return a.exec();
}
