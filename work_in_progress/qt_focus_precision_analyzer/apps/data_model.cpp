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

DataModel::DataModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    rows_ = 82;
    columns_ = 4;
    data_titles_ = QStringList({"X1 [mm]", "Y1 []", "X2 [mm]", "Y2 []"});
    data_ = std::deque<arma::vec*>(rows_);

    for (unsigned int i=0; i < columns_; i++) {
        data_.at(i) = new arma::vec(rows_, arma::fill::zeros);
    }

    for (unsigned int i=0; i < rows_; i++) {
        double X = (double) i;
        (*data_.at(0))(i) = (*data_.at(2))(i) = X;
        (*data_.at(1))(i) = sin(X);
        (*data_.at(3))(i) = cos(X);
    }
}


DataModel::~DataModel()
{
    for (unsigned int i=0; i < columns_; i++) {
        delete data_.at(i);
    }

}


int DataModel::rowCount(const QModelIndex & /*parent*/) const
{
   return rows_;
}


int DataModel::columnCount(const QModelIndex & /*parent*/) const
{
    return columns_;
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
        if (role == Qt::DisplayRole) {
            double val = (*data_.at(index.column()))(index.row());

            return QString("%1").arg(val, 8, 'f', 6);

        }

    }

    return QVariant();
}
