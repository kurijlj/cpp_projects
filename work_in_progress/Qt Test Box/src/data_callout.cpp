#include "data_callout.hpp"

#include <QtGui/QPainter>
#include <QtGui/QFontMetrics>
#include <QtWidgets/QGraphicsSceneMouseEvent>
#include <QtGui/QMouseEvent>
#include <QtCharts/QChart>

void DataCallout::message(const QString &text) {
    text_ = text;
    QFontMetrics metrics(font_);
    text_rect_ = metrics.boundingRect(
            QRect(0, 0, 150, 150),
            Qt::AlignLeft,
            text_
            );
    text_rect_.translate(5, 5);
    prepareGeometryChange();
    rect_ = text_rect_.adjusted(-5, -5, 5, 5);

}

void DataCallout::anchor(QPointF point) {
    anchor_ = point;

}

void DataCallout::updateGeometry() {
    prepareGeometryChange();
    setPos(chart_->mapToPosition(anchor_) + QPoint(10, -50));

}

QRectF DataCallout::boundingRect() const {
    QPointF apoint = mapFromParent(chart_->mapToPosition(anchor_));
    QRectF rect;

    rect.setLeft(qMin(rect_.left(), apoint.x()));
    rect.setRight(qMax(rect_.right(), apoint.x()));
    rect.setTop(qMin(rect_.top(), apoint.y()));
    rect.setBottom(qMax(rect_.bottom(), apoint.y()));

    return rect;
}

void DataCallout::paint(
        QPainter *painter,
        const QStyleOptionGraphicsItem *option,
        QWidget *widget
        ) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPainterPath path;
    path.addRect(rect_);
    // path.addRoundedRect(rect_, 5, 5);

    QPointF apoint = mapFromParent(chart_->mapToPosition(anchor_));
    if (!rect_.contains(apoint) && !anchor_.isNull()) {
        QPointF point1, point2;

        // establish the position of the anchor point in relation to rect_
        bool above = apoint.y() <= rect_.top();
        bool aboveCenter = apoint.y() > rect_.top()
            && apoint.y() <= rect_.center().y();
        bool belowCenter = apoint.y() > rect_.center().y()
            && apoint.y() <= rect_.bottom();
        bool below = apoint.y() > rect_.bottom();

        bool onLeft = apoint.x() <= rect_.left();
        bool leftOfCenter = apoint.x() > rect_.left()
            && apoint.x() <= rect_.center().x();
        bool rightOfCenter = apoint.x() > rect_.center().x()
            && apoint.x() <= rect_.right();
        bool onRight = apoint.x() > rect_.right();

        // get the nearest rect_ corner.
        qreal x = (onRight + rightOfCenter) * rect_.width();
        qreal y = (below + belowCenter) * rect_.height();
        bool cornerCase =
            (above && onLeft)
            || (above && onRight)
            || (below && onLeft)
            || (below && onRight);
        bool vertical = qAbs(apoint.x() - x) > qAbs(apoint.y() - y);

        qreal x1 = x + leftOfCenter * 10 - rightOfCenter * 20
            + cornerCase * !vertical * (onLeft * 10 - onRight * 20);
        qreal y1 = y + aboveCenter * 10 - belowCenter * 20
            + cornerCase * vertical * (above * 10 - below * 20);;
        point1.setX(x1);
        point1.setY(y1);

        qreal x2 = x + leftOfCenter * 20 - rightOfCenter * 10
            + cornerCase * !vertical * (onLeft * 20 - onRight * 10);;
        qreal y2 = y + aboveCenter * 20 - belowCenter * 10
            + cornerCase * vertical * (above * 20 - below * 10);;
        point2.setX(x2);
        point2.setY(y2);

        path.moveTo(point1);
        path.lineTo(apoint);
        path.lineTo(point2);
        path = path.simplified();

    }

    painter->setBrush(QColor(255, 255, 255));
    painter->drawPath(path);
    painter->drawText(text_rect_, text_);

}

void DataCallout::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    event->setAccepted(true);

}

void DataCallout::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton){
        setPos(mapToParent(
                    event->pos()
                    - event->buttonDownPos(Qt::LeftButton)
                    ));
        event->setAccepted(true);

    } else {
        event->setAccepted(false);

    }

}
