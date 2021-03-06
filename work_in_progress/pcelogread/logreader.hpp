// ============================================================================
// Copyright (C) <yyyy> <Author Name> <author@mail.com>
//
// This file is part of <program name>.
//
// <program name> is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
// ============================================================================


// ============================================================================
//
// <Put documentation here>
//
//
// 2020-04-19 Ljubomir Kurij <kurijlj@mail.com>
//
// * logreader.hpp: created.
//
// ============================================================================


// ============================================================================
//
// TODO:
//
// * create class constant holding log file header
//
// ============================================================================


// ============================================================================
//
// References (this section should be deleted in the release version)
//
// * For coding style visit Google C++ Style Guide page at
//   <https://google.github.io/styleguide/cppguide.html>.
//
// ============================================================================


#ifndef LOGREADER_H
#define LOGREADER_H


// ============================================================================
// Headers include section
// ============================================================================

#include <QFile>
#include <QChar>
#include <QDebug>
#include <QVector>
#include <QString>
#include <QObject>
#include <QByteArray>
#include <QTextStream>


// ============================================================================
// Utility functions and classes definition
// ============================================================================


// ============================================================================
// LogRead class definition
// ============================================================================

class LogRead : public QObject
{
    Q_OBJECT

public:
    explicit LogRead(const QString fn, QObject *parent = nullptr);
    ~LogRead();
    void read();
    bool isLogValid();
    bool checkLogHeader();
    void mapMeasurements();
    void printMeasurementsMap();
    int rowsRead();

private:
    QFile *file;
    QVector<qint64> measurements;
    bool is_log_valid;
    qint64 rows_read;

    static const unsigned int log_header_len;
    static const QByteArray log_header;
    static const QByteArray msrmnt_header;
};

#endif
