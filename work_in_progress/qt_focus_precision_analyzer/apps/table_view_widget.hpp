#ifndef TABLEVIEWWIDGET_HPP
#define TABLEVIEWWIDGET_HPP

#include <QTableView>
#include <QVBoxLayout>
#include <QWidget>

#include "custom_header_view.hpp"
#include "data_model.hpp"

class TableViewWidget : public QWidget
{
    Q_OBJECT

private:
    DataModel*        data_model_;
    CustomHeaderView* header_;
    QTableView*       view_;
    QVBoxLayout*      layout_;

protected:

public:
        TableViewWidget(QWidget *parent = nullptr);
        ~TableViewWidget();

        void show();

};


#endif // TABLEVIEWWIDGET_HPP
