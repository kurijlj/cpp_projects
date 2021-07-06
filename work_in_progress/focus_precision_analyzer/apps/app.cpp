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
#include <ctime>       // self explanatory ...
#include <filesystem>  // Used for testing directory and file status
#include <fstream>     // required for reading files
#include <iostream>    // required by cin, cout, ...
#include <regex>       // self explanatory ...
#include <string>      // self explanatory ...
#include <set>         // self explanatory ...
#include <vector>      // self explanatory ...

#include <clipp.hpp>       // command line arguments parsing
#include <input_validators++/validators.hpp>  // custom classes to validate
                                              // user input parameters


// ============================================================================
// Define namespace aliases
// ============================================================================

namespace fs = std::filesystem;


// ============================================================================
// Global constants section
// ============================================================================

const std::string kAppName = "cli_app";
const std::string kVersionString = "0.1";
const std::string kYearString = "yyyy";
const std::string kAuthorName = "Ljubomir Kurij";
const std::string kAuthorEmail = "ljubomir_kurij@protonmail.com";
const std::string kAppDoc = "\
Framework for developing command line applications using \'clipp\' command\n\
line argument parsing library.\n\n\
Mandatory arguments to long options are mandatory for short options too.\n";
const std::string kLicense = "\
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n\
This is free software: you are free to change and redistribute it.\n\
There is NO WARRANTY, to the extent permitted by law.\n";
const char kPathSeparator = '\\';


// ============================================================================
// Global variables section
// ============================================================================

static std::string exec_name = kAppName;


// ============================================================================
// Utility function prototypes
// ============================================================================

void printShortHelp(std::string = kAppName);
void printUsage(
        const clipp::group&,
        const std::string = kAppName,
        const clipp::doc_formatting& = clipp::doc_formatting{}
    );
void printVersionInfo();
void showHelp(
        const clipp::group&,
        const std::string = kAppName,
        const std::string = kAppDoc
    );


// ============================================================================
// App's main function body
// ============================================================================

