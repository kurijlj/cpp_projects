// ============================================================================
//
// GUI Application Framework using Qt and QPlainTextEdit widget
//
//  Copyright (C) 2021 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
//
// This code is derived from software released by Qt Company Ltd. under
// BSD-3-Clause license described below.
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


/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/


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
// * For command line arguments parsing using clipp consult documentation and
//   examples at <https://github.com/muellan/clipp>.
//
// * For filesystem operations (C++17) visit 'filesystem' reference at:
//   <https://en.cppreference.com/w/cpp/filesystem>.
//
// ============================================================================


// ============================================================================
// Headers include section
// ============================================================================

// Standard Library headers
#include <iostream>  // required by cin, cout
#include <sstream>   // required by ostringstream
#include <string>    // required by clipp for parsing unknown options
#include <vector>    // required by clipp for parsing unknown options

// Qt Library headers
#include <QApplication>
#include <QFileInfo>
#include <QString>
#include <QTextStream>

// GUI headers
#include "mainwindow.hpp"

// Custom libraries headers
#include <clipp.hpp>  // command line arguments parsing


// ============================================================================
// Global constants section
// ============================================================================

const QString kAppName {"Focus Precision Analyzer"};
const QString kVersionString {"0.1"};
const QString kYearString {"2021"};
const QString kAuthorName {"Ljubomir Kurij"};
const QString kAuthorEmail {"ljubomir_kurij@protonmail.com"};
const QString kAppDoc {
    "Application for inspecting and analyzing data from Focus Precision Test "
    "logs\n\n"
    "Mandatory arguments to long options are mandatory for short options too.\n"
};
const QString kLicense {
    "License GPLv3+: GNU GPL version 3 or later "
    "<http://gnu.org/licenses/gpl.html>\n"
    "This is free software: you are free to change and redistribute it.\n"
    "There is NO WARRANTY, to the extent permitted by law.\n"
};


// ============================================================================
// Global variables section
// ============================================================================

static QString exec_name = kAppName;


// ============================================================================
// Utility function prototypes
// ============================================================================

void printShortHelp(QString kAppName);
void printUsage(
        const clipp::group&,
        const QString = kAppName,
        const clipp::doc_formatting& = clipp::doc_formatting{}
    );
void printVersionInfo();
void showHelp(
        const clipp::group&,
        const QString = kAppName,
        const QString = kAppDoc
    );


// ============================================================================
// Main function definition
// ============================================================================

int main(int argc, char *argv[])
{
    QFileInfo exec_path(argv[0]);
    exec_name = exec_path.fileName();

    // Define structure to store command line option arguments
    struct CLIArguments {
        bool show_help;
        bool print_usage;
        bool show_version;
    };

    CLIArguments user_options {false, false, false};

    // Unsupported options aggregator.
    std::vector<std::string> unknown_options;

    // Option filters definitions
    auto istarget = clipp::match::prefix_not("-");

    // Set command line options
    auto cli = (
        // Must have more than one option
        // Take care not to omitt value filter when using
        // path input options
        (
            clipp::option("-h", "--help").set(user_options.show_help)
                .doc("show this help message and exit"),
            clipp::option("--usage").set(user_options.print_usage)
                .doc("give a short usage message"),
            clipp::option("-V", "--version").set(user_options.show_version)
                .doc("print program version")
        ).doc("general options:"),
        clipp::any_other(unknown_options)
    );

    // Parse command line options if any
    if(clipp::parse(argc, argv, cli) && unknown_options.empty()) {
        if(user_options.show_help) {
            showHelp(cli, exec_name);

            return EXIT_SUCCESS;
        }
        if(user_options.print_usage) {
            auto fmt = clipp::doc_formatting {}
                .first_column(0)
                .last_column(79);

            printUsage(cli, exec_name, fmt);

            return EXIT_SUCCESS;
        }
        if(user_options.show_version) {
            printVersionInfo();

            return EXIT_SUCCESS;
        }
    }

    // No command line options selected or application run from GUI. Proceed
    // to setting up GUI and running the application.

    Q_INIT_RESOURCE(app);

    QApplication app(argc, argv);

    QCoreApplication::setOrganizationName("Ljubomir Kurij");
    QCoreApplication::setApplicationName("Focus Precision Analyzer");
    QCoreApplication::setApplicationVersion(kVersionString);

    MainWindow main_win;

    main_win.show();
    return app.exec();
}


// ============================================================================
// Utility functions definitions
// ============================================================================

inline void printShortHelp(QString exec_name) {
    QTextStream(stdout) << "Try '" << exec_name
        << " --help' for more information.\n";
}


inline void printUsage(
        const clipp::group& group,
        const QString prefix,
        const clipp::doc_formatting& fmt)
{
    std::ostringstream ss;

    // clipp::usage_lines class require a stream to put its output to,
    // henceforth the workaround
    ss << clipp::usage_lines(group, prefix.toStdString(), fmt);
    QTextStream(stdout) << ss.str().c_str() << "\n";
}


void printVersionInfo() {
    QTextStream(stdout) << kAppName << " " << kVersionString
        << " Copyright (C) " << kYearString << " " << kAuthorName
        << "\n" << kLicense;

}


void showHelp(
        const clipp::group& group,
        const QString exec_name,
        const QString doc
        ) {
    auto fmt = clipp::doc_formatting {}.first_column(0).last_column(79);
    clipp::man_page man;
    std::ostringstream ss;

    man.prepend_section(
            "USAGE",
            clipp::usage_lines(group, exec_name.toStdString(), fmt).str()
            );
    man.append_section("", doc.toStdString());
    man.append_section("", clipp::documentation(group, fmt).str());
    man.append_section(
            "",
            "Report bugs to <" + kAuthorEmail.toStdString() + ">."
            );

    // clipp::man_page class require a stream to put its output to,
    // henceforth the workaround
    ss << man;
    QTextStream(stdout) << ss.str().c_str();
}
