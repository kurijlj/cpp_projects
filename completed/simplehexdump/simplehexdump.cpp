// ============================================================================
// simplehexdump - Application to dump hexadecimal values of the input string.
//
//  Copyright (C) 2020 Ljubomir Kurij <kurijlj@gmail.com>
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
// 2020-04-26 Ljubomir Kurij <kurijlj@gmail.com>
//
// * simplehexdump.cpp: created.
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

#include <cstdlib>  // required by EXIT_SUCCESS, EXIT_FAILURE
#include <iostream>  // required by cin, cout, ...
#include <iomanip>  // required by setfiil, setw, ...
#include <string>  // self explanatory ...
#include <fstream>  // requird by ifstream
#include <boost/program_options.hpp>  // self explanatory ...


// ============================================================================
// Define namespace aliases
// ============================================================================

namespace ap = boost::program_options;  // 'ap' as arguments parsing


// ============================================================================
// Global constants section
// ============================================================================

const std::string kAppName = "clf_boost";
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
// App's main function body
// ============================================================================

int main(int argc, char *argv[])
{
    std::string input;  // We store input string here;

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
Application to dump hexadecimal values of the input string.\n\n\
Mandatory arguments to long options are mandatory for short options too.\n\n\
Supported options are");

        // When we are adding options, first parameter is a name to be used in
        // command line. Second parameter is a type of that option, wrapped in
        // value<> class. Third parameter must be a short description of
        // that option.
        pos_opts.add_options()
            ("STRING", ap::value<std::string>(),
                "(mandatory) string to be dumped as hex")
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
        p.add("STRING", 1);

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
            std::cout << "\n" << visible_opts << "\n";
            PrintPositionalArgumentsHelp();
            PrintReportBugsTo();
        } else if (vmap.count("usage")) {
            PrintUsage();
            PrintShortHelp();
        } else {
            if (!vmap.count("STRING")) {
                PrintUsage();
                PrintShortHelp();
                return EXIT_FAILURE;
            } else {
                input = vmap["STRING"].as<std::string>();
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
        std::cerr << exec_name << ": " << "Exception of unknown type!"
            << std::endl;
        PrintUsage();
        PrintShortHelp();
        return EXIT_FAILURE;
    }

    // Dump string as sequence of hex values to the screen.
    for(unsigned int i=0; i<input.size(); i++) {
        std::cout << std::setfill('0') << std::setw(2) << std::hex <<
            (0xff & (unsigned int) input[i]);
        if(0 == (i + 1) % 16) {
            std::cout << '\n';
        } else {
            std::cout << ' ';
        }
    }
    std::cout << std::endl;

    // Everything went fine. We can bail out.
    return EXIT_SUCCESS;
}



// ============================================================================
// Function definitions
// ============================================================================

void PrintUsage() {
    std::cout << "Usage: " << exec_name
        << " [options ...] [STRING]"
        << std::endl;
}


void PrintShortHelp() {
    std::cout << "Try '" << exec_name << " --help' for more information."
        << std::endl;
}


void PrintPositionalArgumentsHelp() {
    std::cout << "\n\
STRING is the input dumped as hexadecimal values. This argument is\n\
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
