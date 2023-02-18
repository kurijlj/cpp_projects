#include "custom_graph_view.hpp"

#include <QtGui/QMouseEvent>
#include <QtGui/QResizeEvent>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsTextItem>

#include "data_callout.hpp"

CustomGraphView::CustomGraphView(QWidget *parent)
    : QGraphicsView(parent),
      coord_x_(nullptr),
      coord_y_(nullptr),
      graph_(nullptr),
      dc_(nullptr) {
    setDragMode(QGraphicsView::NoDrag);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setRenderHint(QPainter::Antialiasing);
    setMouseTracking(true);

}

void CustomGraphView::setGraph(QChart *graph) {
    if(nullptr != graph) {
        graph_ = graph;
        scene()->addItem(graph);
        coord_x_ = new QGraphicsSimpleTextItem(graph_);
        coord_x_->setPos(graph_->size().width()/2 - 50, graph_->size().height());
        coord_x_->setText("X: ");
        coord_y_ = new QGraphicsSimpleTextItem(graph_);
        coord_y_->setPos(graph_->size().width()/2 + 50, graph_->size().height());
        coord_y_->setText("Y: ");

    }

}

void CustomGraphView::resizeEvent(QResizeEvent *event) {
    if (scene()) {
        scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
         graph_->resize(event->size());
         coord_x_->setPos(graph_->size().width()/2 - 50, graph_->size().height() - 20);
         coord_y_->setPos(graph_->size().width()/2 + 50, graph_->size().height() - 20);
         const auto callouts = saved_dcs_;
         for (DataCallout *callout : callouts) {
             callout->updateGeometry();

         }

    }

    QGraphicsView::resizeEvent(event);

}

void CustomGraphView::mouseMoveEvent(QMouseEvent *event) {
    coord_x_->setText(QString("X: %1").arg(graph_->mapToValue(event->pos()).x()));
    coord_y_->setText(QString("Y: %1").arg(graph_->mapToValue(event->pos()).y()));
    QGraphicsView::mouseMoveEvent(event);

}

void CustomGraphView::save_callout() {
    saved_dcs_.append(dc_);
    dc_ = new DataCallout(graph_);

}

void CustomGraphView::callout(QPointF point, bool state) {
    if (dc_ == 0) {
        dc_ = new DataCallout(graph_);

    }

    if (state) {
        dc_->message(QString("X: %1 \nY: %2 ").arg(point.x()).arg(point.y()));
        dc_->anchor(point);
        dc_->setZValue(11);
        dc_->updateGeometry();
        dc_->show();

    } else {
        dc_->hide();

    }

}
