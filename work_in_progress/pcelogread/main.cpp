// ============================================================================
// Copyright (C) <yyyy> <Author Name> <author@mail.com>
//
// This file is part of <program name>.
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
// <Put documentation here>
//
// 2020-04-19 Ljubomir Kurij <kurijlj@mail.com>
//
// * main.cpp: created.
//
// ============================================================================


// ============================================================================
//
// TODO:
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
#include <QFile>  // required for testing file existance
#include <QString>  // required for storing data file's name

// Boost Library Headers
#include <boost/program_options.hpp>  // self explanatory ...

// Custom Code Headers
#include "logreader.hpp"  // This is our main window

// Unit Testing Headers
#include "lest.hpp"  // required by unit testing framework


// ============================================================================
// Define namespace aliases
// ============================================================================

namespace ap = boost::program_options;  // 'ap' as arguments parsing


// ============================================================================
// Global constants section
// ============================================================================

const std::string kAppName = "pcelogread";
const std::string kVersionString = "0.1";
const std::string kYearString = "yyyy";
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
// Unit testing specifications
// ============================================================================

const QString log_1 = ".//data//(2019-08-26) -- PCE Log Reader Test 1.txt";
const QString log_2 = ".//data//(2019-08-27) -- PCE Log Reader Test 2.txt";
const QString log_3 = ".//idonotexist.txt";

const lest::test specification[] =
{
    CASE ("Initialization")
    {
        EXPECT_NO_THROW (LogRead(log_1, nullptr));
        EXPECT_NO_THROW (LogRead(log_2, nullptr));
        EXPECT_NO_THROW (LogRead(log_3, nullptr));
    },

    CASE ("Testing Validity After Initialization")
    {
        EXPECT (true == LogRead(log_1, nullptr).isLogValid());
        EXPECT (false == LogRead(log_2, nullptr).isLogValid());
        EXPECT (true == LogRead(log_3, nullptr).isLogValid());
    },

    CASE ("Reading Data")
    {
        EXPECT_NO_THROW (LogRead(log_1, nullptr).read());
        EXPECT_NO_THROW (LogRead(log_2, nullptr).read());
        EXPECT_NO_THROW (LogRead(log_3, nullptr).read());
    },

    CASE("Destroying Objects")
    {
        EXPECT_NO_THROW (delete new LogRead(log_1, nullptr));
        EXPECT_NO_THROW (delete new LogRead(log_2, nullptr));
        EXPECT_NO_THROW (delete new LogRead(log_3, nullptr));
    },
};

// ============================================================================
// App's main function body
// ============================================================================

int main(int argc, char *argv[])
{
    QString fn; // We store data file's name here.

    // Determine the exec name under wich program is beeing executed.
    std::string fullpath = argv[0];
    unsigned int pos = fullpath.find_last_of(kPathSeparator);

    if(std::string::npos != pos)
        exec_name = fullpath.substr(pos + 1, std::string::npos);
    else
        exec_name = fullpath;

    // Initialize option parsing engine and parse command line arguments.
    try {

        // Constructing an options describing variable and giving it a
        // textual description.
        ap::options_description pos_opts("Positional arguments");
        ap::options_description optnl_opts("Optional arguments");
        ap::options_description gnrl_opts("General options");
        ap::options_description all_opts("All options");
        ap::options_description visible_opts("\
Framework for application development implementing Boost's program_options\n\
command line arguments parsing library.\n\n\
Mandatory arguments to long options are mandatory for short options too.\n\n\
Supported options are");

        // When we are adding options, first parameter is a name to be used in
        // command line. Second parameter is a type of that option, wrapped in
        // value<> class. Third parameter must be a short description of
        // that option.
        pos_opts.add_options()
            ("DATA_FILE", ap::value<std::string>(),
                "(mandatory) a CSV file containg data to be analysed")
        ;
        optnl_opts.add_options()
            ("help,h", "show this help message and exit")
            ("usage", "give a short usage message")
        ;
        gnrl_opts.add_options()
            ("version,V", "print program version")
        ;
        all_opts.add(pos_opts).add(optnl_opts).add(gnrl_opts);
        visible_opts.add(optnl_opts).add(gnrl_opts);

        // Add positional options.
        ap::positional_options_description p;
        p.add("DATA_FILE", 1);

        // Variable to store our command line arguments.
        ap::variables_map vmap;

        // Parsing and storing arguments.
        ap::store(ap::command_line_parser(argc, argv).
            options(all_opts).positional(p).run(), vmap);

        // Must be called after all the parsing and storing.
        ap::notify(vmap);

        // We can start handling our options.
        if (vmap.count("version")) {
            PrintVersionInfo();
        } else if (vmap.count("help")) {
            PrintUsage();
            std::cout << "\n" << visible_opts << std::endl;
            PrintPositionalArgumentsHelp();
            PrintReportBugsTo();
        } else if (vmap.count("usage")) {
            PrintUsage();
            PrintShortHelp();
        } else {
            if (!vmap.count("DATA_FILE")) {
                PrintUsage();
                PrintShortHelp();
                return EXIT_FAILURE;
            } else {
                fn = vmap["DATA_FILE"].as<std::string>().c_str();
                QFile data_file(fn);
                if (!data_file.exists()) {
                    std::cerr << exec_name << ": File '" << fn.toStdString()
                        << "' does not exist!" << std::endl;
                    return EXIT_FAILURE;
                }
            }
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
        std::cerr << exec_name << ": Exception of unknown type!" << std::endl;
        PrintUsage();
        PrintShortHelp();
        return EXIT_FAILURE;
    }

    // Read the file.
    // return lest::run (specification, argc, argv);
    LogRead *log = nullptr;

    log = new LogRead(fn);

    if (log->isLogValid()) {
        std::cout << exec_name << ": Log is valid!" << std::endl;
    } else {
        std::cout << exec_name << ": Log is not valid!" << std::endl;
    }

    if (log->checkLogHeader()) {
        std::cout << exec_name << ": Log header is valid!" << std::endl;
    } else {
        std::cout << exec_name << ": Log header is not valid!" << std::endl;
    }
    // log->read();

    delete log;

    return EXIT_SUCCESS;
}



// ============================================================================
// Function definitions
// ============================================================================

void PrintUsage() {
    std::cout << "Usage: " << exec_name
        << " [options ...] [DATA_fILE]"
        << std::endl;
}


void PrintShortHelp() {
    std::cout << "Try '" << exec_name << " --help' for more information."
        << std::endl;
}


void PrintPositionalArgumentsHelp() {
    std::cout << "\n\
DATA_FILE is an CSV file containg data to be analysed. This argument is\n\
mandatory.\n" << std::endl;
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
