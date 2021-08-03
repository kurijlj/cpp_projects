#include "custom_header_view.hpp"

#include <QCursor>
#include <QHoverEvent>
#include <QMenu>
#include <QPainter>


CustomHeaderView::CustomHeaderView(Qt::Orientation orientation, QWidget * parent)
    : QHeaderView(orientation, parent)
{
    // Required to refresh button menu when the mouse leave the header.
    setAttribute(Qt::WA_Hover, true);
}


void CustomHeaderView::mousePressEvent (QMouseEvent * event)
{
    QHeaderView::mousePressEvent(event);

    int logicalIndex = logicalIndexAt(event->pos());

    if (buttonMenuRect(logicalIndex).contains(event->pos())) {
        QMenu menu(this);
        QAction *copy = menu.addAction("Copy ...");

        QAction *res = menu.exec(mapToGlobal(event->pos()));

        if (res == copy) {
            // model()->copy(logicalIndex);
        }
    }

}


void CustomHeaderView::mouseMoveEvent(QMouseEvent * event)
{
    QHeaderView::mouseMoveEvent(event);

    // Required to refresh the button menu enable/disable state.
    int logicalIndex = logicalIndexAt(event->pos());
    updateSection(logicalIndex);
}


void CustomHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    painter->save();

    QHeaderView::paintSection(painter, rect, logicalIndex);

    painter->restore();

    if (!rect.isValid() || isSortIndicatorShown())
        return;

    QPoint pos = mapFromGlobal(QCursor::pos());
    if (rect.contains(pos)) {
        drawMenuButton(painter, logicalIndex, buttonMenuRect(logicalIndex).contains(pos));
    }
}


QRect CustomHeaderView::sectionRect(int logicalIndex) const
{
    return QRect(sectionViewportPosition(logicalIndex), 0, sectionSize(logicalIndex), height());
}


QRect CustomHeaderView::buttonMenuRect(int logicalIndex) const
{
    QRect sr = sectionRect(logicalIndex);

    return QRect(sr.right() - 5 - 13, sr.center().y() - 6, 13, 13);
}


void CustomHeaderView::drawMenuButton(QPainter *painter, int logicalIndex, bool enabled) const
{
    QRect brect = buttonMenuRect(logicalIndex);

    painter->setPen(enabled ? QColor(186,186,186) : QColor(223, 223, 223));
    painter->setBrush(QColor(246,246,246));
    painter->drawRect(brect.adjusted(0,0,-1,-1));

    painter->setPen(enabled ? QColor(71,71,71) : QColor(193, 193, 193));
    painter->drawLine(brect.left()+3, brect.top()+5, brect.right()-3, brect.top()+5);
    painter->drawLine(brect.left()+4, brect.top()+6, brect.right()-4, brect.top()+6);
    painter->drawLine(brect.left()+5, brect.top()+7, brect.right()-5, brect.top()+7);
    painter->drawPoint(brect.left()+6, brect.top()+8);
}


