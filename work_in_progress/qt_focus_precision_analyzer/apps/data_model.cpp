/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <cmath>
#include "data_model.hpp"

DataModel::DataModel(QObject *parent) : QAbstractTableModel(parent)
{
    QDate cd = QDate::currentDate();
    QTime ct = QTime::currentTime();
    log_date_ = new QDate(cd.year(), cd.month(), cd.day());
    log_time_ = new QTime(ct.hour(), ct.minute(), ct.second());
    data_titles_ = QStringList({
            "X_frw [mm]",
            "Ix_frw",
            "X_bck [mm]",
            "Ix_bck",
            "Y_frw [mm]",
            "Iy_frw",
            "Y_bck [mm]",
            "Iy_bck",
            "Z_frw [mm]",
            "Iz_frw",
            "Z_bck [mm]",
            "Iz_bck",
            });
    data_ = new FocusPrecisionReadout;
    data_->x_frw_pos = new arma::vec(1, arma::fill::zeros);
    data_->x_frw_rdg = new arma::vec(1, arma::fill::zeros);
    data_->x_bck_pos = new arma::vec(1, arma::fill::zeros);
    data_->x_bck_rdg = new arma::vec(1, arma::fill::zeros);
    data_->y_frw_pos = new arma::vec(1, arma::fill::zeros);
    data_->y_frw_rdg = new arma::vec(1, arma::fill::zeros);
    data_->y_bck_pos = new arma::vec(1, arma::fill::zeros);
    data_->y_bck_rdg = new arma::vec(1, arma::fill::zeros);
    data_->z_frw_pos = new arma::vec(1, arma::fill::zeros);
    data_->z_frw_rdg = new arma::vec(1, arma::fill::zeros);
    data_->z_bck_pos = new arma::vec(1, arma::fill::zeros);
    data_->z_bck_rdg = new arma::vec(1, arma::fill::zeros);
    cell_color_map_ = new  QMultiHash<QString, QRect>;
}


