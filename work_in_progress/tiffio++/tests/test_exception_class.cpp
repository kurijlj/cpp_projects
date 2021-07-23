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
// * test_validators.cpp: created.
//
// ============================================================================


// ============================================================================
//
// References (this section should be deleted in the release version)
//
// * For coding style visit Google C++ Style Guide page at
//   <https://google.github.io/styleguide/cppguide.html>.
//
// ============================================================================


// ============================================================================
// Preprocessor directives
// ============================================================================


// ============================================================================
// Headers include section
// ============================================================================

// "C" system headers

// Standard Library headers
#include <filesystem>  // Used manipulating filesystem paths
#include <string>      // self explanatory ...

// External libraries headers
#include <lest.hpp>  // Required by unit testing framework

// Project headers
#include <tiffio++/tiffio++.hpp>


// ============================================================================
// Define namespace aliases
// ============================================================================

namespace fs = std::filesystem;
namespace ls = lest;


// ============================================================================
// Define global constants
// ============================================================================

// const fs::path kRegularTiff1 = "./data/img20191023_12463056.tif"
// const fs::path kRegularTiff2 = "./data/QA20200727020.tif"
// const fs::path kRegularPng   = "./data/img20191101_13592687.png"
// const fs::path kDummyCpp     = "./data/test_dummy.cpp"
// const fs::path kDummyTif     = "./data/test_dummy.tif"
// const fs::path kDummyTxt     = "./data/test_dummy.txt"


// ============================================================================
// Tests specification
// ============================================================================

const ls::test specification[] =
{
    CASE ("LibtiffError Class Tests") {
        SETUP ("Module Known") {
            TIFFIOObject::LibtiffError error {
                "dummy_module",
                "This is error message"
            };

            EXPECT ("dummy_module: ERROR, This is error message"
                    == error.message());
        }

        SETUP ("Module Unknown") {
            TIFFIOObject::LibtiffError error {"", "This is error message"};

            EXPECT ("ERROR, This is error message" == error.message());
        }
    },

    CASE ("LibtiffWarning Class Tests") {
        SETUP ("Module Known") {
            TIFFIOObject::LibtiffWarning warning {
                "dummy_module",
                "This is warning message"
            };

            EXPECT ("dummy_module: WARNING, This is warning message"
                    == warning.message());
        }

        SETUP ("Module Unknown") {
            TIFFIOObject::LibtiffWarning warning {
                "",
                "This is warning message"
            };

            EXPECT ("WARNING, This is warning message" == warning.message());
        }
    }

};


// ============================================================================
// Entry point for main()
// ============================================================================

int main (int argc, char * argv[])
{
    return ls::run (specification, argc, argv);
}
