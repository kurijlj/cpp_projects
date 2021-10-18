// ============================================================================
//
// maketesttif - Creates and saves a test TIFF file
//
//  Copyright (C) 2021 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
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
// 2021-10-16 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
//
// * maketesttif.cpp: created.
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
#include <clipp.hpp>       // command line arguments parsing

// Project headers
#include <input_validators++/validators.hpp>  // validate user input
#include <tiffio++/tiffio++.hpp>              // TIFF Input/Output


// ============================================================================
// Define namespace aliases
// ============================================================================

namespace fs = std::filesystem;


// ============================================================================
// Global constants section
// ============================================================================

const std::string kAppName = "maketesttif";
const std::string kVersionString = "0.1";
const std::string kYearString = "2021";
const std::string kAuthorName = "Ljubomir Kurij";
const std::string kAuthorEmail = "ljubomir_kurij@protonmail.com";
const std::string kAppDoc = "\
Creates test TIFF file for the given file name.\n\n\
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
        std::string output_file;
    };

    struct OptionValidators {
        PathValidator                        output_file;
    };

    CLIArguments user_options {false, false, false, ""};

    PathValidatorFlags output_file_flags {
            false,  // We don't accept empty path
            true,   // We accept nonexistent files
            true    // We accept empty files
    };
    FileValidatorImp           output_file_imp {""};

    OptionValidators validators{
        PathValidator(output_file_imp, output_file_flags),
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
        clipp::opt_value(istarget, "TIF_FILE", user_options.output_file)
            .doc("tif image file"),
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
            output_file_imp = FileValidatorImp(user_options.output_file);
            validators.output_file.validate();

        } catch (PathValidatorImp::EmptyPath) {
            auto fmt = clipp::doc_formatting {}
                .first_column(0)
                .last_column(79);

            printUsage(cli, exec_name, fmt);
            printShortHelp(exec_name);

            return EXIT_FAILURE;

        } catch (FileValidatorImp::NotRegularFile) {
            std::cerr << exec_name << ": (ERROR) File \'"
                << validators.output_file.value()
                << "\' is not an regular file!\n";

            return EXIT_FAILURE;

        } catch (...) {
            std::cerr << exec_name
                << ": (ERROR) Unknown exception validating file input!\n";

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
            std::cerr << exec_name << ": Unknown error occured!\n";
            std::cout << "Report bugs to <" << kAuthorEmail << ">.\n";

        }

        return EXIT_FAILURE;
    }

    TIFFIOObject tif {
        validators.output_file.value(),
        TIFFIOObject::FileAccessMode(TIFFIOObject::FileAccessMode::Write)
    };
    tif.printWarnings(false);
    tif.printErrors(false);

    // Print report and exit application
    std::cout << exec_name << ": Opening file '"
        << validators.output_file.value() << "' for writing ...\n";

    // Try to open file
    try {
        tif.open();
    } catch (TIFFIOObject::LibtiffWarning w) {
        std::cerr << exec_name << ": " << w.message() << "\n";
    } catch (TIFFIOObject::LibtiffError e) {
        std::cerr << exec_name << ": " << e.message() << "\n";

        return EXIT_FAILURE;

    } catch (...) {
        std::cerr << exec_name
            << ": (ERROR) Unknown exception opening file\n\n";

        return EXIT_FAILURE;

    }

    // Try to write data to the file
    std::cout << exec_name << ": Writing data ...\n";
    try {
        unsigned long int strip_size = 0;
        TIFFObjectInfo tifinfo;
        TIFFIOObject::StatusInformation statinfo;

        tif.readTagValue<unsigned long int>(
                TIFFIOObject::TIFFTag::StripByteCounts,
                &strip_size
                );

        if(std::string("Error") != tifinfo.size(tif)) {
            std::cout << "                  size: "
                << tifinfo.size(tif)
                << "\n";
        };
        std::cout << "            dimensions: "
            << tifinfo.dimensions(tif)
            << "\n";
        std::cout << "           compression: "
            << tifinfo.compression(tif)
            << "\n";
        std::cout << "     samples per pixel: "
            << tifinfo.samplesPerPixel(tif)
            << "\n";
        std::cout << "       bits per sample: "
            << tifinfo.bitsPerSample(tif)
            << "\n";
        std::cout << "  planar configuration: "
            << tifinfo.planarConfig(tif)
            << "\n";
        std::cout << "            resolution: "
            << tifinfo.resolution(tif)
            << "\n";
        std::cout << "           orientation: "
            << tifinfo.orientation(tif)
            << "\n\n";
        std::cout << "                 tiled: "
            << (statinfo.is_tiled ? "true" : "false")
            << "\n";
        std::cout << "      number of strips: "
            << statinfo.number_of_strips
            << "\n";
        std::cout << "          byte swapped: "
            << (statinfo.is_byte_swapped ? "true" : "false")
            << "\n";
        std::cout << "            strip size: " << strip_size << "\n";

    } catch (TIFFIOObject::LibtiffWarning w) {
        std::cerr << exec_name << ": " << w.message() << "\n";
    } catch (TIFFIOObject::LibtiffError e) {
        std::cerr << exec_name << ": " << e.message() << "\n";

        return EXIT_FAILURE;

    } catch (...) {
        std::cerr << exec_name
            << ": (ERROR) Unknown exception creating the file '"
            << validators.output_file.value()
            << "\n\n";

        return EXIT_FAILURE;

    }

    // Close file and bail out
    try {
        tif.close();
    } catch (TIFFIOObject::LibtiffWarning w) {
        std::cerr << exec_name << ": " << w.message() << "\n";
    } catch (TIFFIOObject::LibtiffError e) {
        std::cerr << exec_name << ": " << e.message() << "\n";

        return EXIT_FAILURE;

    } catch (...) {
        std::cerr << exec_name
            << ": (ERROR) Unknown exception closing the file\n\n";

        return EXIT_FAILURE;

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
