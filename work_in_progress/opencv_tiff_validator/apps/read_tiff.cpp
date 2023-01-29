// ============================================================================
//
// validate_tiff - Check and avalidate if input file is a TIFF
//
//  Copyright (C) 2022 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
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
// 2022-04-09 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
//
// * validate_tiff.cpp: created.
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
#include <array>       // self explanatory ...
#include <cstdlib>     // required by EXIT_SUCCESS, EXIT_FAILURE
#include <filesystem>  // Used for testing directory and file status
#include <fstream>     // Used for reading files
#include <iostream>    // required by cin, cout, ...
#include <string>      // self explanatory ...
#include <set>         // self explanatory ...
#include <vector>      // self explanatory ...

// External libraries headers
#include <clipp.hpp>       // command line arguments parsing

// Project headers
#include <input_validators++/validators.hpp>  // validate user input


// ============================================================================
// Define namespace aliases
// ============================================================================

namespace fs = std::filesystem;


// ============================================================================
// Global constants section
// ============================================================================

const std::string kAppName = "validate_tiff";
const std::string kVersionString = "0.1";
const std::string kYearString = "2022";
const std::string kAuthorName = "Ljubomir Kurij";
const std::string kAuthorEmail = "ljubomir_kurij@protonmail.com";
const std::string kAppDoc = "\
Shows info for the given tif file.\n\n\
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

