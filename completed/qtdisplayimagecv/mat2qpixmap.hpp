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
// 2020-05-17 Ljubomir Kurij <kurijlj@mail.com>
//
// * mat2pixmap.hpp: created.
//
// ============================================================================


#ifndef MAT2QPIXMAP_HPP
#define MAT2QPIXMAP_HPP


// ============================================================================
// Headers include section
// ============================================================================

#include <QImage>
#include <QPixmap>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>


// ============================================================================
// Mat2QPixmap Definition
// ============================================================================

namespace m2qp {

    class Mat2QPixmap {
    public:

        // Class constructors and destructors.
        Mat2QPixmap(
                int cvt_code = cv::COLOR_BGR2RGB,
                QImage::Format cvt_fmt = QImage::Format_RGB888
            );

        // Attributes accessors.
        int cvt_code();
        QImage::Format cvt_fmt();

        // Attributes mutators.
        int change_cvt_code(int new_cvt_code);
        QImage::Format change_cvt_flags(QImage::Format new_cvt_fmt);

        // Method holding algorithm for conversion from cv::Mat to Qt::QPixmap.
        QPixmap convert(cv::InputArray src);

    private:
        int cvt_code_;  // Holds color conversion code from cv library used to
                        // convert image from BGR color scheme to a color
                        // scheme sompatible with QImage colors.

        QImage::Format cvt_fmt_;  // Holds destination image format for array
                                  // data to be converted to.
    };

}

#endif
