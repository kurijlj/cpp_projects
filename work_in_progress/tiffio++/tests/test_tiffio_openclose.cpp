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

const fs::path kRegularTif1 = "./data/img20191023_12463056.tif";
const fs::path kRegularTif2 = "./data/QA20200727020.tif";
const fs::path kRegularPng   = "./data/img20191101_13592687.png";
const fs::path kDummyCpp     = "./data/test_dummy.cpp";
const fs::path kDummyTif     = "./data/test_dummy.tif";
const fs::path kDummyTxt     = "./data/test_dummy.txt";


// ============================================================================
// Tests specification
// ============================================================================

const ls::test specification[] =
{
    CASE ("Regular Tif 1") {
        TIFFIOObject tif_obj = TIFFIOObject(
            kRegularTif1.string(),
            TIFFIOObject::FileAccessMode::Read
        );

        EXPECT_NO_THROW(tif_obj.open());
        EXPECT_NO_THROW(tif_obj.close());
        tif_obj.printErrors(false);
        tif_obj.printWarnings(false);
        EXPECT_NO_THROW(tif_obj.open());
        EXPECT_NO_THROW(tif_obj.close());

    },

    CASE ("Regular Tif 2") {
        TIFFIOObject tif_obj = TIFFIOObject(
            kRegularTif2.string(),
            TIFFIOObject::FileAccessMode::Read
        );

        EXPECT_NO_THROW(tif_obj.open());
        EXPECT_NO_THROW(tif_obj.close());
        tif_obj.printErrors(false);
        tif_obj.printWarnings(false);
        EXPECT_NO_THROW(tif_obj.open());
        EXPECT_NO_THROW(tif_obj.close());

    },

    CASE ("Regular PNG") {
        TIFFIOObject tif_obj = TIFFIOObject(
            kRegularPng.string(),
            TIFFIOObject::FileAccessMode::Read
        );

        EXPECT_NO_THROW(tif_obj.open());
        EXPECT_NO_THROW(tif_obj.close());
        tif_obj.printErrors(false);
        tif_obj.printWarnings(false);
        EXPECT_THROWS(tif_obj.open());
        EXPECT_NO_THROW(tif_obj.close());
        EXPECT_THROWS_AS(tif_obj.open(), TIFFIOObject::TIFFIOException);
        EXPECT_NO_THROW(tif_obj.close());
        EXPECT_THROWS_AS(tif_obj.open(), TIFFIOObject::LibtiffError);
        EXPECT_NO_THROW(tif_obj.close());

    },

    CASE ("Dummy CPP") {
        TIFFIOObject tif_obj {
            kDummyCpp.string(),
            TIFFIOObject::FileAccessMode::Read
        };

        EXPECT_NO_THROW(tif_obj.open());

    },

    CASE ("Dummy Tif") {
        TIFFIOObject tif_obj = TIFFIOObject(
            kDummyTif.string(),
            TIFFIOObject::FileAccessMode::Read
        );

        EXPECT_NO_THROW(tif_obj.open());
        EXPECT_NO_THROW(tif_obj.close());
        tif_obj.printErrors(false);
        tif_obj.printWarnings(false);
        EXPECT_THROWS(tif_obj.open());
        EXPECT_NO_THROW(tif_obj.close());
        EXPECT_THROWS_AS(tif_obj.open(), TIFFIOObject::TIFFIOException);
        EXPECT_NO_THROW(tif_obj.close());
        EXPECT_THROWS_AS(tif_obj.open(), TIFFIOObject::LibtiffError);
        EXPECT_NO_THROW(tif_obj.close());

    },

    CASE ("Dummy Txt") {
        TIFFIOObject tif_obj = TIFFIOObject(
            kDummyTxt.string(),
            TIFFIOObject::FileAccessMode::Read
        );

        EXPECT_NO_THROW(tif_obj.open());
        EXPECT_NO_THROW(tif_obj.close());
        tif_obj.printErrors(false);
        tif_obj.printWarnings(false);
        EXPECT_THROWS(tif_obj.open());
        EXPECT_NO_THROW(tif_obj.close());
        EXPECT_THROWS_AS(tif_obj.open(), TIFFIOObject::TIFFIOException);
        EXPECT_NO_THROW(tif_obj.close());
        EXPECT_THROWS_AS(tif_obj.open(), TIFFIOObject::LibtiffError);
        EXPECT_NO_THROW(tif_obj.close());

    },

};


// ============================================================================
// Entry point for main()
// ============================================================================

int main (int argc, char * argv[])
{
    return ls::run (specification, argc, argv);
}
