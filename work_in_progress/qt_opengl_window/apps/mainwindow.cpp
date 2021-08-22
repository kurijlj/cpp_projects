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
// * mainwindow.cpp: created.
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

// Related header
#include "mainwindow.hpp"

// Standard Library headers

// Qt Library headers
#include <QDebug>
#include <QOpenGLShaderProgram>
#include <QString>

// GUI headers
#include "vertex.hpp"

// Custom libraries headers


// ============================================================================
// OpenGL Scene Setu Up
// ============================================================================

// Create a colored triangle
static const Vertex sg_vertexes[] = {
    Vertex( QVector3D( 0.00f,  0.75f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f) ),
    Vertex( QVector3D( 0.75f, -0.75f, 1.0f), QVector3D(0.0f, 1.0f, 0.0f) ),
    Vertex( QVector3D(-0.75f, -0.75f, 1.0f), QVector3D(0.0f, 0.0f, 1.0f) )
};


// ============================================================================
// Constructors and Destrucors section
// ============================================================================

MainWindow::~MainWindow()
{
    makeCurrent();
    teardownGL();
}


// ============================================================================
// OpenGL Events
// ============================================================================

void MainWindow::initializeGL()
{
    // Initialize OpenGL Backend
    initializeOpenGLFunctions();
    printContextInformation();

    // Set global information
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Application-specific initialization
    {
        // Create Shader (Do not release until VAO is created)
        program_ = new QOpenGLShaderProgram();
        program_->addShaderFromSourceFile(
                QOpenGLShader::Vertex,
                "./shaders/simple.vrt"
                );
        program_->addShaderFromSourceFile(
                QOpenGLShader::Fragment,
                "./shaders/simple.frg"
                );
        program_->link();
        program_->bind();

        // Create Buffer (Do not release until VAO is created)
        vertex_.create();
        vertex_.bind();
        vertex_.setUsagePattern(QOpenGLBuffer::StaticDraw);
        vertex_.allocate(sg_vertexes, sizeof(sg_vertexes));

        // Create Vertex Array Object
        object_.create();
        object_.bind();
        program_->enableAttributeArray(0);
        program_->enableAttributeArray(1);
        program_->setAttributeBuffer(
                0,
                GL_FLOAT,
                Vertex::positionOffset(),
                Vertex::PositionTupleSize,
                Vertex::stride()
                );
        program_->setAttributeBuffer(
                1,
                GL_FLOAT,
                Vertex::colorOffset(),
                Vertex::ColorTupleSize,
                Vertex::stride()
                );

        // Release (unbind) all
        object_.release();
        vertex_.release();
        program_->release();
    }
}

void MainWindow::resizeGL(int width, int height)
{
    // Currently we are not handling width/height changes
    (void)width;
    (void)height;
}

void MainWindow::paintGL()
{
    // Clear
    glClear(GL_COLOR_BUFFER_BIT);

    // Render using our shader
    program_->bind();
    {
        object_.bind();
        glDrawArrays(
                GL_TRIANGLES,
                0,
                sizeof(sg_vertexes) / sizeof(sg_vertexes[0])
                );
        object_.release();
    }
    program_->release();
}

void MainWindow::teardownGL()
{
    // Actually destroy our OpenGL information
    object_.destroy();
    vertex_.destroy();
    delete program_;
}


// ============================================================================
// Private Helpers
// ============================================================================

void MainWindow::printContextInformation()
{
    QString glType;
    QString glVersion;
    QString glProfile;

    // Get Version Information
    glType = (context()->isOpenGLES()) ? "OpenGL ES" : "OpenGL";
    glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

    // Get Profile Information
#define CASE(c) case QSurfaceFormat::c: glProfile = #c; break
    switch (format().profile())
    {
        CASE(NoProfile);
        CASE(CoreProfile);
        CASE(CompatibilityProfile);
    }
#undef CASE

    // qPrintable() will print our QString w/o quotes around it.
    qDebug() << qPrintable(glType) << qPrintable(glVersion)
        << "(" << qPrintable(glProfile) << ")";
}