struct TifInfo {
    std::string  endianess;
    unsigned short magick_no;
    unsigned long  image_width;
    unsigned long  image_length;
    std::vector<unsigned short> bits_per_sample;
    unsigned short compression;
    unsigned short photometric_interpretation;
    unsigned short samples_per_pixel;
    unsigned long  x_resolution[2];
    unsigned long  y_resolution[2];
    unsigned short resolution_unit;
    std::string date_time;
};


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
        std::string input_file;
    };

    struct OptionValidators {
        PathValidator                        input_file;
    };

    CLIArguments user_options {false, false, false, ""};

    PathValidatorFlags input_file_flags {
            false,  // We don't accept empty path
            false,  // We don't accept nonexistent files
            false   // We don't accept empty files
    };
    TifValidatorImp           input_file_imp {""};

    OptionValidators validators{
        PathValidator(input_file_imp, input_file_flags),
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
        clipp::opt_value(istarget, "TIF_FILE", user_options.input_file)
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
            input_file_imp = TifValidatorImp(user_options.input_file);
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

        } catch (TifValidatorImp::NotRegularFile) {
            std::cerr << exec_name << ": (ERROR) File \'"
                << validators.input_file.value()
                << "\' is not an regular file!\n";

            return EXIT_FAILURE;

        } catch (PathValidatorImp::EmptyStorage) {
            std::cerr << exec_name << ": (ERROR) File \'"
                << validators.input_file.value()
                << "\' contains no data (empty file)!\n";

            return EXIT_FAILURE;

        } catch (TifValidatorImp::NotTifFile) {
            std::cerr << exec_name << ": (ERROR) File \'"
                << validators.input_file.value()
                << "\' is not a TIF file!\n";

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

    // Test reading routines
    short nent = 0, tag = 0;
    long offset;
    std::array<char, 12> buf;
    std::string endianess("");
    // std::set<short> tif_tags {
    //     0x100, // ImageWidth
    //     0x101, // ImageLength
    //     0x102, // BitsPerSample
    //     0x103, // Compression
    //     0x106, // PhotometricInterpretation
    //     0x115, // SamplesPerPixel
    //     0x11A, // XResolution
    //     0x11B, // YResolution
    //     0x128, // ResolutionUnit
    // };
    TifInfo ti;

    offset = 0;
    ti.magick_no = 42;
    std::ifstream imfstrm;
    imfstrm.open(validators.input_file.value(), std::ios::binary);
    imfstrm.seekg(offset, std::ios::beg);
    imfstrm.read(buf.data(), 2);
    buf[2] = '\0';
    ti.endianess = std::string(buf.data());

    offset = 4;
    imfstrm.seekg(offset, std::ios::beg);
    imfstrm.read(buf.data(), 4);

    if (std::string("II") == ti.endianess) {
        // Little endian: leave byte order intact
        offset = (static_cast<unsigned long>(buf[0]) & 0x000000FF)
                + (static_cast<unsigned long>(buf[1] << 8) & 0x0000FF00)
                + (static_cast<unsigned long>(buf[2] << 16) & 0x00FF0000)
                + (static_cast<unsigned long>(buf[3] << 24) & 0xFF000000);
    } else {
        // Big endian: swap byte order
        offset = (static_cast<unsigned long>(buf[3]) & 0x000000FF)
                + (static_cast<unsigned long>(buf[2] << 8) & 0x0000FF00)
                + (static_cast<unsigned long>(buf[1] << 16) & 0x00FF0000)
                + (static_cast<unsigned long>(buf[0] << 24) & 0xFF000000);
    }
    imfstrm.seekg(offset, std::ios::beg);
    imfstrm.read(buf.data(), 2);
    if (std::string("II") == ti.endianess) {
        // Little endian: leave byte order intact
        nent = (static_cast<unsigned short>(buf[0]) & 0x00FF)
                + (static_cast<unsigned short>(buf[1] << 8) & 0xFF00);
    } else {
        // Big endian: swap byte order
        nent = (static_cast<unsigned short>(buf[1]) & 0x00FF)
                + (static_cast<unsigned short>(buf[0] << 8) & 0xFF00);
    }
    offset += 2;
    long first_ifd_offset = offset;
    for(unsigned short i = 0; i < nent; ++i) {
        imfstrm.read(buf.data(), 12);
        if (std::string("II") == ti.endianess) {
            // Little endian: leave byte order intact
            tag = (static_cast<unsigned short>(buf[0]) & 0x00FF)
                    + (static_cast<unsigned short>(buf[1] << 8) & 0xFF00);
        } else {
            // Big endian: swap byte order
            tag = (static_cast<unsigned short>(buf[1]) & 0x00FF)
                    + (static_cast<unsigned short>(buf[0] << 8) & 0xFF00);
        }

        // if (auto search = tif_tags.find(tag); search != tif_tags.end()) {
        //     std::cout << std::hex << tag << std::dec << ": ... Found.\n";
        // }
        unsigned short dt = 0;
        std::array<char, 20> val;
        // unsigned long count = 0;
        switch (tag)
        {
            case 0x100:  // ImageWidth
                if (std::string("II") == ti.endianess) {
                    // Little endian: leave byte order intact
                    dt = (static_cast<unsigned short>(buf[2]) & 0x00FF)
                            + (static_cast<unsigned short>(buf[3] << 8) & 0xFF00);
                    if(3 == dt) {
                        ti.image_width = (static_cast<unsigned long>(buf[8]) & 0x000000FF)
                                + (static_cast<unsigned long>(buf[9] << 8) & 0x0000FF00);
                    } else {
                        ti.image_width = (static_cast<unsigned long>(buf[8]) & 0x000000FF)
                                + (static_cast<unsigned long>(buf[9] << 8) & 0x0000FF00)
                                + (static_cast<unsigned long>(buf[10] << 16) & 0x00FF0000)
                                + (static_cast<unsigned long>(buf[11] << 24) & 0xFF000000);
                    }
                } else {
                    // Big endian: swap byte order
                    dt = (static_cast<unsigned short>(buf[3]) & 0x00FF)
                            + (static_cast<unsigned short>(buf[2] << 8) & 0xFF00);
                    if(3 == dt) {
                        ti.image_width = (static_cast<unsigned long>(buf[9]) & 0x000000FF)
                                + (static_cast<unsigned long>(buf[8] << 8) & 0x0000FF00);
                    } else {
                        ti.image_width = (static_cast<unsigned long>(buf[11]) & 0x000000FF)
                                + (static_cast<unsigned long>(buf[10] << 8) & 0x0000FF00)
                                + (static_cast<unsigned long>(buf[9] << 16) & 0x00FF0000)
                                + (static_cast<unsigned long>(buf[8] << 24) & 0xFF000000);
                    }
                }
                std::cout << "ImageWidth: " << ti.image_width << std::endl;
                break;

            case 0x101:  // ImageLength
                if (std::string("II") == ti.endianess) {
                    // Little endian: leave byte order intact
                    dt = (static_cast<unsigned short>(buf[2]) & 0x00FF)
                            + (static_cast<unsigned short>(buf[3] << 8) & 0xFF00);
                    if(3 == dt) {
                        ti.image_length = (static_cast<unsigned long>(buf[8]) & 0x000000FF)
                                + (static_cast<unsigned long>(buf[9] << 8) & 0x0000FF00);
                    } else {
                        ti.image_length = (static_cast<unsigned long>(buf[8]) & 0x000000FF)
                                + (static_cast<unsigned long>(buf[9] << 8) & 0x0000FF00)
                                + (static_cast<unsigned long>(buf[10] << 16) & 0x00FF0000)
                                + (static_cast<unsigned long>(buf[11] << 24) & 0xFF000000);
                    }
                } else {
                    // Big endian: swap byte order
                    dt = (static_cast<unsigned short>(buf[3]) & 0x00FF)
                            + (static_cast<unsigned short>(buf[2] << 8) & 0xFF00);
                    if(3 == dt) {
                        ti.image_length = (static_cast<unsigned long>(buf[9]) & 0x000000FF)
                                + (static_cast<unsigned long>(buf[8] << 8) & 0x0000FF00);
                    } else {
                        ti.image_length = (static_cast<unsigned long>(buf[11]) & 0x000000FF)
                                + (static_cast<unsigned long>(buf[10] << 8) & 0x0000FF00)
                                + (static_cast<unsigned long>(buf[9] << 16) & 0x00FF0000)
                                + (static_cast<unsigned long>(buf[8] << 24) & 0xFF000000);
                    }
                }
                std::cout << "ImageLength: " << ti.image_length << std::endl;
                break;

            case 0x102:  // BitsPerSample
                if (std::string("II") == ti.endianess) {
                    dt = (static_cast<unsigned long>(buf[4]) & 0x000000FF)
                            + (static_cast<unsigned long>(buf[5] << 8) & 0x0000FF00)
                            + (static_cast<unsigned long>(buf[6] << 8) & 0x00FF0000)
                            + (static_cast<unsigned long>(buf[7] << 8) & 0xFF000000);
                    if(3 == dt) {
                        offset = (static_cast<unsigned long>(buf[8]) & 0x000000FF)
                                + (static_cast<unsigned long>(buf[9] << 8) & 0x0000FF00)
                                + (static_cast<unsigned long>(buf[10] << 16) & 0x00FF0000)
                                + (static_cast<unsigned long>(buf[11] << 24) & 0xFF000000);
                        imfstrm.seekg(offset, std::ios::beg);
                        for(unsigned long j=0; j < dt; j++) {
                            imfstrm.read(val.data(), 2);
                            ti.bits_per_sample.push_back(
                                    (static_cast<unsigned short>(val[0]) & 0x00FF)
                                    + (static_cast<unsigned short>(val[1] << 8) & 0xFF00)
                                    );
                        }
                    } else {
                        ti.bits_per_sample.push_back(
                                (static_cast<unsigned short>(buf[8]) & 0x00FF)
                                + (static_cast<unsigned short>(buf[9] << 8) & 0xFF00)
                                );
                    }
                } else {
                    dt = (static_cast<unsigned long>(buf[7]) & 0x000000FF)
                            + (static_cast<unsigned long>(buf[6] << 8) & 0x0000FF00)
                            + (static_cast<unsigned long>(buf[5] << 8) & 0x00FF0000)
                            + (static_cast<unsigned long>(buf[4] << 8) & 0xFF000000);
                    if(3 == dt) {
                        offset = (static_cast<unsigned long>(buf[11]) & 0x000000FF)
                                + (static_cast<unsigned long>(buf[10] << 8) & 0x0000FF00)
                                + (static_cast<unsigned long>(buf[9] << 16) & 0x00FF0000)
                                + (static_cast<unsigned long>(buf[8] << 24) & 0xFF000000);
                        imfstrm.seekg(offset, std::ios::beg);
                        for(unsigned long j=0; j < dt; j++) {
                            imfstrm.read(val.data(), 2);
                            ti.bits_per_sample.push_back(
                                    (static_cast<unsigned short>(val[1]) & 0x00FF)
                                    + (static_cast<unsigned short>(val[0] << 8) & 0xFF00)
                                    );
                        }
                    } else {
                        ti.bits_per_sample.push_back(
                                (static_cast<unsigned short>(buf[9]) & 0x00FF)
                                + (static_cast<unsigned short>(buf[8] << 8) & 0xFF00)
                                );
                    }
                }
                std::cout << "BitsPerSample: ";
                std::for_each(
                        ti.bits_per_sample.begin(),
                        ti.bits_per_sample.end(),
                        [] (const unsigned short &x) { std::cout << x <<" "; }
                        );
                std::cout << std::endl;
                break;

            case 0x103:  // Compression
                if (std::string("II") == ti.endianess) {
                    ti.compression = (static_cast<unsigned short>(buf[8]) & 0x00FF)
                            + (static_cast<unsigned short>(buf[9] << 8) & 0xFF00);
                } else {
                    ti.compression  = (static_cast<unsigned short>(buf[9]) & 0x00FF)
                            + (static_cast<unsigned short>(buf[8] << 8) & 0xFF00);
                }
                std::cout << "Compression: " << ti.compression << std::endl;
                break;

            case 0x106:  // PhotometricInterpretation
                if (std::string("II") == ti.endianess) {
                    ti.photometric_interpretation = (static_cast<unsigned short>(buf[8]) & 0x00FF)
                            + (static_cast<unsigned short>(buf[9] << 8) & 0xFF00);
                } else {
                    ti.photometric_interpretation  = (static_cast<unsigned short>(buf[9]) & 0x00FF)
                            + (static_cast<unsigned short>(buf[8] << 8) & 0xFF00);
                }
                std::cout << "PhotometricInterpretation: " << ti.photometric_interpretation << std::endl;
                break;

            case 0x115:  // SamplesPerPixel
                if (std::string("II") == ti.endianess) {
                    ti.samples_per_pixel = (static_cast<unsigned short>(buf[8]) & 0x00FF)
                            + (static_cast<unsigned short>(buf[9] << 8) & 0xFF00);
                } else {
                    ti.samples_per_pixel  = (static_cast<unsigned short>(buf[9]) & 0x00FF)
                            + (static_cast<unsigned short>(buf[8] << 8) & 0xFF00);
                }
                std::cout << "SamplesPerPixel: " << ti.samples_per_pixel << std::endl;
                break;

            case 0x11A:  // XResolution
                if (std::string("II") == ti.endianess) {
                    // Little endian: leave byte order intact
                    offset = (static_cast<unsigned long>(buf[8]) & 0x000000FF)
                            + (static_cast<unsigned long>(buf[9] << 8) & 0x0000FF00)
                            + (static_cast<unsigned long>(buf[10] << 16) & 0x00FF0000)
                            + (static_cast<unsigned long>(buf[11] << 24) & 0xFF000000);
                    imfstrm.seekg(offset, std::ios::beg);
                    imfstrm.read(val.data(), 8);
                    ti.x_resolution[0] = (static_cast<unsigned long>(val[0]) & 0x000000FF)
                            + (static_cast<unsigned long>(val[1] << 8) & 0x0000FF00)
                            + (static_cast<unsigned long>(val[2] << 16) & 0x00FF0000)
                            + (static_cast<unsigned long>(val[3] << 24) & 0xFF000000);
                    ti.x_resolution[1] = (static_cast<unsigned long>(val[4]) & 0x000000FF)
                            + (static_cast<unsigned long>(val[5] << 8) & 0x0000FF00)
                            + (static_cast<unsigned long>(val[6] << 16) & 0x00FF0000)
                            + (static_cast<unsigned long>(val[7] << 24) & 0xFF000000);
                } else {
                    // Big endian: swap byte order
                    offset = (static_cast<unsigned long>(buf[11]) & 0x000000FF)
                            + (static_cast<unsigned long>(buf[10] << 8) & 0x0000FF00)
                            + (static_cast<unsigned long>(buf[9] << 16) & 0x00FF0000)
                            + (static_cast<unsigned long>(buf[8] << 24) & 0xFF000000);
                    imfstrm.seekg(offset, std::ios::beg);
                    imfstrm.read(val.data(), 8);
                    ti.x_resolution[0] = (static_cast<unsigned long>(val[3]) & 0x000000FF)
                            + (static_cast<unsigned long>(val[2] << 8) & 0x0000FF00)
                            + (static_cast<unsigned long>(val[1] << 16) & 0x00FF0000)
                            + (static_cast<unsigned long>(val[0] << 24) & 0xFF000000);
                    ti.x_resolution[1] = (static_cast<unsigned long>(val[7]) & 0x000000FF)
                            + (static_cast<unsigned long>(val[6] << 8) & 0x0000FF00)
                            + (static_cast<unsigned long>(val[5] << 16) & 0x00FF0000)
                            + (static_cast<unsigned long>(val[4] << 24) & 0xFF000000);
                }
                std::cout << "XResolution: "
                    << static_cast<double>(ti.x_resolution[0]) / static_cast<double>(ti.x_resolution[1])
                    << std::endl;
                break;

            case 0x11B:  // YResolution
                if (std::string("II") == ti.endianess) {
                    // Little endian: leave byte order intact
                    offset = (static_cast<unsigned long>(buf[8]) & 0x000000FF)
                            + (static_cast<unsigned long>(buf[9] << 8) & 0x0000FF00)
                            + (static_cast<unsigned long>(buf[10] << 16) & 0x00FF0000)
                            + (static_cast<unsigned long>(buf[11] << 24) & 0xFF000000);
                    imfstrm.seekg(offset, std::ios::beg);
                    imfstrm.read(val.data(), 8);
                    ti.y_resolution[0] = (static_cast<unsigned long>(val[0]) & 0x000000FF)
                            + (static_cast<unsigned long>(val[1] << 8) & 0x0000FF00)
                            + (static_cast<unsigned long>(val[2] << 16) & 0x00FF0000)
                            + (static_cast<unsigned long>(val[3] << 24) & 0xFF000000);
                    ti.y_resolution[1] = (static_cast<unsigned long>(val[4]) & 0x000000FF)
                            + (static_cast<unsigned long>(val[5] << 8) & 0x0000FF00)
                            + (static_cast<unsigned long>(val[6] << 16) & 0x00FF0000)
                            + (static_cast<unsigned long>(val[7] << 24) & 0xFF000000);
                } else {
                    // Big endian: swap byte order
                    offset = (static_cast<unsigned long>(buf[11]) & 0x000000FF)
                            + (static_cast<unsigned long>(buf[10] << 8) & 0x0000FF00)
                            + (static_cast<unsigned long>(buf[9] << 16) & 0x00FF0000)
                            + (static_cast<unsigned long>(buf[8] << 24) & 0xFF000000);
                    imfstrm.seekg(offset, std::ios::beg);
                    imfstrm.read(val.data(), 8);
                    ti.y_resolution[0] = (static_cast<unsigned long>(val[3]) & 0x000000FF)
                            + (static_cast<unsigned long>(val[2] << 8) & 0x0000FF00)
                            + (static_cast<unsigned long>(val[1] << 16) & 0x00FF0000)
                            + (static_cast<unsigned long>(val[0] << 24) & 0xFF000000);
                    ti.y_resolution[1] = (static_cast<unsigned long>(val[7]) & 0x000000FF)
                            + (static_cast<unsigned long>(val[6] << 8) & 0x0000FF00)
                            + (static_cast<unsigned long>(val[5] << 16) & 0x00FF0000)
                            + (static_cast<unsigned long>(val[4] << 24) & 0xFF000000);
                }
                std::cout << "YResolution: "
                    << static_cast<double>(ti.y_resolution[0]) / static_cast<double>(ti.y_resolution[1])
                    << std::endl;
                break;

            case 0x128:  // ResolutionUnit
                if (std::string("II") == ti.endianess) {
                    ti.resolution_unit = (static_cast<unsigned short>(buf[8]) & 0x00FF)
                            + (static_cast<unsigned short>(buf[9] << 8) & 0xFF00);
                } else {
                    ti.resolution_unit = (static_cast<unsigned short>(buf[9]) & 0x00FF)
                            + (static_cast<unsigned short>(buf[8] << 8) & 0xFF00);
                }
                std::cout << "ResolutionUnit: " << ti.resolution_unit << std::endl;
                break;

            case 0x132:  // DateTime
                if (std::string("II") == ti.endianess) {
                    // Little endian: leave byte order intact
                    offset = (static_cast<unsigned long>(buf[8]) & 0x000000FF)
                            + (static_cast<unsigned long>(buf[9] << 8) & 0x0000FF00)
                            + (static_cast<unsigned long>(buf[10] << 16) & 0x00FF0000)
                            + (static_cast<unsigned long>(buf[11] << 24) & 0xFF000000);
                } else {
                    offset = (static_cast<unsigned long>(buf[11]) & 0x000000FF)
                            + (static_cast<unsigned long>(buf[10] << 8) & 0x0000FF00)
                            + (static_cast<unsigned long>(buf[9] << 16) & 0x00FF0000)
                            + (static_cast<unsigned long>(buf[8] << 24) & 0xFF000000);
                }
                imfstrm.seekg(offset, std::ios::beg);
                imfstrm.read(val.data(), 20);
                ti.date_time = std::string(val.data());
                std::cout << "DateTime: " << ti.date_time << std::endl;
                break;
        }

        offset = first_ifd_offset + 12*(i + 1);
        imfstrm.seekg(offset, std::ios::beg);
    }

    imfstrm.close();

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
