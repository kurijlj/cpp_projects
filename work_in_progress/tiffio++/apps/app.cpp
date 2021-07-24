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

// "C" system headers

// Standard Library headers
#include <cstdlib>     // required by EXIT_SUCCESS, EXIT_FAILURE
#include <filesystem>  // Used for testing directory and file status
#include <iostream>    // required by cin, cout, ...
#include <string>      // self explanatory ...
#include <set>         // self explanatory ...
#include <vector>      // self explanatory ...

// External libraries headers
extern "C" {
    #include <tiffio.h>
}

#include <clipp.hpp>       // command line arguments parsing

// Project headers
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
    // Determine the exec name under wich program is beeing executed
    fs::path exec_path {argv[0]};
    exec_name = exec_path.filename().string();

    // Define structures to store command line options arguments and validators
    struct CLIArguments {
        bool        show_help;
        bool        print_usage;
        bool        show_version;
        int         iter_no;       // Number of iterations
        std::string input_file;
        std::string output_dir;
        std::string color_selec;    // Color channel selection
    };

    struct OptionValidators {
        PathValidator                        input_file;
        PathValidator                        output_dir;
        NumericalInputValidator<int>         iter_no;
        ListSelectionValidator<std::string>  color_selec;
    };

    CLIArguments user_options {false, false, false, 0, "", "", "all"};

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
    FileValidatorImp           input_file_imp {""};
    DirValidatorImp            output_dir_imp {""};
    CntNumInterval<int>        iter_no_domain {0, 255, true, true};
    std::set<std::string>      rgb_colors {"red", "green", "blue", "all"};
    ListOfChoices<std::string> color_list(rgb_colors);

    OptionValidators validators{
        PathValidator(input_file_imp, input_file_flags),
        PathValidator(output_dir_imp, output_dir_flags),
        NumericalInputValidator<int>(user_options.iter_no, iter_no_domain),
        ListSelectionValidator<std::string>(
                user_options.color_selec,
                color_list
                )
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
        (
            // Take care not to omitt value filter when using
            // path input options
            (clipp::option("-c", "--color-channel")
            & clipp::value(istarget, "COLOR_CHANNEL", user_options.color_selec))
            .doc(
                std::string("dummy color selection option. ")
                + std::string("Valid choices are: ")
                + color_list.str_repr()
                ),
            (clipp::option("-n", "--number-of-iterations")
            & clipp::value("INTEGER_NUMBER", user_options.iter_no))
            .doc(
                std::string("dummy option to demonstrate parsing ")
                + std::string("of integers. Argument can take any integer ")
                + std::string("value from the interval ")
                + iter_no_domain.str_repr()
                ),
            (clipp::option("-o", "--output_dir")
            & clipp::value(istarget, "OUTPUT_DIR", user_options.output_dir))
            .doc("directory to store output data to")
        ).doc("optional arguments: "),
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

        // Validate user input for 'color selection' cmd line option
        try {
            validators.color_selec.validate();
        } catch (ListSelectionValidator<std::string>::InvalidSelection) {
            std::cerr << exec_name << ": (ERROR) Invalid option \'"
                << validators.color_selec.value()
                << "\'\n";

            return EXIT_FAILURE;

        } catch (...) {
            std::cerr << exec_name
                << ": (ERROR) Unknown exception validating color selection!\n";

            return EXIT_FAILURE;

        }

        // Validate user input for 'number of iterations' cmd line option
        try {
            validators.iter_no.validate();
        } catch (NumericalInputValidator<int>::OutOfRange) {
            std::cerr << exec_name << ": (ERROR) Input value \'"
                << validators.iter_no.value()
                << "\' is out of range!\n";

            return EXIT_FAILURE;

        } catch (...) {
            std::cerr << exec_name
                << ": (ERROR) Unknown exception validating directory input!\n";

            return EXIT_FAILURE;

        }

        // Validate user input for 'output directory' cmd line option
        try {
            output_dir_imp = DirValidatorImp(user_options.output_dir);
            validators.output_dir.validate();

        } catch (DirValidatorImp::NotDirectory) {
            std::cerr << exec_name << ": (ERROR) Path \'"
                << validators.output_dir.value()
                << "\' is not an directory!\n";

            return EXIT_FAILURE;

        } catch (...) {
            std::cerr << exec_name
                << ": (ERROR) Unknown exception validating directory input!\n";

            return EXIT_FAILURE;

        }

        // If no output dir supplied, use the default value
        if (validators.output_dir.is_empty_path()) {
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
    std::cout << exec_name << ": Opening file '"
        << validators.input_file.value() << "' for reading ...\n";

    // TIFF* tif = TIFFOpen(validators.input_file.value().c_str(), "r");
    TIFF* tif = TIFFOpen(validators.input_file.value().c_str(), "rblLHMC");

    std::cout << exec_name << ": Reading file '"
        << validators.input_file.value() << "' ...\n";

    if(tif) {
        std::cout << exec_name << ": Closing file '"
            << validators.input_file.value() << "' ...\n";

        TIFFClose(tif);

    }

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
