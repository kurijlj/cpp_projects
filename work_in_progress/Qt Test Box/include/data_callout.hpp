#ifndef DATA_CALLOUT_HPP
#define DATA_CALLOUT_HPP

#include <QtCharts/QChart>
#include <QtGui/QFont>
#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QGraphicsSceneMouseEvent>

using namespace QtCharts;

class DataCallout : public QGraphicsItem
{
private:
    QString text_;
    QRectF  text_rect_;
    QRectF  rect_;
    QPointF anchor_;
    QFont   font_;       // Set font to app default
    QChart  *chart_;

public:
    DataCallout(QChart *parent) : QGraphicsItem(parent), chart_(parent) { };
    ~DataCallout() { };

    void message(const QString &text);
    void anchor(QPointF point);
    void updateGeometry();

    QRectF boundingRect() const;
    void paint(
            QPainter *painter,
            const QStyleOptionGraphicsItem *option,
            QWidget *widget
            );

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

};

#endif  // DATA_CALLOUT_H
