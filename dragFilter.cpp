#include "dragFilter.h"

bool DragFilter::eventFilter(QObject *obj, QEvent *event)
{
    QWidget* w = dynamic_cast<QWidget*>(obj);
    if (!w) return false;

    if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent* e = dynamic_cast<QMouseEvent*>(event);

        if (e) this->m_position = e->pos();
    }
    else if (event->type() == QEvent::MouseMove)
    {
        QMouseEvent* e = dynamic_cast<QMouseEvent*>(event);

        if (e && e->buttons() && Qt::MouseButton::LeftButton) w->move(e->globalPosition().toPoint() - this->m_position);
    }

    return QObject::eventFilter(obj, event);
}
