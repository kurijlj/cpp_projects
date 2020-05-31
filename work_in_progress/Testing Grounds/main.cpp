// ============================================================================
// Copyright (C) 2020 Ljubomir Kurij <kurijlj@gmail.com>
//
// This file is part of mda (Measurement Data Analytics).
//
// <program name> is free software: you can redistribute it and/or modify
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
// 2020-05-23 Ljubomir Kurij <kurijlj@gmail.com>
//
// * main.cpp: created.
//
// ============================================================================


// ============================================================================
//
// TODO:
//
// * Add support for some common Qt App command line arguments.
//
// ============================================================================


// ============================================================================
//
// References (this section should be deleted in the release version)
//
// * For coding style visit Google C++ Style Guide page at
//   <https://google.github.io/styleguide/cppguide.html>.
//
// * For command line arguments parsing using Boost program_options library
//   consult manual at <https://www.boost.org/doc/libs/1_49_0/doc/html/
//   program_options.html>.
//
// ============================================================================


// ============================================================================
// Headers include section
// ============================================================================

// Standard Library Headers
#include <string>  // self explanatory ...
#include <cstdlib>  // required by EXIT_SUCCESS, EXIT_FAILURE
#include <iostream>  // required by cin, cout, ...

// Qt Library Headers
#include <QString>  // required for formatting output
#include <QVarLengthArray>  // self explanatory ...

// Boost Library Headers
#include <boost/program_options.hpp>  // self explanatory ...


// ============================================================================
// Define namespace aliases
// ============================================================================

namespace ap = boost::program_options;  // 'ap' as arguments parsing


// ============================================================================
// Global constants section
// ============================================================================

const std::string kAppName = "mda";
const std::string kVersionString = "0.1";
const std::string kYearString = "2020";
const std::string kAuthorName = "Ljubomir Kurij";
const std::string kAuthorEmail = "kurijlj@gmail.com";
const char kPathSeparator = '/';


// ============================================================================
// Global variables section
// ============================================================================

static std::string exec_name = kAppName;


// ============================================================================
// Utility function prototypes
// ============================================================================

void PrintUsage();
void PrintShortHelp();
void PrintPositionalArgumentsHelp();
void PrintReportBugsTo();
void PrintVersionInfo();


// ============================================================================
// App's main function body
// ============================================================================

int main(int argc, char *argv[])
{
    // Determine the exec name under wich program is beeing executed.
    std::string fullpath = argv[0];
    unsigned int pos = fullpath.find_last_of(kPathSeparator);

    // Variables for main scope.

    if(std::string::npos != pos)
        exec_name = fullpath.substr(pos + 1, std::string::npos);
    else
        exec_name = fullpath;

    // Initialize option parsing engine and parse command line arguments.
    try {

        // Constructing an options describing variable and giving it a
        // textual description.
        ap::options_description optnl_opts("Optional arguments");
        ap::options_description gnrl_opts("General options");
        ap::options_description all_opts("All options");
        ap::options_description visible_opts("\
Application for testing various algorithms and implementations using\n\
Qt library.\n\n\
Mandatory arguments to long options are mandatory for short options too.\n\n\
Supported options are");

        // When we are adding options, first parameter is a name to be used in
        // command line. Second parameter is a type of that option, wrapped in
        // value<> class. Third parameter must be a short description of
        // that option.
        optnl_opts.add_options()
            ("help,h", "show this help message and exit")
            ("usage", "give a short usage message")
        ;
        gnrl_opts.add_options()
            ("version,V", "print program version")
        ;
        all_opts.add(optnl_opts).add(gnrl_opts);
        visible_opts.add(optnl_opts).add(gnrl_opts);

        // Variable to store our command line arguments.
        ap::variables_map vmap;

        // Parsing and storing arguments.
        ap::store(ap::command_line_parser(argc, argv).
            options(all_opts).run(), vmap);

        // Must be called after all the parsing and storing.
        ap::notify(vmap);

        // We can start handling our options.
        if (vmap.count("version")) {
            PrintVersionInfo();
            return EXIT_SUCCESS;
        } else if (vmap.count("help")) {
            PrintUsage();
            std::cout << "\n" << visible_opts << std::endl;
            PrintPositionalArgumentsHelp();
            PrintReportBugsTo();
            return EXIT_SUCCESS;
        } else if (vmap.count("usage")) {
            PrintUsage();
            PrintShortHelp();
            return EXIT_SUCCESS;
        }
    }

    // Handle unknown options.
    catch(std::exception& e) {
        std::cerr << exec_name << ": " << e.what() << std::endl;
        PrintUsage();
        PrintShortHelp();
        return EXIT_FAILURE;
    }

    // Handle unknown exceptions.
    catch(...) {
        std::cerr << exec_name << ": " << "Exception of unknown type!"
            << std::endl;
        PrintUsage();
        PrintShortHelp();
        return EXIT_FAILURE;
    }

    QVarLengthArray<float, 8> array(8);

    for(int i=0; i < 10; i++) {
        if(i <= 8 - 1) {
            array[i] = float(i);
        } else {
            array.append(float(i));
        }
    }

    for(int i=0; i < 10; i++) {
        std::cout << exec_name << ": " << array[i] << "\n";
    }
    std::cout << std::endl;

    return EXIT_SUCCESS;
}



// ============================================================================
// Function definitions
// ============================================================================

void PrintUsage() {
    std::cout << "Usage: " << exec_name
        << " [options ...] [DATA_FILE]"
        << std::endl;
}


void PrintShortHelp() {
    std::cout << "Try '" << exec_name << " --help' for more information."
        << std::endl;
}


void PrintPositionalArgumentsHelp() {
    std::cout << "\n\
DATA_FILE is a csv file containg measurement data to be analysed. This\n\
argument is mandatory.\n" << std::endl;
}


void PrintReportBugsTo() {
    std::cout << "Report " << exec_name << " bugs to " << kAuthorEmail
        << "\n" << std::endl;
}


void PrintVersionInfo() {
    std::cout << exec_name << " " << kVersionString << " Copyright (C) "
        << kYearString << " " << kAuthorName << "\n"
        << "\
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n\
This is free software: you are free to change and redistribute it.\n\
There is NO WARRANTY, to the extent permitted by law." << std::endl;
}