int main(int argc, char *argv[])
{
    // Determine the exec name under wich program is beeing executed.
    std::string fullpath = argv[0];
    size_t pos = fullpath.find_last_of(kPathSeparator);
    size_t fullpath_last_index = fullpath.length() - 1;

    if(fullpath_last_index != pos)
        exec_name = fullpath.substr(pos + 1, std::string::npos);
    else
        exec_name = fullpath;

    // Define structures to store command line options arguments and validators
    struct CLIArguments {
        bool        show_help;
        bool        print_usage;
        bool        show_version;
        std::string input_file;
    };

    struct OptionValidators {
        PathValidator input_file;
    };

    CLIArguments user_options {false, false, false, ""};

    PathValidatorFlags input_file_flags {
            false,  // We don't accept empty path
            false,  // We don't accept nonexistent files
            false   // We don't accept empty files
    };
    FileValidatorImp input_file_imp {""};

    OptionValidators validators{
        PathValidator(input_file_imp, input_file_flags)
    };

    // Unsupported options aggregator.
    std::vector<std::string> unknown_options;

    // Option filters definitions
    auto istarget = clipp::match::prefix_not("-");

    // Set command line options
    auto cli = (
        // Must have more than one option
        // Take care not to omitt value filter when using
        // path input options
        clipp::opt_value(istarget, "INPUT_FILE", user_options.input_file)
            .doc("file containing input data"),
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

    // Parse command line options
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

        // Validate user input for 'input file' cmd line option
        try {
            input_file_imp = FileValidatorImp(user_options.input_file);
            validators.input_file.validate();

        } catch (PathValidatorImp::EmptyPath) {
            auto fmt = clipp::doc_formatting {}
                .first_column(0)
                .last_column(79);

            printUsage(cli, exec_name, fmt);
            printShortHelp(exec_name);

            return EXIT_FAILURE;

        } catch (PathValidatorImp::NonExistent) {
            std::cerr << exec_name << ": (ERROR) File \'"
                << validators.input_file.value() << "\' does not exist!\n";

            return EXIT_FAILURE;

        } catch (FileValidatorImp::NotRegularFile) {
            std::cerr << exec_name << ": (ERROR) File \'"
                << validators.input_file.value()
                << "\' is not an regular file!\n";

            return EXIT_FAILURE;

        } catch (PathValidatorImp::EmptyStorage) {
            std::cerr << exec_name << ": (ERROR) File \'"
                << validators.input_file.value()
                << "\' contains no data (empty file)!\n";

            return EXIT_FAILURE;

        } catch (...) {
            std::cerr << exec_name
                << ": (ERROR) Unknown exception validating file input!\n";

            return EXIT_FAILURE;

        }

    }


    // Print report and exit application
    std::cout << exec_name << ": Input file \""
        << validators.input_file.value() << "\"\n";

    // Extract filename
    std::string log_filename =  fs::path(validators.input_file.value())
        .filename().string();

    // Validate log file name pattern
    std::regex log_filename_pattern(
            "QAFocusPrecisionTest\\([0-9]{4}(-[0-9]{2}){2} "
            "([0-9]{2}\\.){2}[0-9]{2}\\)\\.rmd"
            );

    if(!std::regex_match(log_filename, log_filename_pattern)) {
        std::cout << exec_name << ": Invalid file name \""
            << validators.input_file.value() << "\". File does not match "
            "Focus Precision Test log file name pattern.\n";

        return EXIT_FAILURE;
    }

    // We have a file with the valid filename, so we can extract time and date
    // of the log creation
    std::string log_date_str = log_filename.substr(21, 10);
    std::string log_time_str = log_filename.substr(32, 8);

    // Convert to the time structure
    std::tm log_time;
    sscanf(log_date_str.c_str(),
            "%4d-%2d-%2d",
            &log_time.tm_year,
            &log_time.tm_mon,
            &log_time.tm_mday
            );
    sscanf(log_time_str.c_str(),
            "%2d.%2d.%2d",
            &log_time.tm_hour,
            &log_time.tm_min,
            &log_time.tm_sec
            );

    std::cout << exec_name << ": Log date "
        << log_time.tm_mon << "/"
        << log_time.tm_mday << "/"
        << log_time.tm_year << "\n";

    std::cout << exec_name << ": Log time "
        << log_time.tm_hour << ":"
        << log_time.tm_min << ":"
        << log_time.tm_sec << "\n";

    // Try to open file for reading
    std::cout << exec_name << ": Opening file \""
        << validators.input_file.value() << "\" ...\n";

    std::ifstream input_file;
    input_file.open(validators.input_file.value());

    if(input_file.is_open()) {
        std::cout << exec_name << ": File \""
            << validators.input_file.value() << "\" successfully opened!\n";
    } else {
        std::cout << exec_name << ": Unable to open file \""
            << validators.input_file.value() << "\n";
    }

    std::cout << exec_name << ": Closing file \""
        << validators.input_file.value() << "\" ...\n";
    input_file.close();



    return EXIT_SUCCESS;
}


// ============================================================================
// Function definitions
// ============================================================================

inline void printShortHelp(std::string exec_name) {
    std::cout << "Try '" << exec_name << " --help' for more information.\n";
}


inline void printUsage(
        const clipp::group& group,
        const std::string prefix,
        const clipp::doc_formatting& fmt)
{
    std::cout << clipp::usage_lines(group, prefix, fmt) << "\n";
}


void printVersionInfo() {
    std::cout << kAppName << " " << kVersionString << " Copyright (C) "
        << kYearString << " " << kAuthorName << "\n"
        << kLicense;
}


void showHelp(
        const clipp::group& group,
        const std::string exec_name,
        const std::string doc
        ) {
    auto fmt = clipp::doc_formatting {}.first_column(0).last_column(79);
    clipp::man_page man;

    man.prepend_section("USAGE", clipp::usage_lines(group, exec_name, fmt).str());
    man.append_section("", doc);
    man.append_section("", clipp::documentation(group, fmt).str());
    man.append_section("", "Report bugs to <" + kAuthorEmail + ">.");

    std::cout << man;
}
