#ifndef CUSTOM_GRAPH_VIEW_HPP
#define CUSTOM_GRAPH_VIEW_HPP

#include <QtWidgets/QGraphicsView>
#include <QtCharts/QChart>

#include "data_callout.hpp"

// using namespace QGraphicsScene;
// using namespace QMouseEvent;
// using namespace QResizeEvent;
using namespace QtCharts;

class CustomGraphView: public QGraphicsView
{
private:
    Q_OBJECT
    QGraphicsSimpleTextItem *coord_x_;
    QGraphicsSimpleTextItem *coord_y_;
    QChart                  *graph_;
    DataCallout             *dc_;
    QList<DataCallout *>    saved_dcs_;

public:
    CustomGraphView(QWidget *parent = 0);
    void setGraph(QChart *graph);

protected:
    void resizeEvent(QResizeEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

public slots:
    void save_callout();
    void callout(QPointF point, bool state);

};

#endif  // CUSTOM_GRAPH_VIEW_Hpp
