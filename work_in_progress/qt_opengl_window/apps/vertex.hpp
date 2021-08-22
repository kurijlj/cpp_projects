// ============================================================================
// qt_opengl_window - Window framework for rendering OpenGL scenes
//
//  Copyright (C) 2021 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
//
// This program is free software: you can redistribute it and/or modify
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
// 2021-08-21 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
//
// * vertex.hpp: created.
//
// ============================================================================


// ============================================================================
//
// References (this section should be deleted in the release version)
//
// * For coding style visit Google C++ Style Guide page at
//   <https://google.github.io/styleguide/cppguide.html>.
//
// * For introduction to OpenGL scene rendering visit tutorials list at
//   <https://www.trentreed.net/topics/opengl/>
//
// ============================================================================


#ifndef VERTEX_HPP
#define VERTEX_HPP

// ============================================================================
// Headers include section
// ============================================================================

// Standard Library headers

// Qt Library headers
#include <QVector3D>

// GUI headers

// Custom libraries headers


// ============================================================================
// Define Vertex class
// ============================================================================

///////////////////////////////////////////////////////////////////////////////
//
// class Vertex
//
// TODO: Put class description here
//
///////////////////////////////////////////////////////////////////////////////

class Vertex
{
public:
    // Constructors
    Vertex() {}
    explicit Vertex(const QVector3D &position) : position_(position) {}
    Vertex(const QVector3D &position, const QVector3D &color)
        : position_(position), color_(color) {}

    // Accessors / Mutators
    const QVector3D& position() const { return position_; }
    const QVector3D& color() const {return color_; }
    void setPosition(const QVector3D& position) { position_ = position; }
    void setColor(const QVector3D& color) { color_ = color; }

    // OpenGL Helpers
    static const int PositionTupleSize = 3;
    static const int ColorTupleSize = 3;
    static int positionOffset() { return offsetof(Vertex, position_); }
    static int colorOffset() { return offsetof(Vertex, color_); }
    static int stride() { return sizeof(Vertex); }

private:
    QVector3D position_;
    QVector3D color_;
};

#endif  // VERTEX_HPP
