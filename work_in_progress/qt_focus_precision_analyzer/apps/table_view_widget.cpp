#include "table_view_widget.hpp"


TableViewWidget::TableViewWidget(QWidget *parent)
    : QWidget(parent)
{
    data_model_ = new DataModel(this);
    header_     = new CustomHeaderView(Qt::Horizontal, this);
    view_       = new QTableView(this);
    layout_     = new QVBoxLayout(this);

    view_->setHorizontalHeader(header_);
    view_->setModel(data_model_);
    view_->show();
    layout_->addWidget(view_);
    this->setLayout(layout_);
}


TableViewWidget::~TableViewWidget()
{
    delete header_;
    delete data_model_;
    delete view_;
    delete layout_;
}


void TableViewWidget::show()
{
    view_->resizeRowsToContents();
    view_->resizeColumnsToContents();
    QWidget::show();
}
