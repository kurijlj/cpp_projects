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

#ifndef DATA_MODEL_HPP
#define DATA_MODEL_HPP
#include <armadillo>
#include <deque>
#include <QAbstractTableModel>
#include <QColor>
#include <QDate>
#include <QMultiHash>
#include <QRect>
#include <QStringList>
#include <QTextStream>
#include <QTime>

struct FocusPrecisionReadout {
    arma::vec *x_frw_pos;
    arma::vec *x_frw_rdg;
    arma::vec *x_bck_pos;
    arma::vec *x_bck_rdg;
    arma::vec *y_frw_pos;
    arma::vec *y_frw_rdg;
    arma::vec *y_bck_pos;
    arma::vec *y_bck_rdg;
    arma::vec *z_frw_pos;
    arma::vec *z_frw_rdg;
    arma::vec *z_bck_pos;
    arma::vec *z_bck_rdg;
};

class DataModel : public QAbstractTableModel
{
    Q_OBJECT
private:
    QStringList data_titles_;
    QDate *log_date_;
    QTime *log_time_;
    QMultiHash<QString, QRect> *cell_color_map_;
    FocusPrecisionReadout *data_;

public:
    DataModel(QObject *parent = nullptr);
    DataModel(
            QDate &log_date,
            QTime &log_time,
            QTextStream &src,
            QObject *parent = nullptr
            );
    ~DataModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant headerData(
            int section,
            Qt::Orientation orientation,
            int role
            ) const override;
    QVariant data(
            const QModelIndex &index,
            int role = Qt::DisplayRole
            ) const override;
    void addCellColorMap(QString color, QRect area);
    void print() const;
};


#endif // DATA_MODEL_HPP
