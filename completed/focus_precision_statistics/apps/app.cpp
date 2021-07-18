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

// Standard Library Headers
#include <cstdlib>     // required by EXIT_SUCCESS, EXIT_FAILURE
#include <ctime>       // self explanatory ...
#include <filesystem>  // Used for testing directory and file status
#include <fstream>     // required for reading files
#include <iostream>    // required by cin, cout, ...
#include <regex>       // self explanatory ...
#include <string>      // self explanatory ...
#include <set>         // self explanatory ...
#include <vector>      // self explanatory ...

// Custom Libraries Headers
#include <clipp.hpp>                          // command line arguments parsing
#include <input_validators++/validators.hpp>  // custom classes to validate
                                              // user input parameters


// ============================================================================
// Define namespace aliases
// ============================================================================

namespace fs = std::filesystem;


// ============================================================================
// Global constants section
// ============================================================================

const std::string kAppName = "fpt_stat";
const std::string kVersionString = "0.1";
const std::string kYearString = "yyyy";
const std::string kAuthorName = "Ljubomir Kurij";
const std::string kAuthorEmail = "ljubomir_kurij@protonmail.com";
const std::string kAppDoc = "\
Does statistics on Focus Precision Test logs.\n\n\
Mandatory arguments to long options are mandatory for short options too.\n";
const std::string kLicense = "\
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n\
This is free software: you are free to change and redistribute it.\n\
There is NO WARRANTY, to the extent permitted by law.\n";


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
    fs::path exec_path {argv[0]};
    exec_name = exec_path.filename();

    // Define structures to store command line options arguments and validators
    struct CLIArguments {
        bool        show_help;
        bool        print_usage;
        bool        show_version;
        std::string input_dir;
    };

    struct OptionValidators {
        PathValidator input_dir;
    };

    CLIArguments user_options {false, false, false, ""};

    PathValidatorFlags input_dir_flags {
            false,  // We don't accept empty path string
            false,  // We don't accept nonexistent files
            false   // We don't accept empty directories
    };
    DirValidatorImp input_dir_imp {""};

    OptionValidators validators{
        PathValidator(input_dir_imp, input_dir_flags)
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
        clipp::opt_value(istarget, "INPUT_DIR", user_options.input_dir)
            .doc("directory containg log files"),
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

        // Validate user input for 'input directory' cmd line option
        try {
            input_dir_imp = DirValidatorImp(user_options.input_dir);
            validators.input_dir.validate();

        } catch (PathValidatorImp::EmptyPath) {
            auto fmt = clipp::doc_formatting {}
                .first_column(0)
                .last_column(79);

            printUsage(cli, exec_name, fmt);
            printShortHelp(exec_name);

            return EXIT_FAILURE;

        } catch (PathValidatorImp::NonExistent) {
            std::cerr << exec_name << ": (ERROR) Directory \'"
                << validators.input_dir.value() << "\' does not exist!\n";

            return EXIT_FAILURE;

        } catch (DirValidatorImp::NotDirectory) {
            std::cerr << exec_name << ": (ERROR) Directory \'"
                << validators.input_dir.value()
                << "\' is not an directory!\n";

            return EXIT_FAILURE;

        } catch (PathValidatorImp::EmptyStorage) {
            std::cerr << exec_name << ": (ERROR) Directory \'"
                << validators.input_dir.value()
                << "\' contains no log files!\n";

            return EXIT_FAILURE;

        } catch (...) {
            std::cerr << exec_name
                << ": (ERROR) Unknown exception validating file input!\n";

            return EXIT_FAILURE;

        }

    }


    // Print report and exit application
    unsigned long int file_count = 0;
    unsigned long int valid_file_count = 0;
    unsigned long int total_row_count = 0;
    unsigned long int x1_total_count = 0;
    unsigned long int x2_total_count = 0;
    unsigned long int y1_total_count = 0;
    unsigned long int y2_total_count = 0;
    unsigned long int z1_total_count = 0;
    unsigned long int z2_total_count = 0;

    std::cout << exec_name << ": Scanning directory '"
        << validators.input_dir.value() << "\n";

    for(auto& entry: fs::directory_iterator(validators.input_dir.value())) {
        if(entry.is_regular_file()) {

            // Validate log file name pattern
            std::string filename = entry.path().filename();
            std::regex log_filename_pattern(
                    "QAFocusPrecisionTest\\([0-9]{4}(-[0-9]{2}){2} "
                    "([0-9]{2}\\.){2}[0-9]{2}\\)\\.rmd"
                    );

            if(std::regex_match(filename, log_filename_pattern)) {

                // We have a matching filename. Read file contents and
                // initialize row counter
                unsigned long int log_row_count = 0;

                std::cout << "Reading file '" << filename << "': ";
                std::ifstream log_stream;
                log_stream.open(entry.path());
                if(log_stream.is_open()){

                    // We can read file. Initalize row buffer and field counters
                    unsigned long int x1_count = 0;
                    unsigned long int x2_count = 0;
                    unsigned long int y1_count = 0;
                    unsigned long int y2_count = 0;
                    unsigned long int z1_count = 0;
                    unsigned long int z2_count = 0;
                    std::string line;

                    file_count++;
                    while(getline(log_stream, line)) {
                        log_row_count++;

                        std::string row_id = line.substr(0, 6);

                        if("\"X1-1\"" == row_id) {
                            x1_count++;
                        } else if("\"X1-2\"" == row_id) {
                            x2_count++;
                        } else if("\"Y1-1\"" == row_id) {
                            y1_count++;
                        } else if("\"Y1-2\"" == row_id) {
                            y2_count++;
                        } else if("\"Z1-1\"" == row_id) {
                            z1_count++;
                        } else if("\"Z1-2\"" == row_id) {
                            z2_count++;
                        }
                    }
                    std::cout << log_row_count << " rows read.\n";

                    // We drop files with less than 1200 rows
                    if(1200 <= log_row_count) {
                        valid_file_count++;
                        total_row_count += log_row_count;
                        x1_total_count += x1_count;
                        x2_total_count += x2_count;
                        y1_total_count += y1_count;
                        y2_total_count += y2_count;
                        z1_total_count += z1_count;
                        z2_total_count += z2_count;
                    }

                } else {
                    // For some reason we cannot read file so print information
                    // on that
                    std::cout << "cannot read!\n";

                }

            }

        }

    }

    std::cout << exec_name << ": Total row count: " << total_row_count << "\n";
    std::cout << exec_name << ": Total files read: "
        << file_count << "\n";
    std::cout << exec_name << ": Total \"X1\" rows read: "
        << x1_total_count << "\n";
    std::cout << exec_name << ": Total \"X2\" rows read: "
        << x2_total_count << "\n";
    std::cout << exec_name << ": Total \"Y1\" rows read: "
        << y1_total_count << "\n";
    std::cout << exec_name << ": Total \"Y2\" rows read: "
        << y2_total_count << "\n";
    std::cout << exec_name << ": Total \"Z1\" rows read: "
        << z1_total_count << "\n";
    std::cout << exec_name << ": Total \"Z2\" rows read: "
        << z2_total_count << "\n";
    std::cout << exec_name << ": Valid files read: "
        << valid_file_count << "\n";
    std::cout << exec_name << ": Invalid files read: "
        << (file_count - valid_file_count) << "\n";
    std::cout << exec_name << ": Average row count: "
        << (total_row_count / valid_file_count) << "\n";
    std::cout << exec_name << ": Average \"X1\" rows count: "
        << (x1_total_count / valid_file_count) << "\n";
    std::cout << exec_name << ": Average \"X2\" rows count: "
        << (x2_total_count / valid_file_count) << "\n";
    std::cout << exec_name << ": Average \"Y1\" rows count: "
        << (y1_total_count / valid_file_count) << "\n";
    std::cout << exec_name << ": Average \"Y2\" rows count: "
        << (y2_total_count / valid_file_count) << "\n";
    std::cout << exec_name << ": Average \"Z1\" rows count: "
        << (z1_total_count / valid_file_count) << "\n";
    std::cout << exec_name << ": Average \"Z2\" rows count: "
        << (z2_total_count / valid_file_count) << "\n\n";

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
