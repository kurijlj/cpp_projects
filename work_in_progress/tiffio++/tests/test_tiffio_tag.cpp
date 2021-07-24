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
#include <iostream>
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

const fs::path kGkQA1 = "./data/img20191023_12463056.tif";
const fs::path kGkQA2 = "./data/QA20200727020.tif";
const fs::path kCells = "./data/at3_1m4_01.tif";
const fs::path kMri   = "./data/mri.tif";
const fs::path kRoi   = "./data/roi_14.tif";


// ============================================================================
// Tests specification
// ============================================================================

const ls::test specification[] =
{
    CASE ("Gamma Knife QA #1") {
        TIFFIOObject tif_obj {
            kGkQA1,
            TIFFIOObject::FileAccessMode::Read
        };
        unsigned long int width = 0;
        unsigned long int length = 0;

        tif_obj.printErrors(false);
        tif_obj.printWarnings(false);
        EXPECT_NO_THROW(tif_obj.open());
        EXPECT_NO_THROW(tif_obj.readTagValue<unsigned long int>(
                    TIFFIOObject::ImageWidth,
                    &width
                    ));
        EXPECT(true == tif_obj.readTagValue<unsigned long int>(
                    TIFFIOObject::ImageWidth,
                    &width
                    ));
        EXPECT(843 == width);
        EXPECT_NO_THROW(tif_obj.readTagValue<unsigned long int>(
                    TIFFIOObject::ImageLength,
                    &length
                    ));
        EXPECT(true == tif_obj.readTagValue<unsigned long int>(
                    TIFFIOObject::ImageLength,
                    &length
                    ));
        EXPECT(547 == length);
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
