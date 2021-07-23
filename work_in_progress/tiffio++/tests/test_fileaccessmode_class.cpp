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

// fs::path kRegularTiff1 = "./data/img20191023_12463056.tif"
// fs::path kRegularTiff2 = "./data/QA20200727020.tif"
// fs::path kRegularPng   = "./data/img20191101_13592687.png"
// fs::path kDummyCpp     = "./data/test_dummy.cpp"
// fs::path kDummyTif     = "./data/test_dummy.tif"
// fs::path kDummyTxt     = "./data/test_dummy.txt"


// ============================================================================
// Tests specification
// ============================================================================

const ls::test specification[] =
{
    CASE ("Append Access Mode") {
        SETUP ("Copy Constructor") {
            TIFFIOObject::FileAccessMode mode {
                TIFFIOObject::FileAccessMode::Append,
                TIFFIOObject::FileAccessMode::ForceLittleEndian
            };
            TIFFIOObject::FileAccessMode mode_copy
                = TIFFIOObject::FileAccessMode(mode);

            EXPECT (true == mode.equalTo(mode_copy));
            EXPECT (false == mode_copy.equalTo(TIFFIOObject::FileAccessMode()));

        }

        SETUP ("None Modifier") {
            TIFFIOObject::FileAccessMode mode {
                TIFFIOObject::FileAccessMode::Append,
                TIFFIOObject::FileAccessMode::None
            };
            TIFFIOObject::FileAccessMode equal_mode {
                TIFFIOObject::FileAccessMode::Append,
                TIFFIOObject::FileAccessMode::None
            };
            TIFFIOObject::FileAccessMode nonequal_mode {
                TIFFIOObject::FileAccessMode::Append,
                TIFFIOObject::FileAccessMode::ForceLittleEndian
            };
            TIFFIOObject::FileAccessMode default_mode
                = TIFFIOObject::FileAccessMode();

            EXPECT (TIFFIOObject::FileAccessMode::Append == mode.mode());
            EXPECT (TIFFIOObject::FileAccessMode::None == mode.modifier());
            EXPECT ("a" == mode.toStdString());
            EXPECT (true == mode.equalTo(equal_mode));
            EXPECT (false == mode.equalTo(nonequal_mode));
            EXPECT (false == mode.equalTo(default_mode));

        }

    },

    CASE ("Read Access Mode") {
        SETUP ("Default Constructor") {
            TIFFIOObject::FileAccessMode mode = TIFFIOObject::FileAccessMode();
            TIFFIOObject::FileAccessMode equal_mode
                = TIFFIOObject::FileAccessMode();
            TIFFIOObject::FileAccessMode nonequal_mode {
                TIFFIOObject::FileAccessMode::Append,
                TIFFIOObject::FileAccessMode::None
            };
            TIFFIOObject::FileAccessMode default_mode
                = TIFFIOObject::FileAccessMode();

            EXPECT (TIFFIOObject::FileAccessMode::Read == mode.mode());
            EXPECT (TIFFIOObject::FileAccessMode::None == mode.modifier());
            EXPECT ("r" == mode.toStdString());
            EXPECT (true == mode.equalTo(default_mode));
            EXPECT (true == mode.equalTo(equal_mode));
            EXPECT (false == mode.equalTo(nonequal_mode));

        }

    },

    CASE ("Write Access Mode") {
        SETUP ("ForceLSB Modifier") {
            TIFFIOObject::FileAccessMode mode {
                TIFFIOObject::FileAccessMode::Write,
                TIFFIOObject::FileAccessMode::ForceLSB
            };
            TIFFIOObject::FileAccessMode equal_mode {
                TIFFIOObject::FileAccessMode::Write,
                TIFFIOObject::FileAccessMode::ForceLSB
            };
            TIFFIOObject::FileAccessMode nonequal_mode {
                TIFFIOObject::FileAccessMode::Append,
                TIFFIOObject::FileAccessMode::None
            };
            TIFFIOObject::FileAccessMode default_mode
                = TIFFIOObject::FileAccessMode();

            EXPECT (TIFFIOObject::FileAccessMode::Write == mode.mode());
            EXPECT (TIFFIOObject::FileAccessMode::ForceLSB == mode.modifier());
            EXPECT ("wL" == mode.toStdString());
            EXPECT (false == mode.equalTo(default_mode));
            EXPECT (true == mode.equalTo(equal_mode));
            EXPECT (false == mode.equalTo(nonequal_mode));

        }

    },

};


// ============================================================================
// Entry point for main()
// ============================================================================

int main (int argc, char * argv[])
{
    return ls::run (specification, argc, argv);
}
