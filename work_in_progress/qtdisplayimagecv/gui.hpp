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


#ifndef GUI_H
#define GUI_H


// ============================================================================
// Headers include section
// ============================================================================

#include <QDialog>


// ============================================================================
// Namespace Definition
// ============================================================================

namespace Ui {
    class MainWindow;
}


// ============================================================================
// MainWindow Definition
// ============================================================================

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    Ui::MainWindow *ui;
};

#endif
