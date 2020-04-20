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
// * logreader.cpp: created.
//
// ============================================================================


// ============================================================================
//
// TODO:
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


// ============================================================================
// Headers include section
// ============================================================================

#include <QObject>
#include <QDebug>
#include <QString>
#include <QFile>
#include <QByteArray>
#include <QTextStream>
#include "logreader.hpp"


// ============================================================================
// LogRead Implementation
// ============================================================================

LogRead::LogRead(const QString fn, QObject *parent) :
    QObject(parent)
{
    file = new QFile(fn);
    is_log_valid = true;
    rows_read = 0;

    if(!file->open(QIODevice::ReadOnly)) {
        is_log_valid = false;
        qWarning() << "Unable to open file: " << file->fileName();
    }
}

LogRead::~LogRead()
{
    file->close();
    delete file;
}

void LogRead::LogRead::read()
{
    QTextStream stream(file);
    QString row = stream.readLine();
    while(!row.isNull()) {
        rows_read++;
        row = stream.readLine();
    }
}

bool LogRead::isLogValid()
{
    return is_log_valid;
}

bool LogRead::checkLogHeader()
{
    char buffer[50];
    bool result = true;
    qint64 bytes_read;
    qint64 save_pos = file->pos();  // Save last position.

    file->seek(0);  // Reset file position to begininning of the file.
    if(file->atEnd()) {
        result = false;
        return is_log_valid = result;
    }

    bytes_read = file->read(buffer, sizeof(buffer));
    if(sizeof(buffer) != bytes_read) {
        result = false;
        return is_log_valid = result;
    }

    for (int i=0; i<sizeof(buffer); i++) {
        qDebug("%c", buffer[i]);
    }
    qDebug("\n");

    file->seek(save_pos);  // Revert file position to the saved.
    return result;
}

int LogRead::rowsRead()
{
    return rows_read;
}
