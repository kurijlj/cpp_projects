// ============================================================================
//
// <Put documentation here>
//
// <yyyy>-<mm>-<dd> <Author Name> <author@mail.com>
//
// * <programfilename>.cpp: created.
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
#include <QtWidgets>

// GUI headers

// Custom libraries headers
#include "data_model.hpp"


// ============================================================================
// Global constants section
// ============================================================================

//
// ============================================================================
// Global variables section
// ============================================================================


// ============================================================================
// Utility function prototypes
// ============================================================================


// ============================================================================
// Main function definition
// ============================================================================

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget window;
    DataModel *m = new DataModel();

    window.resize(320, 240);
    window.show();

    window.setWindowTitle(
        QApplication::translate("toplevel", "Top-level widget")
        );

    return app.exec();

}


// ============================================================================
// Utility functions definitions
// ============================================================================

