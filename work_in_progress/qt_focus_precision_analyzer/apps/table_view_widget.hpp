#ifndef TABLEVIEWWIDGET_HPP
#define TABLEVIEWWIDGET_HPP

class TableViewWidget : public QWidget
{
    Q_OBJECT

private:
    // DataModel        *data_model_;
    // CustomHeaderView *header_;
    // QTableView       *table_view_;
    // QChart           *chart_;
    // QChartView       *chart_view_;
    // QGridLayout      *main_layout_;

protected:

public:
    TableViewWidget(
            QDate &log_date,
            QTime &log_time,
            QTextStream &src,
            QWidget *parent = nullptr
            );
        ~TableViewWidget() { };

};


#endif // TABLEVIEWWIDGET_HPP
