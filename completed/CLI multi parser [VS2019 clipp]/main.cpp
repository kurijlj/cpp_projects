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
#include <set>         // self explanatory ...
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
const std::string kAppDoc = "\
Framework for developing command line applications using \'clipp\' command\n\
line argument parsing library.\n\n\
Mandatory arguments to long options are mandatory for short options too.\n";
const std::string kReceiveDoc = "\
Load data form a given file.\n\n\
Mandatory arguments to long options are mandatory for short options too.\n";
const std::string kSendDoc = "\
Save data to a given file.\n\n\
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

void printShortHelp(const std::string = kAppName, const std::string = "");
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
    unsigned int pos = fullpath.find_last_of(kPathSeparator);

    if(std::string::npos != pos)
        exec_name = fullpath.substr(pos + 1, std::string::npos);
    else
        exec_name = fullpath;

    // Define structures to store command line options arguments and validators
    enum class Command {general, receive, send};

    struct OptionArguments {
        bool show_help;
        bool print_usage;
        bool show_version;
        std::string input_file;
        std::string target_file;
    };

    struct OptionValidators {
        PathValidator input_file;
        PathValidator target_file;
    };

    // Define where we store user selected action
    Command selected = Command::general;

    // Defaine default user options values
    OptionArguments user_options {
        false,  // Don't show help
        false,  // Don't print usage
        false,  // Don't show version
        "",     // No default input file
        ""      // Initialize target file to empty path
    };

    PathValidatorFlags input_file_flags {
            false,  // We don't accept empty path
            false,  // We don't accept nonexistent files
            false   // We don't accept empty files
    };
    PathValidatorFlags target_file_flags {
            true,  // Accept empty path
            true,  // Accept nonexistent files
            true   // Accept empty files
    };
    FileValidatorImp input_file_imp {""};
    FileValidatorImp target_file_imp {""};

    OptionValidators validators{
        PathValidator(input_file_imp, input_file_flags),
        PathValidator(target_file_imp, target_file_flags),
    };

    // Unsupported options aggregator.
    std::vector<std::string> unknown_options;

    // Option filters definitions:
    // * Exclude option arguments starting with hyphen
    auto istarget = clipp::match::prefix_not("-");

    // Set command line options. Must have more than one option. Take care not
    // to omitt value filter when using path input options
    auto general = (
        clipp::option("-h", "--help").set(user_options.show_help)
            .doc("show this help message and exit"),
        clipp::option("--usage").set(user_options.print_usage)
            .doc("give a short usage message"),
        clipp::option("-V", "--version").set(user_options.show_version)
            .doc("print program version")
    ).doc("General options:");

    auto receive = (
        clipp::command("receive").set(selected, Command::receive),
        clipp::opt_value(istarget, "INPUT_FILE", user_options.input_file)
            .doc("file containing input data"),
        clipp::option("-h", "--help").set(user_options.show_help)
            .doc("show this help message and exit"),
        clipp::option("--usage").set(user_options.print_usage)
            .doc("give a short usage message")
    ).doc("Options for \"receive\":");

    auto send = (
        clipp::command("send").set(selected, Command::send),
        clipp::opt_value(istarget, "OUTPUT_FILE", user_options.target_file)
            .doc("file to send data to"),
        clipp::option("-h", "--help").set(user_options.show_help)
            .doc("show this help message and exit"),
        clipp::option("--usage").set(user_options.print_usage)
            .doc("give a short usage message")
    ).doc("Options for \"send\":");

    auto cli = (general | receive | send, clipp::any_other(unknown_options));

    // Parse command line options
    if(clipp::parse(argc, argv, cli) && unknown_options.empty()) {
        if(Command::receive == selected) {
            if(user_options.show_help) {
                showHelp(receive, exec_name, kReceiveDoc);

                return EXIT_SUCCESS;
            }
            if(user_options.print_usage) {
                auto fmt = clipp::doc_formatting {}
                    .first_column(0)
                    .last_column(79);

                printUsage(receive, exec_name, fmt);

                return EXIT_SUCCESS;
            }

            // Validate user input for 'input file'
            try {
                input_file_imp = FileValidatorImp(user_options.input_file);
                validators.input_file.validate();

            } catch (PathValidatorImp::EmptyPath) {
                auto fmt = clipp::doc_formatting {}
                    .first_column(0)
                    .last_column(79);

                printUsage(receive, exec_name, fmt);
                printShortHelp(exec_name, "receive");

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
                    << ": (ERROR) Unknown exception validating input file!\n";

                return EXIT_FAILURE;

            }

        }

        if(Command::send == selected) {
            if(user_options.show_help) {
                showHelp(send, exec_name, kSendDoc);

                return EXIT_SUCCESS;
            }
            if(user_options.print_usage) {
                auto fmt = clipp::doc_formatting {}
                    .first_column(0)
                    .last_column(79);

                printUsage(send, exec_name, fmt);

                return EXIT_SUCCESS;
            }

            // Validate user input for 'target file'
            try {
                target_file_imp = FileValidatorImp(user_options.target_file);
                validators.target_file.validate();

            } catch (FileValidatorImp::NotRegularFile) {
                std::cerr << exec_name << ": (ERROR) Path \'"
                    << validators.target_file.value()
                    << "\' is not an regular file!\n";

                return EXIT_FAILURE;

            } catch (...) {
                std::cerr << exec_name
                    << ": (ERROR) Unknown exception validating target file!\n";

                return EXIT_FAILURE;

            }

            // If no target file supplied, use the default one
            if (validators.target_file.is_empty_path()) {
                target_file_imp = FileValidatorImp(".\\output.txt");
            }
        }

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

        if(Command::general == selected) {
            // No command selected so print usage and short help, and exit with
            // an error
            auto fmt = clipp::doc_formatting {}
                .first_column(0)
                .last_column(79);
            printUsage(cli, exec_name, fmt);
            printShortHelp(exec_name);

            return EXIT_FAILURE;
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
            // Here we handle some special conflicting situations. It seems
            // that 'clipp' doesn't handle appropriately cases when two
            // mutually exclusive commands are passed as command line
            // arguments, e.g.:
            //     app.exe send receive
            //     app.exe send -V
            //     app.exe receive -V

            // Determine what is passed as command line arguments
            std::set<std::string> arguments;
            for(unsigned int i = 0; i < (unsigned int) argc; i++) {
                arguments.insert(std::string(argv[i]));
            }

            bool is_send = (arguments.count("send") > 0);
            bool is_receive = (arguments.count("receive") > 0);
            bool is_version = (arguments.count("-V") > 0)
                || (arguments.count("--version") > 0);

            auto fmt = clipp::doc_formatting {}
                .first_column(0)
                .last_column(79);

            if(is_send && is_receive) {
                std::cerr << exec_name << ": Mutually exclusive commands\n";
                printUsage(cli, exec_name, fmt);
                printShortHelp(exec_name);

            } else {
                if((is_send || is_receive) && is_version) {
                    std::cerr << exec_name << ": Option '-V' not supported"
                        << " with '"
                        << (is_send ? "send" : "receive")
                        << "' command\n";
                    printUsage(cli, exec_name, fmt);
                    printShortHelp(exec_name);

                } else {
                    // None of the conflicting cases that we know of occured
                    std::cerr << exec_name << ": Unknown error occured!\n";
                    std::cout << "Report bugs to <" << kAuthorEmail << ">.\n";

                }

            }

        }

        return EXIT_FAILURE;
    }

    // Print report and exit application
    if(Command::receive == selected) std::cout << exec_name << ": "
        << validators.input_file.value() << "\n";

    if(Command::send == selected) std::cout << exec_name << ": "
        << validators.target_file.value() << "\n";

    return EXIT_SUCCESS;
}


// ============================================================================
// Function definitions
// ============================================================================

inline void printShortHelp(
        const std::string exec_name,
        const std::string command_name
        ) {
    std::cout << "Try '" << exec_name
        << ("" == command_name ? "" : " ")
        << command_name
        << " --help' for more information.\n";
}


inline void printUsage(
        const clipp::group& group,
        const std::string prefix,
        const clipp::doc_formatting& fmt
        ) {
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

    man.prepend_section(
            "USAGE:",
            clipp::usage_lines(group, exec_name, fmt).str()
            );
    man.append_section("", doc);
    man.append_section("", clipp::documentation(group, fmt).str());
    man.append_section("", "Report bugs to <" + kAuthorEmail + ">.");

    std::cout << man;
}
