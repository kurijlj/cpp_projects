#include <iostream>

#include <QString>

#include "data_model.hpp"

DataModel::DataModel(QObject *parent) : QAbstractTableModel(parent)
{
    std::cout << "DataModel instance: Calling constructor.\n";

    data_ = static_cast<unsigned int>(42);

}


DataModel::~DataModel()
{
    std::cout << "DataModel instance: Calling destructor.\n";

}


int DataModel::rowCount(const QModelIndex & /*parent*/) const
{
    return static_cast<int>(1);

}


int DataModel::columnCount(const QModelIndex & /*parent*/) const
{
        return static_cast<int>(1);

}


QVariant DataModel::headerData(
        int section,
        Qt::Orientation orientation,
        int role
        ) const
{
    std::cout << "DataModel instance: Calling headerData.\n";

    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        if (section < this->columnCount()) {
            return QString("%1").arg(section);

        }

    } else if (role == Qt::DisplayRole && orientation == Qt::Vertical) {
        if (section < this->rowCount()) {
            return QString("%1").arg(section);

        }

    }

    return QVariant();
}


QVariant DataModel::data(const QModelIndex &index, int role) const
{
    std::cout << "DataModel instance: Calling data.\n";

    if (this->checkIndex(index)) {
        QString sval("");

        if (role == Qt::DisplayRole) {
            if (
                    static_cast<int>(index.column()) < this->columnCount()
                    && static_cast<int>(index.row()) < this->rowCount()
               )
                sval = QString("%1").arg(this->data_, 4, 10);

        }

        return sval;

    }

    return QVariant();

}


void DataModel::print() const
{
    std::cout << "DataModel instance: Calling print.\n";

}
