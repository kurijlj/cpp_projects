// ============================================================================
// Copyright (C) 2020 Ljubomir Kurij <kurijlj@gmail.com>
//
// This file is part of qtdisplayimagecv.
//
// qtdisplayimagecv is free software: you can redistribute it and/or modify
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
// 2020-05-10 Ljubomir Kurij <kurijlj@mail.com>
//
// * gui.hpp: created.
//
// ============================================================================


#ifndef GUI_HPP
#define GUI_HPP


// ============================================================================
// Headers include section
// ============================================================================

#include <QDialog>
#include <QString>
#include <QPixmap>
#include <QTextStream>
#include <cstdlib>  // required by EXIT_SUCCESS, EXIT_FAILURE
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "mat2qpixmap.hpp"


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
    MainWindow(
            QWidget *parent = nullptr,
            const QString & exec_name = "Qt Display Image (OpenCV)"
        );
    int showImage(const QString & image_file);

private:
    Ui::MainWindow *ui_;
    QString exec_name_;
};

#endif
