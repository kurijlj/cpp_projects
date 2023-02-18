// ============================================================================
//
// qt_test_box - Test if QObject instance does the proper clean up of attached
//               child instances
//
//  Copyright (C) 2023 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
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
// 2023-02-16 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
//
// * qt_test_box.cpp: created.
//
// ============================================================================


// ============================================================================
// Headers include section
// ============================================================================

// Qt Library headers
#include <QApplication>
#include <QtWidgets>

// Custom libraries headers
#include "../include/data_model.hpp"


// ============================================================================
// Main function definition
// ============================================================================

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget window;
    DataModel *m = new DataModel(&window);

    window.resize(320, 240);
    window.show();

    window.setWindowTitle(
        QApplication::translate("toplevel", "Top-level widget")
        );

    return app.exec();

}
