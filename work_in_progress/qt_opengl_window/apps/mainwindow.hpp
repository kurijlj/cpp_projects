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
// * mainwindow.hpp: created.
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


#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

// ============================================================================
// Headers include section
// ============================================================================

// Standard Library headers

// Qt Library headers
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWindow>

// GUI headers

// Custom libraries headers


// ============================================================================
// Define namespace aliases
// ============================================================================


// ============================================================================
// Forward declarations
// ============================================================================

class QOpenGLShaderProgram;


// ============================================================================
// Define main window class
// ============================================================================

///////////////////////////////////////////////////////////////////////////////
//
// class MainWindow
//
// TODO: Put class description here
//
///////////////////////////////////////////////////////////////////////////////

class MainWindow : public QOpenGLWindow,
                   protected QOpenGLFunctions
{
    Q_OBJECT
        //
// OpenGL Events
public:
    ~MainWindow();

    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void teardownGL();

private:
    // OpenGL State Information
    QOpenGLBuffer vertex_;
    QOpenGLVertexArrayObject object_;
    QOpenGLShaderProgram *program_;

    // Private Helpers
    void printContextInformation();
};

#endif  // MAINWINDOW_HPP
