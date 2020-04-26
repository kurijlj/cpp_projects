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

#include "logreader.hpp"


// ============================================================================
// Utility functions and classes implementation
// ============================================================================


// ============================================================================
// Static members initialization
// ============================================================================

const unsigned int LogRead::log_header_len = 50;
const QByteArray LogRead::log_header = QByteArray::fromHex("53756e204e75636c65"
    "617220436f72706f726174696f6e0a504320456c656374726f6d65746572202d204c6f67"
    "2066696c65");
const QByteArray LogRead::msrmnt_header = QByteArray::fromHex("3d3d3d3d3d3d3d"
    "3d3d3d3d3d3d3d206e6577206d6561737572656d656e74203d3d3d3d3d3d3d3d3d3d3d3d"
    "3d3d");

// ============================================================================
// LogRead implementation
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
    char buffer[log_header_len];
    qint64 bytes_read;
    qint64 save_pos = file->pos();  // Save last position.

    file->seek(0);  // Reset file position to begininning of the file.
    if(file->atEnd()) {  // The file is empty.
        return is_log_valid = false;
    }

    bytes_read = file->read(buffer, log_header_len);
    if(log_header_len != bytes_read) {  // File is shorter than PCE Log header.
        return is_log_valid = false;
    }

    // Check if first fifty bytes of file match PCE Log header.
    QByteArray ba(buffer, log_header_len);
    if(log_header != ba) {
        return is_log_valid = false;  // No match.
    }

    file->seek(save_pos);  // Revert file position to the saved one.
    return true;
}

void LogRead::mapMeasurements()
{
    qint64 last_pos = 0;
    QTextStream content(file);

    QString line = content.readLine();
    while(!line.isNull()) {
        if(msrmnt_header == line.toAscii()) {
            measurements.append(++last_pos);
        }
        last_pos = content.pos();
        line = content.readLine();
    }
}

void LogRead::printMeasurementsMap()
{
    QTextStream qtcout(stdout);
    for(qint64 i=0; i<measurements.size(); i++) {
        qtcout << measurements[i] << " ";
    }
    qtcout << endl;
}

int LogRead::rowsRead()
{
    return rows_read;
}
