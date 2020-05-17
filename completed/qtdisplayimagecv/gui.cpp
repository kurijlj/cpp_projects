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
// * gui.cpp: created.
//
// ============================================================================


// ============================================================================
//
// TODO:
//
// * Reconsider using EXIT_SUCCESS and EXIT_FAILURE as method exit statuses.
//
// ============================================================================


// ============================================================================
// Headers include section
// ============================================================================

#include "gui.hpp"
#include "ui_MainWindow.h"


// ============================================================================
// MainWindow Implementation
// ============================================================================

MainWindow::MainWindow(QWidget *parent, const QString & exec_name)
    : QDialog(parent),
    ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);

    exec_name_ = exec_name;
    setWindowTitle(exec_name);
    ui_->plot->replot();
}

int MainWindow::showImage(const QString & image_file)
{
    QTextStream out_(stdout, QIODevice::WriteOnly);
    QTextStream err_(stderr, QIODevice::WriteOnly);
    cv::Mat img;
    m2qp::Mat2QPixmap converter(cv::COLOR_BGR2RGB, QImage::Format_RGB888);

    out_ <<  exec_name_ << ": Image file \"" << image_file << "\".\n";
    out_ <<  exec_name_ << ": Loading image data.\n" << flush;
    img = cv::imread(image_file.toLatin1().constData(), cv::IMREAD_COLOR);

    if(img.empty())
    {
        err_ <<  exec_name_ << ": Could not find image data.\n" << flush;
        return EXIT_FAILURE;
    }

    setWindowTitle(image_file);
    ui_->plot->axisRect()->setBackground(converter.convert(img));
    ui_->plot->replot();

    return EXIT_SUCCESS;
}