DataModel::DataModel(
        QDate &log_date,
        QTime &log_time,
        QTextStream &src,
        QObject *parent
        ) :
    log_date_(new QDate(log_date.year(), log_date.month(), log_date.day())),
    log_time_(new QTime(log_time.hour(), log_time.minute(), log_time.second())),
    QAbstractTableModel(parent)
{
    // Reset stream position to begining of the file
    src.seek(0);

    // Count the entries for each axis, and each run (forward and backward) ---
    unsigned int x_frw_n = 0;
    unsigned int x_bck_n = 0;
    unsigned int y_frw_n = 0;
    unsigned int y_bck_n = 0;
    unsigned int z_frw_n = 0;
    unsigned int z_bck_n = 0;

    while (!src.atEnd()) {
        QString line = src.readLine();
        QStringList fields = line.split(", ");

        if("\"X1-1\"" == fields.at(0)) {
            x_frw_n++;
        } else if("\"X1-2\"" == fields.at(0)) {
            x_bck_n++;
        } else if("\"Y1-1\"" == fields.at(0)) {
            y_frw_n++;
        } else if("\"Y1-2\"" == fields.at(0)) {
            y_bck_n++;
        } else if("\"Z1-1\"" == fields.at(0)) {
            z_frw_n++;
        } else if("\"Z1-2\"" == fields.at(0)) {
            z_bck_n++;
        }
    }

    // Allocate memory for storing data
    data_ = new FocusPrecisionReadout;
    data_->x_frw_pos = new arma::vec(x_frw_n, arma::fill::zeros);
    data_->x_frw_rdg = new arma::vec(x_frw_n, arma::fill::zeros);
    data_->x_bck_pos = new arma::vec(x_bck_n, arma::fill::zeros);
    data_->x_bck_rdg = new arma::vec(x_bck_n, arma::fill::zeros);
    data_->y_frw_pos = new arma::vec(y_frw_n, arma::fill::zeros);
    data_->y_frw_rdg = new arma::vec(y_frw_n, arma::fill::zeros);
    data_->y_bck_pos = new arma::vec(y_bck_n, arma::fill::zeros);
    data_->y_bck_rdg = new arma::vec(y_bck_n, arma::fill::zeros);
    data_->z_frw_pos = new arma::vec(z_frw_n, arma::fill::zeros);
    data_->z_frw_rdg = new arma::vec(z_frw_n, arma::fill::zeros);
    data_->z_bck_pos = new arma::vec(z_bck_n, arma::fill::zeros);
    data_->z_bck_rdg = new arma::vec(z_bck_n, arma::fill::zeros);

    // Reset stream position to begining of the file
    src.seek(0);

    // Reset counters
    x_frw_n = 0; x_bck_n = 0; y_frw_n = 0; y_bck_n = 0; z_frw_n = 0;
    z_bck_n = 0;

    // Read data from the file ------------------------------------------------
    while (!src.atEnd()) {
        QString line = src.readLine();
        QStringList fields = line.split(", ");

        // Verify row ID
        if("\"X1-1\"" == fields.at(0)) {
            (*data_->x_frw_pos)(x_frw_n) = fields.at(1).toDouble();
            (*data_->x_frw_rdg)(x_frw_n) = fields.at(4).toDouble();
            x_frw_n++;
        } else if("\"X1-2\"" == fields.at(0)) {
            (*data_->x_bck_pos)(x_bck_n) = fields.at(1).toDouble();
            (*data_->x_bck_rdg)(x_bck_n) = fields.at(4).toDouble();
            x_bck_n++;
        } else if("\"Y1-1\"" == fields.at(0)) {
            (*data_->y_frw_pos)(y_frw_n) = fields.at(2).toDouble();
            (*data_->y_frw_rdg)(y_frw_n) = fields.at(4).toDouble();
            y_frw_n++;
        } else if("\"Y1-2\"" == fields.at(0)) {
            (*data_->y_bck_pos)(y_bck_n) = fields.at(2).toDouble();
            (*data_->y_bck_rdg)(y_bck_n) = fields.at(4).toDouble();
            y_bck_n++;
        } else if("\"Z1-1\"" == fields.at(0)) {
            (*data_->z_frw_pos)(z_frw_n) = fields.at(3).toDouble();
            (*data_->z_frw_rdg)(z_frw_n) = fields.at(4).toDouble();
            z_frw_n++;
        } else if("\"Z1-2\"" == fields.at(0)) {
            (*data_->z_bck_pos)(z_bck_n) = fields.at(3).toDouble();
            (*data_->z_bck_rdg)(z_bck_n) = fields.at(4).toDouble();
            z_bck_n++;
        }
    }

    // Reverse data for the backward runs
    arma::vec *a;

    a = new arma::vec(arma::reverse(*data_->x_bck_pos));
    delete data_->x_bck_pos;
    data_->x_bck_pos = a;

    a = new arma::vec(arma::reverse(*data_->x_bck_rdg));
    delete data_->x_bck_rdg;
    data_->x_bck_rdg = a;

    a = new arma::vec(arma::reverse(*data_->y_bck_pos));
    delete data_->y_bck_pos;
    data_->y_bck_pos = a;

    a = new arma::vec(arma::reverse(*data_->y_bck_rdg));
    delete data_->y_bck_rdg;
    data_->y_bck_rdg = a;

    a = new arma::vec(arma::reverse(*data_->z_bck_pos));
    delete data_->z_bck_pos;
    data_->z_bck_pos = a;

    a = new arma::vec(arma::reverse(*data_->z_bck_rdg));
    delete data_->z_bck_rdg;
    data_->z_bck_rdg = a;

    cell_color_map_ = new  QMultiHash<QString, QRect>;
}


