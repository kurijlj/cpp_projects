#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QGridLayout>
#include <QTableView>
#include <QWidget>
#include <QtCharts/QLineSeries>
#include <QtCharts/QVXYModelMapper>

#include "table_view_widget.hpp"

#include "custom_header_view.hpp"
#include "data_model.hpp"

#include <iostream>

// QT_USE_NAMESPACE
using namespace QtCharts;

TableViewWidget::TableViewWidget(
        QDate &log_date,
        QTime &log_time,
        QTextStream &src,
        QWidget *parent
        ) : QWidget(parent)
{
    DataModel*        data_model_  = new DataModel(log_date, log_time, src, this);
    CustomHeaderView* header_      = new CustomHeaderView(Qt::Horizontal, this);
    QChart*           chart_       =  new QChart;
    QTableView*       table_view_  =  new QTableView(this);
    QChartView*       chart_view_  =  new QChartView(chart_);
    QGridLayout*      main_layout_ = new QGridLayout;

    std::cout << "Initialization over ...\n";

    table_view_->setModel(data_model_);

    std::cout << "Model set ...\n";

    table_view_->setHorizontalHeader(header_);

    std::cout << "Header set ...\n";

    table_view_->resizeRowsToContents();

    std::cout << "Row resize set ...\n";

    table_view_->resizeColumnsToContents();

    std::cout << "Column resize set ...\n";

    chart_->setAnimationOptions(QChart::AllAnimations);

    std::cout << "Initializing series X1 ...\n";

    QLineSeries *series = new QLineSeries;
    series->setName("X1");
    QVXYModelMapper *mapper = new QVXYModelMapper(this);
    mapper->setXColumn(0);
    mapper->setYColumn(1);
    mapper->setSeries(series);
    mapper->setModel(data_model_);
    chart_->addSeries(series);

    QString seriesColorHex = "#000000";

    seriesColorHex = "#" + QString::number(series->pen().color().rgb(), 16).right(6).toUpper();
    data_model_->addCellColorMap(seriesColorHex, QRect(0, 0, 2, data_model_->rowCount()));

    std::cout << "Initializing series X2 ...\n";

    series = new QLineSeries;
    series->setName("X2");

    mapper = new QVXYModelMapper(this);
    mapper->setXColumn(2);
    mapper->setYColumn(3);
    mapper->setSeries(series);
    mapper->setModel(data_model_);
    chart_->addSeries(series);

    seriesColorHex = "#" + QString::number(series->pen().color().rgb(), 16).right(6).toUpper();
    data_model_->addCellColorMap(seriesColorHex, QRect(2, 0, 2, data_model_->rowCount()));

    std::cout << "Initializing series Y1 ...\n";

    series = new QLineSeries;
    series->setName("Y1");

    mapper = new QVXYModelMapper(this);
    mapper->setXColumn(4);
    mapper->setYColumn(5);
    mapper->setSeries(series);
    mapper->setModel(data_model_);
    chart_->addSeries(series);

    seriesColorHex = "#" + QString::number(series->pen().color().rgb(), 16).right(6).toUpper();
    data_model_->addCellColorMap(seriesColorHex, QRect(2, 0, 2, data_model_->rowCount()));

    std::cout << "Initializing series Y2 ...\n";

    series = new QLineSeries;
    series->setName("Y2");

    mapper = new QVXYModelMapper(this);
    mapper->setXColumn(6);
    mapper->setYColumn(7);
    mapper->setSeries(series);
    mapper->setModel(data_model_);
    chart_->addSeries(series);

    seriesColorHex = "#" + QString::number(series->pen().color().rgb(), 16).right(6).toUpper();
    data_model_->addCellColorMap(seriesColorHex, QRect(2, 0, 2, data_model_->rowCount()));

    std::cout << "Initializing series Z1 ...\n";

    series = new QLineSeries;
    series->setName("Z1");

    mapper = new QVXYModelMapper(this);
    mapper->setXColumn(8);
    mapper->setYColumn(9);
    mapper->setSeries(series);
    mapper->setModel(data_model_);
    chart_->addSeries(series);

    seriesColorHex = "#" + QString::number(series->pen().color().rgb(), 16).right(6).toUpper();
    data_model_->addCellColorMap(seriesColorHex, QRect(2, 0, 2, data_model_->rowCount()));

    std::cout << "Initializing series Z2 ...\n";

    series = new QLineSeries;
    series->setName("Z2");

    mapper = new QVXYModelMapper(this);
    mapper->setXColumn(10);
    mapper->setYColumn(11);
    mapper->setSeries(series);
    mapper->setModel(data_model_);
    chart_->addSeries(series);

    seriesColorHex = "#" + QString::number(series->pen().color().rgb(), 16).right(6).toUpper();
    data_model_->addCellColorMap(seriesColorHex, QRect(2, 0, 2, data_model_->rowCount()));

    chart_->createDefaultAxes();
    chart_view_->setRenderHint(QPainter::Antialiasing);
    chart_view_->setMinimumSize(640, 480);

    main_layout_->addWidget(table_view_, 1, 0);
    main_layout_->addWidget(chart_view_, 1, 1);
    main_layout_->setColumnStretch(1, 1);
    main_layout_->setColumnStretch(0, 0);
    this->setLayout(main_layout_);
}


// TableViewWidget::~TableViewWidget()
// {
//     delete header_;
//     delete data_model_;
//     delete table_view_;
//     delete chart_;
//     delete chart_view_;
//     delete main_layout_;
// }
