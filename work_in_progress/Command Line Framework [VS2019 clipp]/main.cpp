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
// ============================================================================


// ============================================================================
// Headers include section
// ============================================================================

#include <cstdlib>     // required by EXIT_SUCCESS, EXIT_FAILURE
#include <iostream>    // required by cin, cout, ...
#include <string>      // self explanatory ...
#include <vector>      // self explanatory ...

#include <clipp.hpp>       // command line arguments parsing
#include "validators.hpp"  // custom classes to validate user input parameters


// ============================================================================
// Define namespace aliases
// ============================================================================


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

    // Variables holding command line options arguments
    bool show_help = false, print_usage = false, show_version = false;
    int n = 0;

    // Unsupported options aggregator.
    std::vector<std::string> unknown_options;

    // Input file and output directory variables and option filters definitions
    std::string input_file = "", output_dir = "";
    auto istarget = clipp::match::prefix_not("-");

    PathValidatorFlags input_file_flags {
            false,  // We don't accept empty path
            false,  // We don't accept nonexistent files
            false   // We don't accept empty files
    };
    PathValidatorFlags output_dir_flags {
            true,  // Accept empty path
            true,  // Accept nonexistent directories
            true   // Accept empty directories
    };
    FileValidatorImp input_file_imp {""};
    DirValidatorImp output_dir_imp {""};
    PathValidator input_file_vd {
        input_file_imp,
        input_file_flags
    };
    PathValidator output_dir_vd {
        output_dir_imp,
        output_dir_flags
    };

    // Set command line options
    auto cli = (
        // Must have more than one option
        // Take care not to omitt value filter when using
        // path input options
        clipp::opt_value(istarget, "INPUT_FILE", input_file)
            .doc("file containing input data"),
        (
            clipp::option("-h", "--help").set(show_help)
                .doc("show this help message and exit"),
            clipp::option("--usage").set(print_usage)
                .doc("give a short usage message"),
            clipp::option("-V", "--version").set(show_version)
                .doc("print program version")
        ).doc("general options:"),
        (
            // Take care not to omitt value filter when using
            // path input options
            clipp::option("-n", "--number-of-iterations")
                .doc("dummy option to demonstrate parsing of integers")
                & clipp::value("INTEGER_NUMBER", n),
            clipp::option("-o", "--output_dir")
                .doc("directory to store output data to")
                & clipp::value(istarget, "OUTPUT_DIR", output_dir)
        ).doc("optional arguments:"),
        clipp::any_other(unknown_options)
    );

    // Parse command line options
    if(clipp::parse(argc, argv, cli) && unknown_options.empty()) {
        if(show_help) { showHelp(cli, exec_name); return EXIT_SUCCESS; }
        if(print_usage) {
            auto fmt = clipp::doc_formatting {}
                .first_column(0)
                .last_column(79);

            printUsage(cli, exec_name, fmt);

            return EXIT_SUCCESS;
        }
        if(show_version) { printVersionInfo(); return EXIT_SUCCESS; }

        // Validate user input for 'input_file' cmd line option
        try {
            input_file_imp = FileValidatorImp(input_file);
            input_file_vd.validate();

        } catch (PathValidatorImp::EmptyPath) {
            auto fmt = clipp::doc_formatting {}
                .first_column(0)
                .last_column(79);

            printUsage(cli, exec_name, fmt);
            printShortHelp(exec_name);

            return EXIT_FAILURE;

        } catch (PathValidatorImp::NonExistent) {
            std::cerr << exec_name << ": (ERROR) File \'"
                << input_file_vd.value() << "\' does not exist!\n";

            return EXIT_FAILURE;

        } catch (FileValidatorImp::NotRegularFile) {
            std::cerr << exec_name << ": (ERROR) File \'"
                << input_file_vd.value() << "\' is not an regular file!\n";

            return EXIT_FAILURE;

        } catch (PathValidatorImp::EmptyStorage) {
            std::cerr << exec_name << ": (ERROR) File \'"
                << input_file_vd.value()
                << "\' contains no data (empty file)!\n";

            return EXIT_FAILURE;

        } catch (...) {
            std::cerr << exec_name
                << ": (ERROR) Unknown exception validating file input!\n";

            return EXIT_FAILURE;

        }

        // Validate user input for 'output_dir' cmd line option
        try {
            output_dir_imp = DirValidatorImp(output_dir);
            output_dir_vd.validate();

        } catch (DirValidatorImp::NotDirectory) {
            std::cerr << exec_name << ": (ERROR) Path \'"
                << output_dir_vd.value() << "\' is not an directory!\n";

            return EXIT_FAILURE;

        } catch (...) {
            std::cerr << exec_name
                << ": (ERROR) Unknown exception validating directory input!\n";

            return EXIT_FAILURE;

        }

        // If no output dir supplied, use the default value
        if (output_dir_vd.is_empty_path()) {
            output_dir_imp = DirValidatorImp(".\\output");
        }

    } else {
        if(!unknown_options.empty()) {
            auto fmt = clipp::doc_formatting {}
                .first_column(0)
                .last_column(79);

            // Print only first option on the stack
            std::cerr << exec_name << ": Unknown option "
                << unknown_options.front() << "\n";
            printUsage(cli, exec_name, fmt);
            printShortHelp(exec_name);

        } else {
            std::cerr << exec_name << ": Unknown error occured!\n";
            std::cout << "Report bugs to <" << kAuthorEmail << ">.\n";

        }

        return EXIT_FAILURE;
    }

    // Print report and exit application
    std::cout << exec_name << ": Input file\t-> "
        << input_file_vd.value() << "\n";
    std::cout << exec_name << ": Output dir\t-> "
        << output_dir_vd.value() << "\n";
    std::cout << exec_name << ": Number of iterations\t-> " << n << "\n";

    return EXIT_SUCCESS;
}


// ============================================================================
// Function definitions
// ============================================================================

inline void printShortHelp(std::string progname) {
    std::cout << "Try '" << progname << " --help' for more information.\n";
}


inline void printUsage(
        const clipp::group& cli,
        std::string prefix,
        const clipp::doc_formatting& fmt)
{
    std::cout << clipp::usage_lines(cli, prefix, fmt) << "\n";
}


void printVersionInfo() {
    std::cout << exec_name << " " << kVersionString << " Copyright (C) "
        << kYearString << " " << kAuthorName << "\n"
        << "\
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n\
This is free software: you are free to change and redistribute it.\n\
There is NO WARRANTY, to the extent permitted by law.\n";
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
