#include "widget.h"

#include <QApplication>
#include <QSystemTrayIcon>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    QSystemTrayIcon sys_tray(QIcon("://resources/logo.png"), &w);

    QMenu menu;
    QAction* showAct = new QAction("显示", &sys_tray);
    QAction* exitAct = new QAction("退出", &sys_tray);

    QObject::connect(showAct, &QAction::triggered, [&]()
                     {
        w.setVisible(true);
    });

    QObject::connect(exitAct, &QAction::triggered, [&]()
                     {
        QApplication::quit();
    });

    menu.addAction(showAct);
    menu.addAction(exitAct);

    sys_tray.setContextMenu(&menu);;

    sys_tray.show();
    w.show();
    return a.exec();
}