DataModel::~DataModel()
{
    delete data_->x_frw_pos;
    delete data_->x_frw_rdg;
    delete data_->x_bck_pos;
    delete data_->x_bck_rdg;
    delete data_->y_frw_pos;
    delete data_->y_frw_rdg;
    delete data_->y_bck_pos;
    delete data_->y_bck_rdg;
    delete data_->z_frw_pos;
    delete data_->z_frw_rdg;
    delete data_->z_bck_pos;
    delete data_->z_bck_rdg;
    delete data_;
    delete log_time_;
    delete log_date_;
    delete cell_color_map_;
}


int DataModel::rowCount(const QModelIndex & /*parent*/) const
{
    arma::vec n(12, arma::fill::zeros);
    n(0)  = data_->x_frw_pos->n_elem;
    n(1)  = data_->x_frw_rdg->n_elem;
    n(2)  = data_->x_bck_pos->n_elem;
    n(3)  = data_->x_bck_rdg->n_elem;
    n(4)  = data_->y_frw_pos->n_elem;
    n(5)  = data_->y_frw_rdg->n_elem;
    n(6)  = data_->y_bck_pos->n_elem;
    n(7)  = data_->y_bck_rdg->n_elem;
    n(8)  = data_->z_frw_pos->n_elem;
    n(9)  = data_->z_frw_rdg->n_elem;
    n(10) = data_->z_bck_pos->n_elem;
    n(11) = data_->z_bck_rdg->n_elem;
    return n.max();
}


int DataModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 12;
}


QVariant DataModel::headerData(
        int section,
        Qt::Orientation orientation,
        int role
        ) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        if (section < this->columnCount()) {
            return data_titles_.at(section);

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
    if (checkIndex(index)) {
        double val = 0.0;
        QString sval("");

        if (role == Qt::DisplayRole) {
            switch (index.column()) {
                case 0:
                    if(static_cast<unsigned long long>(index.row())
                            <= data_->x_frw_pos->n_elem - 1) {
                        val = (*data_->x_frw_pos)(index.row()) / 1000.0;
                        sval = QString("%1").arg(val, 8, 'f', 6);
                    }
                    break;
                case 1:
                    if(static_cast<unsigned long long>(index.row())
                            <= data_->x_frw_rdg->n_elem - 1) {
                        val = (*data_->x_frw_rdg)(index.row()) / 1000.0;
                        sval = QString("%1").arg(val, 8, 'f', 6);
                    }
                    break;
                case 2:
                    if(static_cast<unsigned long long>(index.row())
                            <= data_->x_bck_pos->n_elem - 1) {
                        val = (*data_->x_bck_pos)(index.row()) / 1000.0;
                        sval = QString("%1").arg(val, 8, 'f', 6);
                    }
                    break;
                case 3:
                    if(static_cast<unsigned long long>(index.row())
                            <= data_->x_bck_rdg->n_elem - 1) {
                        val = (*data_->x_bck_rdg)(index.row()) / 1000.0;
                        sval = QString("%1").arg(val, 8, 'f', 6);
                    }
                    break;
                case 4:
                    if(static_cast<unsigned long long>(index.row())
                            <= data_->y_frw_pos->n_elem - 1) {
                        val = (*data_->y_frw_pos)(index.row()) / 1000.0;
                        sval = QString("%1").arg(val, 8, 'f', 6);
                    }
                    break;
                case 5:
                    if(static_cast<unsigned long long>(index.row())
                            <= data_->y_frw_rdg->n_elem - 1) {
                        val = (*data_->y_frw_rdg)(index.row()) / 1000.0;
                        sval = QString("%1").arg(val, 8, 'f', 6);
                    }
                    break;
                case 6:
                    if(static_cast<unsigned long long>(index.row())
                            <= data_->y_bck_pos->n_elem - 1) {
                        val = (*data_->y_bck_pos)(index.row()) / 1000.0;
                        sval = QString("%1").arg(val, 8, 'f', 6);
                    }
                    break;
                case 7:
                    if(static_cast<unsigned long long>(index.row())
                            <= data_->y_bck_rdg->n_elem - 1) {
                        val = (*data_->y_bck_rdg)(index.row()) / 1000.0;
                        sval = QString("%1").arg(val, 8, 'f', 6);
                    }
                    break;
                case 8:
                    if(static_cast<unsigned long long>(index.row())
                            <= data_->z_frw_pos->n_elem - 1) {
                        val = (*data_->z_frw_pos)(index.row()) / 1000.0;
                        sval = QString("%1").arg(val, 8, 'f', 6);
                    }
                    break;
                case 9:
                    if(static_cast<unsigned long long>(index.row())
                            <= data_->z_frw_rdg->n_elem - 1) {
                        val = (*data_->z_frw_rdg)(index.row()) / 1000.0;
                        sval = QString("%1").arg(val, 8, 'f', 6);
                    }
                    break;
                case 10:
                    if(static_cast<unsigned long long>(index.row())
                            <= data_->z_bck_pos->n_elem - 1) {
                        val = (*data_->z_bck_pos)(index.row()) / 1000.0;
                        sval = QString("%1").arg(val, 8, 'f', 6);
                    }
                    break;
                case 11:
                    if(static_cast<unsigned long long>(index.row())
                            <= data_->z_bck_rdg->n_elem - 1) {
                        val = (*data_->z_bck_rdg)(index.row()) / 1000.0;
                        sval = QString("%1").arg(val, 8, 'f', 6);
                    }
                    break;
            }

            return sval;

        } else if (role == Qt::BackgroundRole) {
            for (const QRect &rect : *cell_color_map_) {
                if (rect.contains(index.column(), index.row()))
                    return QColor(cell_color_map_->key(rect));
            }

            // cell not mapped return white color
            return QColor(Qt::white);
        }

    }

    return QVariant();
}


