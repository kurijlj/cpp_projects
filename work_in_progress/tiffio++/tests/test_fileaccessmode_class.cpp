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

// const fs::path kRegularTiff1 = "./data/img20191023_12463056.tif";
// const fs::path kRegularTiff2 = "./data/QA20200727020.tif";
// const fs::path kRegularPng   = "./data/img20191101_13592687.png";
// const fs::path kDummyCpp     = "./data/test_dummy.cpp";
// const fs::path kDummyTif     = "./data/test_dummy.tif";
// const fs::path kDummyTxt     = "./data/test_dummy.txt";


// ============================================================================
// Tests specification
// ============================================================================

const ls::test specification[] =
{
    CASE ("Append Access Mode") {
        TIFFIOObject::FileAccessMode mode {
            TIFFIOObject::FileAccessMode::Append
        };
        TIFFIOObject::FileAccessMode equal_mode {
            TIFFIOObject::FileAccessMode::Append
        };
        TIFFIOObject::FileAccessMode nonequal_mode {
            TIFFIOObject::FileAccessMode::Write
        };
        TIFFIOObject::FileAccessMode default_mode
            = TIFFIOObject::FileAccessMode();

        EXPECT (TIFFIOObject::FileAccessMode::Append == mode.value());
        EXPECT ("a" == std::string(mode.c_str()));
        EXPECT (false == mode.equalTo(default_mode));
        EXPECT (true == mode.equalTo(equal_mode));
        EXPECT (false == mode.equalTo(nonequal_mode));

    },

    CASE ("Read Access Mode") {
        TIFFIOObject::FileAccessMode mode {
            TIFFIOObject::FileAccessMode::Read
        };
        TIFFIOObject::FileAccessMode equal_mode {
            TIFFIOObject::FileAccessMode::Read
        };
        TIFFIOObject::FileAccessMode nonequal_mode {
            TIFFIOObject::FileAccessMode::Write
        };
        TIFFIOObject::FileAccessMode default_mode
            = TIFFIOObject::FileAccessMode();

        EXPECT (TIFFIOObject::FileAccessMode::Read == mode.value());
        EXPECT ("r" == std::string(mode.c_str()));
        EXPECT (true == mode.equalTo(default_mode));
        EXPECT (true == mode.equalTo(equal_mode));
        EXPECT (false == mode.equalTo(nonequal_mode));

    },

    CASE ("ReadWrite Access Mode") {
        TIFFIOObject::FileAccessMode mode {
            TIFFIOObject::FileAccessMode::ReadWrite
        };
        TIFFIOObject::FileAccessMode equal_mode {
            TIFFIOObject::FileAccessMode::ReadWrite
        };
        TIFFIOObject::FileAccessMode nonequal_mode {
            TIFFIOObject::FileAccessMode::Write
        };
        TIFFIOObject::FileAccessMode default_mode
            = TIFFIOObject::FileAccessMode();

        EXPECT (TIFFIOObject::FileAccessMode::ReadWrite == mode.value());
        EXPECT ("r+" == std::string(mode.c_str()));
        EXPECT (false == mode.equalTo(default_mode));
        EXPECT (true == mode.equalTo(equal_mode));
        EXPECT (false == mode.equalTo(nonequal_mode));

    },

    CASE ("Write Access Mode") {
        TIFFIOObject::FileAccessMode mode {
            TIFFIOObject::FileAccessMode::Write
        };
        TIFFIOObject::FileAccessMode equal_mode {
            TIFFIOObject::FileAccessMode::Write
        };
        TIFFIOObject::FileAccessMode nonequal_mode {
            TIFFIOObject::FileAccessMode::ReadWrite
        };
        TIFFIOObject::FileAccessMode default_mode
            = TIFFIOObject::FileAccessMode();

        EXPECT (TIFFIOObject::FileAccessMode::Write == mode.value());
        EXPECT ("w" == std::string(mode.c_str()));
        EXPECT (false == mode.equalTo(default_mode));
        EXPECT (true == mode.equalTo(equal_mode));
        EXPECT (false == mode.equalTo(nonequal_mode));

    },

    CASE ("Default Constructor Access Mode") {
        TIFFIOObject::FileAccessMode mode
            = TIFFIOObject::FileAccessMode();
        TIFFIOObject::FileAccessMode nonequal_mode {
            TIFFIOObject::FileAccessMode::ReadWrite
        };
        TIFFIOObject::FileAccessMode default_mode
            = TIFFIOObject::FileAccessMode();

        EXPECT (TIFFIOObject::FileAccessMode::Read == mode.value());
        EXPECT ("r" == std::string(mode.c_str()));
        EXPECT (true == mode.equalTo(default_mode));
        EXPECT (false == mode.equalTo(nonequal_mode));

    },

    CASE ("Copy Constructor") {
        TIFFIOObject::FileAccessMode mode
            = TIFFIOObject::FileAccessMode();
        TIFFIOObject::FileAccessMode mode_copy
            = TIFFIOObject::FileAccessMode(mode);
        TIFFIOObject::FileAccessMode default_mode
            = TIFFIOObject::FileAccessMode();

        EXPECT (TIFFIOObject::FileAccessMode::Read == mode.value());
        EXPECT (TIFFIOObject::FileAccessMode::Read == mode_copy.value());
        EXPECT ("r" == std::string(mode.c_str()));
        EXPECT ("r" == std::string(mode_copy.c_str()));
        EXPECT (true == mode.equalTo(mode_copy));
        EXPECT (true == mode.equalTo(default_mode));
        EXPECT (true == mode_copy.equalTo(default_mode));

    },

};


// ============================================================================
// Entry point for main()
// ============================================================================

int main (int argc, char * argv[])
{
    return ls::run (specification, argc, argv);
}
