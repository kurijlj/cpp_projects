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
// 2020-04-15 Ljubomir Kurij <kurijlj@mail.com>
//
// * gui.cpp: created.
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

#include <QtGui>
#include <QStringList>
#include <QStringListModel>
#include "gui.hpp"
#include "ui_MainWindow.h"


// ============================================================================
// MainWindow Implementation
// ============================================================================

MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList list;
    model = new QStringListModel(this);
    list << "Hello" << "World" << "There";
    model->setStringList(list);
    ui->data_view->setModel(model);
    ui->data_view->setEditTriggers(
            QAbstractItemView::AnyKeyPressed |
            QAbstractItemView::DoubleClicked
        );
}