void DataModel::addCellColorMap(QString color, QRect area)
{
    cell_color_map_->insert(color, area);
}


void DataModel::print() const
{
    double v1, v2;

    std::cout << log_date_->toString("d. MMMM yyyy").toStdString() << " " <<
        log_time_->toString("h:mm:ss").toStdString() << std::endl;

    for(
            unsigned long long i = 0;
            i < static_cast<unsigned long long>(this->rowCount());
            i++
            ) {
        std::cout << i << ":\t";
        if(i <= data_->x_frw_pos->n_elem - 1) {
            v1 = (*data_->x_frw_pos)(i);
            v2 = (*data_->x_frw_rdg)(i);
            std::cout << v1 << "\t" << v2 << "\t";
        } else {
            std::cout << "\t\t";
        }
        if(i <= data_->x_bck_pos->n_elem - 1) {
            v1 = (*data_->x_bck_pos)(i);
            v2 = (*data_->x_bck_rdg)(i);
            std::cout << v1 << "\t" << v2 << "\t";
        } else {
            std::cout << "\t\t";
        }
        if(i <= data_->y_frw_pos->n_elem - 1) {
            v1 = (*data_->y_frw_pos)(i);
            v2 = (*data_->y_frw_rdg)(i);
            std::cout << v1 << "\t" << v2 << "\t";
        } else {
            std::cout << "\t\t";
        }
        if(i <= data_->y_bck_pos->n_elem - 1) {
            v1 = (*data_->y_bck_pos)(i);
            v2 = (*data_->y_bck_rdg)(i);
            std::cout << v1 << "\t" << v2 << "\t";
        } else {
            std::cout << "\t\t";
        }
        if(i <= data_->z_frw_pos->n_elem - 1) {
            v1 = (*data_->z_frw_pos)(i);
            v2 = (*data_->z_frw_rdg)(i);
            std::cout << v1 << "\t" << v2 << "\t";
        } else {
            std::cout << "\t\t";
        }
        if(i <= data_->z_bck_pos->n_elem - 1) {
            v1 = (*data_->z_bck_pos)(i);
            v2 = (*data_->z_bck_rdg)(i);
            std::cout << v1 << "\t" << v2 << "\t";
        } else {
            std::cout << "\t\t";
        }

        std::cout << std::endl;
    }
}
