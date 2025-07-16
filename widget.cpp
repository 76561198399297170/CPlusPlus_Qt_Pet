#include "widget.h"

#include <QPaintEvent>
#include <QCursor>
#include <QPainter>
#include <QMetaEnum>

Widget::Widget(QWidget* parent)
    : QWidget(parent),
    m_timer(new QTimer(this)),
    m_menu(new QMenu(this))
{
    this->installEventFilter(new DragFilter);

    this->setWindowFlag(Qt::FramelessWindowHint);//去边框
    this->setAttribute(Qt::WA_TranslucentBackground);//去背景

    connect(this->m_timer, &QTimer::timeout, [this]()
            {
        static int pix_idx = 0;
        QList<QUrl> paths = this->m_action.value(this->m_current_act);

        this->m_current_pix = paths[pix_idx++ % paths.size()];

        this->update();
    });

    this->loadRoleActResources();
    this->initMenu();

    this->changeActRole(RoleAct::Normal);
}

Widget::~Widget() {}

void Widget::changeActRole(RoleAct role)
{
    this->m_timer->stop();

    this->m_current_act = role;

    this->m_timer->start(150);
}

void Widget::onMenuTriggered(QAction* act)
{
    QMetaEnum en = QMetaEnum::fromType<RoleAct>();

    bool flg;
    int role = en.keysToValue(act->text().toStdString().c_str(), &flg);

    if (!flg) return;
    this->changeActRole(static_cast<RoleAct>(role));
}

void Widget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    QPixmap pix;
    pix.load(this->m_current_pix.toLocalFile());

    painter.drawPixmap(100, 100, pix);

}

void Widget::contextMenuEvent(QContextMenuEvent* event)
{
    this->m_menu->popup(QCursor::pos());
}

void Widget::loadRoleActResources()
{
    std::function<void(RoleAct, QString, int)> func_pt = [this](RoleAct role, QString path, int count)
    {
        QList<QUrl> paths;

        char buffer[260];
        for (int i = 0; i < count; i++)
        {
            memset(buffer, 0, sizeof(buffer));
            sprintf_s(buffer, path.toStdString().c_str(), i + 1);
            paths.append(QUrl::fromLocalFile(buffer));
        }

        this->m_action.insert(role, paths);
    };

    func_pt(RoleAct::Normal, ":/normal/resources/normal/img_%d.png", 8);
    func_pt(RoleAct::Wink, ":/wink/resources/wink/img_%d.png", 8);
}

void Widget::initMenu()
{
    this->m_menu->addAction("Normal");
    this->m_menu->addAction("Wink");

    QAction* act = new QAction("隐藏");
    connect(act, &QAction::triggered, [this]()
            {
        this->setVisible(false);
    });

    this->m_menu->addAction(act);
    connect(this->m_menu, &QMenu::triggered, this, &Widget::onMenuTriggered);
}
