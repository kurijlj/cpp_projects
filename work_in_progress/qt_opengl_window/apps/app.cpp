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
// * app.cpp: created.
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

// Standard Library headers

// Qt Library headers
#include <QApplication>

// GUI headers
#include "mainwindow.hpp"

// Custom libraries headers


// ============================================================================
// Main function definition
// ============================================================================

int main(int argc, char *argv[])
{
    // Q_INIT_RESOURCE(app);

    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("Corsairs");
    QCoreApplication::setApplicationName("OpenGL Window Framework");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);

    // Set OpenGL Version information
    // Note: This format must be set before show() is called.
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(3,3);

    // Set the window up
    MainWindow window;
    window.setFormat(format);
    window.resize(QSize(800, 600));
    window.show();

    return app.exec();
}
