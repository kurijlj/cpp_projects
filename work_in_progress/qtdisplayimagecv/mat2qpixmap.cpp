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

// ============================================================================
// Headers include section
// ============================================================================

#include "mat2qpixmap.hpp"


// ============================================================================
// Mat2QPixmap Implementation
// ============================================================================

m2qp::Mat2QPixmap::Mat2QPixmap(int cvt_code, QImage::Format cvt_fmt)
{
    cvt_code_ = cvt_code;
    cvt_fmt_ = cvt_fmt;
}

int m2qp::Mat2QPixmap::cvt_code()
{
    return cvt_code_;
}

QImage::Format m2qp::Mat2QPixmap::cvt_fmt()
{
    return cvt_fmt_;
}

int m2qp::Mat2QPixmap::change_cvt_code(int new_cvt_code)
{
    return cvt_code_ = new_cvt_code;
}

QImage::Format m2qp::Mat2QPixmap::change_cvt_flags(QImage::Format new_cvt_fmt)
{
    return cvt_fmt_ = new_cvt_fmt;
}

QPixmap m2qp::Mat2QPixmap::convert(cv::InputArray src)
{
    cv::Mat rgb_src;
    QPixmap src_pxm;

    cv::cvtColor(src, rgb_src, cvt_code_);
    src_pxm = QPixmap::fromImage(QImage(
            (unsigned char *) rgb_src.data,
            rgb_src.cols,
            rgb_src.rows,
            rgb_src.step,
            cvt_fmt_
        ));

    return src_pxm.copy();
}
