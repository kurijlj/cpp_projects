// ============================================================================
// <one line to give the program's name and a brief idea of what it does.>
//
//  Copyright (C) <yyyy> <Author Name> <author@mail.com>
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
// * For refrence on badbit, failbit, eofbit visit:
//   <https://gehrcke.de/2011/06/reading-files-in-c-using-ifstream-dealing
//    -correctly-with-badbit-failbit-eofbit-and-perror/>
//
// ============================================================================


// ============================================================================
// Headers include section
// ============================================================================

#include <cstdlib>  // required by EXIT_SUCCESS, EXIT_FAILURE
#include <iostream>  // required by cin, cout, ...
#include <filesystem>  // Used for testing directory and file status
#include <string>  // self explanatory ...
#include <fstream>  // requird by ifstream
#include <clipp.hpp> // command line arguments parsing
#include "validators.hpp"  // classes to validate user input parameters


// ============================================================================
// Define namespace aliases
// ============================================================================

namespace fs = std::filesystem;


// ============================================================================
// Global constants section
// ============================================================================

const std::string kAppName = "app";
const std::string kVersionString = "0.1";
const std::string kYearString = "yyyy";
const std::string kAuthorName = "Ljubomir Kurij";
const std::string kAuthorEmail = "ljubomir_kurij@protonmail.com";
const char kPathSeparator = '\\';


// ============================================================================
// Global variables section
// ============================================================================

static std::string exec_name = kAppName;


// ============================================================================
// Utility function prototypes
// ============================================================================

void printShortHelp(std::string);
void printUsage(
        const clipp::group&,
        std::string = "",
        const clipp::doc_formatting& = clipp::doc_formatting{}
    );
void printVersionInfo();
void showHelp(
        const clipp::group&cli,
        clipp::doc_string = "",
        const clipp::doc_formatting& = clipp::doc_formatting{}
    );


// ============================================================================
// App's main function body
// ============================================================================

int main(int argc, char *argv[])
{
    // Determine the exec name under wich program is beeing executed.
    std::string fullpath = argv[0];
    unsigned int pos = fullpath.find_last_of(kPathSeparator);

    if(std::string::npos != pos)
        exec_name = fullpath.substr(pos + 1, std::string::npos);
    else
        exec_name = fullpath;

    // Parse command line options
    bool show_help = false, print_usage = false;
    std::string input_file = "";

    auto cli = (
        // Must have more than one option.
        clipp::option("-h", "--help").set(show_help)
            .doc("show this help message and exit"),
        clipp::option("--usage").set(print_usage)
            .doc("give a short usage message"),
        clipp::option("-V", "--version").call(printVersionInfo)
            .doc("print program version"),
        clipp::opt_value("input_file", input_file)
            .doc("file containing input data")
    );

    if(clipp::parse(argc, argv, cli)) {
        if(show_help) {showHelp(cli, exec_name); return EXIT_SUCCESS;}
        if(print_usage) {printUsage(cli, exec_name); return EXIT_SUCCESS;}

        // Validate user input for <input_file>
        try {
            PathValidator vd {
                new FileValidatorImp(input_file),
                new PathValidatorFlags(
                        false,  // We don't accept empty path
                        false,  // We don't accept nonexistent files
                        false   // We don't accept empty files
                        )
            };
            vd.validate();

        } catch (PathValidatorImp::EmptyPath) {
            printUsage(cli, exec_name);
            printShortHelp(exec_name);

            return EXIT_FAILURE;

        } catch (PathValidatorImp::NonExistent) {
            std::cerr << exec_name << ": (ERROR) File \'" << input_file
                << "\' does not exist!\n";

            return EXIT_FAILURE;

        } catch (FileValidatorImp::NotRegularFile) {
            std::cerr << exec_name << ": (ERROR) File \'" << input_file
                << "\' is not an regular file!\n";

            return EXIT_FAILURE;

        } catch (PathValidatorImp::EmptyStorage) {
            std::cerr << exec_name << ": (ERROR) File \'" << input_file
                << "\' contains no data (empty file)!\n";

            return EXIT_FAILURE;

        }

    } else {
        printUsage(cli, exec_name);
        printShortHelp(exec_name);

        return EXIT_FAILURE;
    }

    // Everything went fine. We can exit the application.
    return EXIT_SUCCESS;
}


// ============================================================================
// Function definitions
// ============================================================================

inline void printShortHelp(std::string progname) {
    std::cout << "\tTry '" << progname << " --help' for more information.\n";
}


inline void printUsage(
        const clipp::group& cli,
        std::string prefix,
        const clipp::doc_formatting& fmt)
{
    std::cout << clipp::usage_lines(cli, prefix, fmt) << '\n';
}


void printVersionInfo() {
    std::cout << exec_name << " " << kVersionString << " Copyright (C) "
        << kYearString << " " << kAuthorName << "\n"
        << "\
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n\
This is free software: you are free to change and redistribute it.\n\
There is NO WARRANTY, to the extent permitted by law." << std::endl;
}


void showHelp(
        const clipp::group& cli,
        clipp::doc_string progname,
        const clipp::doc_formatting& fmt)
{
    clipp::man_page man;
    man.append_section("", "\
Framework for developing command line applications using \'clipp\' command\n\
line argument parsing library.\n\n\
Mandatory arguments to long options are mandatory for short options too.\n");
    man.append_section("USAGE", clipp::usage_lines(cli, progname, fmt).str());
    man.append_section("OPTIONS", clipp::documentation(cli, fmt).str());
    man.append_section("BUGS", "\tReport bugs to <" + kAuthorEmail + ">.");

    std::cout << man;
}
