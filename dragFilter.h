#ifndef DRAGFILTER_H
#define DRAGFILTER_H

#include <QWidget>
#include <QEvent>
#include <QPoint>
#include <QMouseEvent>

class DragFilter : public QObject
{
public:

    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    QPoint m_position;

};

#endif // DRAGFILTER_H
