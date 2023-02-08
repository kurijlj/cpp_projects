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

DataModel::DataModel(QObject *parent, const QString &file_name)
    : QAbstractTableModel(parent)
{
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
}


int DataModel::rowCount(const QModelIndex & /*parent*/) const
{
    arma::vec n = arma::vec(12, arma::fill::zeros);
    n(0)  = data_->x_frw_pos->n_elem();
    n(1)  = data_->x_frw_rdg->n_elem();
    n(2)  = data_->x_bck_pos->n_elem();
    n(3)  = data_->x_bck_rdg->n_elem();
    n(4)  = data_->y_frw_pos->n_elem();
    n(5)  = data_->y_frw_rdg->n_elem();
    n(6)  = data_->y_bck_pos->n_elem();
    n(7)  = data_->y_bck_rdg->n_elem();
    n(8)  = data_->z_frw_pos->n_elem();
    n(9)  = data_->z_frw_rdg->n_elem();
    n(10) = data_->z_bck_pos->n_elem();
    n(11) = data_->z_bck_rdg->n_elem();
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
        if (section < columns_) {
            return data_titles_.at(section);

        }

    } else if (role == Qt::DisplayRole && orientation == Qt::Vertical) {
        if (section < rows_) {
            return QString("%1").arg(section);

        }

    }

    return QVariant();
}


QVariant DataModel::data(const QModelIndex &index, int role) const
{
    if (checkIndex(index)) {
        double val = 0.0;

        if (role == Qt::DisplayRole) {
            switch (index.column()) {
                case 0:
                    val = data_->(*x_frw_pos)(index.row());
                    break;
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
            }
            double val = (*data_.at(index.column()))(index.row());

            return QString("%1").arg(val, 8, 'f', 6);

        }

    }

    return QVariant();
}
