#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMap>
#include <QList>
#include <QUrl>
#include <QTimer>
#include <QPixmap>
#include <QContextMenuEvent>
#include <QMenu>

#include "dragFilter.h"

class QPaintEvent;

namespace Act
{
    Q_NAMESPACE

    enum RoleAct
    {
        Normal,
        Wink
    };

    Q_ENUM_NS(RoleAct)

}

using namespace Act;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void changeActRole(RoleAct role);

public slots:
    void onMenuTriggered(QAction* act);

protected:
    void paintEvent(QPaintEvent* event) override;

    void contextMenuEvent(QContextMenuEvent* event) override;

private:
    void loadRoleActResources();

    void initMenu();

private:
    RoleAct m_current_act;

    QTimer* m_timer;

    QMap<RoleAct, QList<QUrl>> m_action;
    QUrl m_current_pix;

    QMenu* m_menu;

};
#endif // WIDGET_H
